#include <TheThingsNetwork.h>
#include <TheThingsMessage.h>
#include <SoftwareSerial.h>

// Définir votre AppEUI et AppKey
const char *appEui = "5d564638a37cb161";
const char *appKey = "1abce0981ed3c9648fd735bd97e2b74e";

// Définition des broches pour le module Bluetooth
SoftwareSerial bluetoothSerial(A3, A4); // RX, TX

// Variable pour suivre l'état de la connexion Bluetooth
bool isConnected = false;

#include "SSD1306Ascii.h"
#include "SSD1306AsciiAvrI2c.h"
#define I2C_ADDRESS 0x3C
SSD1306AsciiAvrI2c oled;

SoftwareSerial loraSerial(A0, A1); // TX, RX
#define debugSerial Serial

// Définir le plan de fréquence (EU868 ou US915)
#define freqPlan TTN_FP_EU868

#define GAZ_SENSOR_PIN A2
#define LED_PIN 12

TheThingsNetwork ttn(loraSerial, debugSerial, freqPlan);

devicedata_t data = api_DeviceData_init_default;

void setup()
{
  loraSerial.begin(57600);
  debugSerial.begin(57600);
  // Initialisation de la communication Bluetooth
  bluetoothSerial.begin(9600);

  // Initialisation de la LED
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // La LED est éteinte au démarrage

  // Moniteur série pour debug
  Serial.begin(9600);
  Serial.println("Module Bluetooth initialisé. En attente de connexion...");

  // Attendre un maximum de 10s pour la connexion au Moniteur Série
  while (!debugSerial && millis() < 10000)
    ;

  debugSerial.println("-- STATUT : Initialisation de la connexion au réseau LoRa --");
  ttn.showStatus();

  debugSerial.println("-- REJOINDRE : Tentative de connexion au réseau --");
  ttn.join(appEui, appKey);

  // Configurer les champs à inclure dans le message encodé
  data.has_motion = true;
  data.has_water = false;
  data.has_temperature_celcius = true;
  data.has_temperature_fahrenheit = true;
  data.has_humidity = true;

  pinMode(LED_PIN, OUTPUT);

  oled.begin(&Adafruit128x64, I2C_ADDRESS);
  oled.setFont(Adafruit5x7);  
  oled.clear();
  oled.set2X();
  oled.println("Bjr BG");
}

void loop()
{
  // Détecter si un appareil Bluetooth s'est connecté
  if (bluetoothSerial.available() && !isConnected) {
    isConnected = true;
    Serial.println("Connexion Bluetooth réussie !");
  }

  // Lire la valeur du capteur de gaz
  int GAZ_VALUE = analogRead(GAZ_SENSOR_PIN);
  debugSerial.print("VALEUR_CAPTEUR_GAZ : ");
  debugSerial.println(GAZ_VALUE);

  // Allumer la LED si la valeur du gaz dépasse le seuil et envoyer "DANGER" via Bluetooth
  if (GAZ_VALUE > 10) {
    digitalWrite(LED_PIN, HIGH);
    debugSerial.println("Seuil dépassé ! LED allumée.");
    oled.clearField(0,2,5);
    oled.setCursor(0, 2);  // Positionner le curseur sur la ligne 2
    oled.println("Danger Gaz");

    oled.setCursor(0, 4);  // Positionner le curseur sur la ligne 3 (ligne suivante)
    oled.println("polluant");

    // Envoyer le message "DANGER" via Bluetooth
    if (isConnected) {
      bluetoothSerial.println("DANGER");
    }

    // Envoyer "DANGER" au réseau LoRa
    const char dangerMessage[] = "DANGER";
    ttn.sendBytes((uint8_t *)dangerMessage, sizeof(dangerMessage) - 1);
  } else {
    digitalWrite(LED_PIN, LOW);
    debugSerial.println("Niveau de gaz normal. LED éteinte.");
    oled.clearField(0,2,5);
    oled.setCursor(0, 3);
    oled.println("Tout est OK");

    // Envoyer la valeur normale via Bluetooth
    if (isConnected) {
      bluetoothSerial.print("GAZ: ");
      bluetoothSerial.println(GAZ_VALUE);
    }

    // Envoyer la valeur du capteur au réseau LoRa
    debugSerial.print("Envoi des données : GAZ_VALUE = ");
    debugSerial.println(GAZ_VALUE);
    ttn.sendBytes((uint8_t *)&GAZ_VALUE, sizeof(GAZ_VALUE));
  }

  // Attendre 5 secondes avant la prochaine lecture
  debugSerial.println("-- ATTENTE : Attente de 5 secondes avant la prochaine lecture --");
  delay(5000);
}