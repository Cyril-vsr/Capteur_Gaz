#include <SoftwareSerial.h>

// Définition des broches pour SoftwareSerial
#define RX_PIN A1 // Broche où le TX du RN2483A est connecté
#define TX_PIN A0 // Broche où le RX du RN2483A est connecté
#define RESET_PIN 8 // Broche pour réinitialiser le RN2483A

SoftwareSerial RN2483(TX_PIN, RX_PIN);

void setup() {
  // Initialisation des broches
  pinMode(RESET_PIN, OUTPUT);
  digitalWrite(RESET_PIN, HIGH); // Assurer un état initial non réinitialisé

  // Initialisation de la communication série
  Serial.begin(9600);           // Moniteur série
  RN2483.begin(57600);          // Vitesse de communication du RN2483A
  
  Serial.println("Initialisation du module RN2483...");
  
  // Réinitialisation logicielle du module RN2483A
  resetModule();

  // Envoi d'une commande AT
  RN2483.println("sys get ver");
  delay(100);

  // Lecture de la réponse
  while (RN2483.available()) {
    String response = RN2483.readString();
    Serial.println("Réponse du RN2483: " + response);
  }
}

void loop() {
  // autre precision
}

void resetModule() {
  digitalWrite(RESET_PIN, LOW);
  delay(100); // Temps de réinitialisation
  digitalWrite(RESET_PIN, HIGH);
  delay(100); // Temps de stabilisation
}
