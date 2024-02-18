# Smart Glow - Automatic Street Lights System with NodeMCU ESP8266

Smart Glow is an IoT-based street lights control system using NodeMCU ESP8266. It allows users to control street lights automatically or manually through an Android application. The system incorporates a NodeMCU ESP8266 microcontroller, a Light Dependent Resistor (LDR) for ambient light sensing, a Passive Infrared (PIR) sensor for human presence detection, and an LED for street lighting.

## Features

- Automatic mode for intelligent street light control based on ambient light and human presence.
- Manual mode for manual control of LEDs via the Android app.
- Real-time status display in the Android app:
  - Mode status (Automatic/Manual).
  - Day/Night status based on LDR readings.
  - LED status based on PIR sensor and user control.
- Integration with Google Firebase Realtime Database for data logging.

## Hardware Setup

1. Connect LDR to analog pin A0 for light sensing.
2. Connect PIR sensor to digital pin D2 for human presence detection.
3. Connect LED to digital pin D1 for street lighting.

## Arduino Code Setup

1. Install the Arduino IDE and required libraries.
2. Open the Arduino IDE and upload the provided `SmartGlow_ESP8266.ino` sketch to your NodeMCU ESP8266.

## Android App

1. Install the "Smart Glow" Android app on your device.
2. Launch the app and connect it to your NodeMCU ESP8266.
3. Choose between Automatic and Manual modes.


## Usage

- In Automatic mode:
  - LDR senses ambient light and updates day/night status in the Firebase Realtime Database.
  - PIR sensor detects human presence and turns on the LED when it's night.
- In Manual mode:
  - User controls LED state through the Android app.

## Dependencies

- NodeMCU ESP8266
- Arduino IDE
- "Smart Glow" Android app
- Google Firebase Realtime Database

## Contact

For any inquiries or issues, please contact Sunil Kanaki at sunilkanaki17@gmail.com.
