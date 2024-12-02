// Définir la broche analogique pour le signal du capteur
#define GAS_SENSOR_PIN A2

#define LED_PIN 12

void setup() {
  // Initialisation de la communication série
  Serial.begin(9600);
  Serial.println("Initialisation du capteur de gaz...");

  // Initialisation de la LED
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // Lire la valeur analogique du capteur
  int sensorValue = analogRead(GAS_SENSOR_PIN);

  // Convertir la valeur brute en tension (0 - 5V)
  float voltage = sensorValue * (3.3 / 1023.0);

  // Afficher les valeurs sur le moniteur série
  Serial.print("Valeur brute : ");
  Serial.print(sensorValue);
  Serial.print("\tTension (V) : ");
  Serial.println(voltage);

  // Définir une alerte si la concentration dépasse un seuil
  // Allumer la LED si la valeur brute dépasse 100
  if (sensorValue > 120) {
    digitalWrite(LED_PIN, HIGH);  // Allumer la LED
  } else {
    digitalWrite(LED_PIN, LOW);   // Éteindre la LED
  }

  delay(1000); // Pause de 1 seconde entre chaque lecture
}
