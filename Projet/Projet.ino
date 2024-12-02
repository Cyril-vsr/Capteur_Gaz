#include <TheThingsNetwork.h>
#include <TheThingsMessage.h>
#include <SoftwareSerial.h>

// Set your AppEUI and AppKey
const char *appEui = "BD6C7DC301108EE6";
const char *appKey = "77F85835964FC8C511F87CE864B96A6D";


// Utiliser un afficheur OLED 0.96" avec un Arduino Uno
// https://tutoduino.fr/
// Copyleft 2020
// Librairie pour l'afficheur OLED
// https://github.com/greiman/SSD1306Ascii
#include "SSD1306Ascii.h"
#include "SSD1306AsciiAvrI2c.h"
#define I2C_ADDRESS 0x3C
SSD1306AsciiAvrI2c oled;

SoftwareSerial loraSerial(10, 11); //TX, RX

#define debugSerial Serial

// Replace REPLACE_ME with TTN_FP_EU868 or TTN_FP_US915
#define freqPlan TTN_FP_EU868

#define GAZ_SENSOR_PIN A0
#define LED_PIN 4

TheThingsNetwork ttn(loraSerial, debugSerial, freqPlan);

devicedata_t data = api_DeviceData_init_default;

void setup()
{
  loraSerial.begin(57600);
  debugSerial.begin(57600);

  // Wait a maximum of 10s for Serial Monitor
  /*while (!debugSerial && millis() < 10000)
    ;

  debugSerial.println("-- STATUS");
  ttn.showStatus();

  debugSerial.println("-- JOIN");
  ttn.join(appEui, appKey);*/

  // Select what fields to include in the encoded message
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
  oled.println("Hello user1");

}

void loop()
{
  debugSerial.println("-- LOOP");

  /*// Gaz Sensor Read Value
  float sensor_volt;
  float sensorValue;

  sensorValue = analogRead(A0);
  sensor_volt = sensorValue/1024*5.0;

  Serial.print("sensor_volt = ");
  Serial.print(sensor_volt);
  Serial.println("V");*/

  // Read the sensors
  /*data.motion = true;
  data.water = 682;
  data.temperature_celcius = 30;
  data.temperature_fahrenheit = 86;
  data.humidity = 97;*/
  //byte humidity = 97;
  byte GAZ_VALUE = analogRead(GAZ_SENSOR_PIN);
  debugSerial.print("GAZ_VALUE : ");
  debugSerial.println(GAZ_VALUE);
  if (GAZ_VALUE >100){
    digitalWrite(LED_PIN,HIGH);
    oled.clearField(0,2,5);
    oled.println("HELP");
  }else {
    digitalWrite(LED_PIN,LOW);
    oled.clearField(0,2,5);
  }
  // Encode the selected fields of the struct as bytes
  /*byte *buffer;
  size_t size;
  TheThingsMessage::encodeDeviceData(&data, &buffer, &size);*/

  ttn.sendBytes(&GAZ_VALUE, 2);
  //ttn.sendBytes(buffer, size);

  delay(10000);
}