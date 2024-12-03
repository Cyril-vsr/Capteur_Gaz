# ISS 2024/2025: Gas Sensor AIME

## Introduction

This project involves designing and implementing a smart gas sensor. Starting with its fabrication at the AIME laboratory, the project extended to integrating the sensor with an Arduino UNO and LoRa module for wireless communication.

The objective was to create a system capable of detecting gas, processing the data, and transmitting it to a remote dashboard via LoRaWAN. This project helped us gain hands-on experience in electronics, programming, and networking.

## Gas Sensor

The gas sensor was fabricated during a training period at AIME. It uses [material, e.g., nanoparticles of WO3], which allows for high sensitivity to specific gases like [e.g., ethanol, ammonia].

The sensor includes:

- **Sensitive layer**: Nanoparticles deposited on interdigitated aluminum combs.
  
- **Heating element**: A polysilicon resistor to adjust operating temperature.
  
- **Calibration zone**: An area without nanoparticles for baseline measurements.

| **Pin Number** | **Description**                       |
|----------------|---------------------------------------|
| 2, 4           | Sensitive layer (with nanoparticles) |
| 3, 6           | Heating element                      |
| 5, 10          | Temperature sensor                   |
| 7, 9           | Calibration layer                    |
| 1, 8           | Not used                             |


## Wiring

To create a functional system, we wired the following components:

- **Arduino UNO**: Central microcontroller for the system.
- **LoRa Module (RN2483)**: For wireless communication.
- **Gas Sensor**: To detect gas concentrations.

 The connections were as follows:

- **Gas sensor**: Connected to the analog pin A0 on the Arduino.
- **LoRa module**: TX and RX connected to pins 10 and 11 on the Arduino.
- **Power**: Arduino powered via USB, LoRa module powered through the 3.3V pin.

<div align="center">
  <img src="https://github.com/user-attachments/assets/43ec4861-ff2c-4e94-a09d-cb6a87cde89f" alt="Image Description" width="500"/>
</div>


## Arduino Code

The Arduino code consists of two parts:

1) **Initialization**: Retrieve and configure the LoRa module with its EUI for registration in the LoRaWAN network (via ChirpStack).
2) **Data Transmission**: Read gas sensor values, process the data, and send it via LoRa.

**Code Highlights**

The setup() function initializes the LoRa module and the gas sensor.
The loop() function reads the sensor data, encodes it, and transmits it using the sendBytes() function.

**Configuration Parameters:**

- AppEUI: Configured for LoRaWAN registration.
- AppKey: Security key for LoRaWAN.
- Sensor Pin: Pin A0 for the gas sensor.
- LoRa TX/RX: Pins 10 and 11 for communication.
