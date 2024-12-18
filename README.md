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

## Conclusion

This project allows you to receive LoRa sensor data, process it in Node-RED, and display it in real time on a chart. You can customize and extend this flow to add more features as needed (e.g., sending email or SMS alerts when critical gas levels are detected).
  
