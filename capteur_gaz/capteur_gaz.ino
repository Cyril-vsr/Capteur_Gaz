#include <SoftwareSerial.h>

// Définition des broches pour SoftwareSerial
#define RX_PIN A1 // Broche où le TX du RN2483 est connecté
#define TX_PIN A0 // Broche où le RX du RN2483 est connecté
#define RESET_PIN 8 // Broche pour réinitialiser le RN2483

SoftwareSerial RN2483(TX_PIN, RX_PIN);

void setup() {
  pinMode(RESET_PIN, OUTPUT);
  digitalWrite(RESET_PIN, HIGH);

  // Initialisation de la communication série
  Serial.begin(9600);           // Moniteur série
  RN2483.begin(57600);          // Communication avec le RN2483

  Serial.println("Test RN2483");

  // Réinitialisation logicielle
  resetModule();

  // Vérification avec une commande basique
  testModule();
}

void loop() {
  // Rien à faire en boucle pour ce test
}

void resetModule() {
  Serial.println("Réinitialisation du module...");
  digitalWrite(RESET_PIN, LOW);
  delay(500);
  digitalWrite(RESET_PIN, HIGH);
  delay(1000);
  Serial.println("Module réinitialisé.");
}

void testModule() {
  Serial.println("Envoi de la commande 'sys get ver'...");
  RN2483.println("sys get hweui"); // Commande pour obtenir la version du firmware
  delay(1000);

  // Lecture de la réponse
  if (RN2483.available()) {
    Serial.println("Réponse reçue :");
    while (RN2483.available()) {
      char c = RN2483.read();
      Serial.print(c); // Affiche chaque caractère reçu
    }
    Serial.println();
  } else {
    Serial.println("Aucune réponse du RN2483.");
  }
}
