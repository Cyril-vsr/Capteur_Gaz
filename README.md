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
  <img src="https://github.com/user-attachments/assets/43ec4861-ff2c-4e94-a09d-cb6a87cde89f" alt="Image Description" width="400"/>
  <img src="https://github.com/user-attachments/assets/81cbb06b-d775-4b6a-95d6-926ad19fbc2a" alt="Image Description" width="400"/>
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


## Node-Red Overview

The Node-RED flow for this project is designed to receive, process, and display data from a LoRa sensor. The flow involves:

1) **Data Reception**: An MQTT node listens for incoming sensor data, typically from a LoRaWAN network like ChirpStack.
2) **Data Extraction**: A function node decodes the received Base64-encoded data and extracts the gas level value.
3) **Data Processing**: Another function node analyzes the gas level and triggers an alert if the value exceeds a set threshold (e.g., 200).
4) **Visualization**: A chart node displays the real-time gas levels in the Node-RED dashboard.

Flow Highlights:
- MQTT Node: Configured to receive sensor data from a LoRa network.
- Function Nodes: Process and filter the incoming data (e.g., extract, decode, and analyze gas levels).
- Chart Node: Displays the data in real-time on a graphical interface.

<div align="center">
  <img src="https://github.com/user-attachments/assets/3de43fe1-4f5c-4bce-88c6-673ff3560da8" alt="Image Description" width="800"/>
</div>

Key Parameters:
- MQTT broker configuration: Connects to the LoRa network.
- Threshold value: Set to 200 for triggering the alert.
- Dashboard: Accessible via http://127.0.0.1:1880/ui.
<div align="center">
  <img src="https://github.com/user-attachments/assets/666008f7-da93-44ea-abd9-14b4d441cbd3" alt="Image Description" width="300"/>
</div>

## MIT App Inventor

The MIT App Inventor app is designed to connect to the Arduino, allowing users to control the system and view sensor data in real-time.

Features:

1) **Connect to Arduino**: The app connects to the Arduino via Bluetooth when the user presses a connect button.
2) **Control LED**: Users can turn the LED on or off using buttons in the app.
3) **Gas Level Monitoring**: The app continuously receives the current gas level from the sensor and displays it.
4) **Real-time Updates**: Gas level data is updated in real-time on the app interface.

<div align="center">
  <img src="https://github.com/user-attachments/assets/4c98437b-c4e0-48fe-a503-19426bd9d05f" alt="Image Description" width="300"/>
  <img src="https://github.com/user-attachments/assets/238ae7ba-5674-4854-991c-d3379a41183a" alt="Image Description" width="300"/>
</div>

Key Components:
- Connect Button: Establishes communication with the Arduino.
- LED Control Buttons: Turns the LED on and off.
- Label: Displays the current gas level.
- Notifier: Alerts the user if the gas level exceeds a predefined threshold.
  
This app provides simple, real-time interaction with the Arduino system, enabling both control and monitoring of environmental conditions.






# Node-Red
## Introduction

This Node-RED project is designed to receive, process, and display data from a LoRa sensor. It includes several nodes to interact with a LoRa network, decode received data, analyze it, and generate alerts when the gas level is high. The user interface allows real-time visualization of this data in a chart.

## Prerequisites

Before starting, make sure you have installed the following:
- Node.js (version 14.x or higher)
- npm (which comes with Node.js)
- Access to: https://srv-chirpstack.insa-toulouse.fr/

## Installation

Follow these steps to install Node-Red: 

https://nodered.org/docs/getting-started/local

## Connexion

- In your terminal launch: $node-red 
- Open http://127.0.0.1:1880/ to have the project view

## Project Bloc Structure

- mqtt in which receive Lora data
- Function 1 that extract data
- Function 2 that treat the data if >200 then Help message
- Chart available at the address http://127.0.0.1:1880/ui

  <img width="340" alt="image" src="https://github.com/user-attachments/assets/d94da382-be66-40f6-ab8e-efef396b91e3" />


## Conclusion

This project allows you to receive LoRa sensor data, process it in Node-RED, and display it in real time on a chart. You can customize and extend this flow to add more features as needed (e.g., sending email or SMS alerts when critical gas levels are detected).
  
