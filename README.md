# 🏠 Smart Home Controller using ESP32

An ESP32-based smart home automation system that integrates automatic lighting, temperature-based fan control, motion detection, security monitoring, and real-time OLED display.

---

## 📌 Overview

The **Smart Home Controller** is an embedded systems project designed to demonstrate basic home automation using an ESP32 microcontroller.

The system continuously monitors the environment using an **LDR, PIR sensor, and DHT22 sensor**. Based on the sensor readings, the ESP32 automatically controls lighting and fan operation.

A dedicated security system can be **armed or disarmed using a push button**. When the security system is armed and motion is detected, a security LED and buzzer are activated.

An **SSD1306 OLED display** provides real-time information about the system.

The complete system was developed and tested using the **Wokwi ESP32 simulator**.

---

## ✨ Features

- 💡 Automatic lighting based on light intensity and motion
- 👤 PIR-based motion detection
- 🌡️ Temperature monitoring using DHT22
- 💧 Humidity monitoring using DHT22
- 🌀 Automatic fan control based on temperature
- 🔐 Security system with ARM/DISARM control
- 🚨 Motion-triggered security alarm
- 🔴 Security LED indication
- 🔊 Buzzer alarm
- 📺 Real-time OLED dashboard
- 🖥️ Serial Monitor system information
- 🚀 OLED startup screen
- 🔄 Automatic OLED status page switching

---

## 🧰 Hardware Components

| Component | Quantity | Purpose |
|---|---:|---|
| ESP32 | 1 | Main microcontroller |
| LDR / Photoresistor | 1 | Light intensity detection |
| PIR Motion Sensor | 1 | Motion detection |
| DHT22 | 1 | Temperature and humidity sensing |
| LED | 1 | Automatic lighting |
| LED | 1 | Fan status indication |
| LED | 1 | Security indication |
| Push Button | 1 | Security ARM/DISARM |
| Buzzer | 1 | Security alarm |
| SSD1306 OLED 128×64 | 1 | System status display |

---

## 🔌 Pin Configuration

| Component | ESP32 Pin |
|---|---:|
| PIR Sensor | GPIO 13 |
| LDR | GPIO 34 |
| Light LED | GPIO 26 |
| DHT22 | GPIO 14 |
| Fan LED | GPIO 25 |
| Security LED | GPIO 27 |
| Buzzer | GPIO 33 |
| Security Button | GPIO 4 |
| OLED SDA | GPIO 21 |
| OLED SCL | GPIO 22 |

---

## ⚙️ System Architecture

```text
                         SMART HOME CONTROLLER
                                  │
                                  ▼
                              ESP32
                                  │
              ┌───────────────────┼───────────────────┐
              │                   │                   │
              ▼                   ▼                   ▼
           Sensors             Control            Security
              │                   │                   │
      ┌───────┼───────┐           │              ┌────┴────┐
      │       │       │           │              │         │
     LDR     PIR    DHT22         │           Button     PIR
      │       │       │           │              │         │
      └───────┴───────┴───────────┘              │         │
              │                                   │         │
              ▼                                   ▼         ▼
           ESP32                              ARM/DISARM  Alarm
              │                                             │
       ┌──────┼──────────────┐                       ┌──────┴──────┐
       │      │              │                       │             │
       ▼      ▼              ▼                       ▼             ▼
     Light   Fan          OLED Display          Security LED    Buzzer
💡 Automatic Lighting

The LDR is used to monitor the surrounding light intensity, while the PIR sensor detects motion.

When the environment is dark and motion is detected, the ESP32 turns the light ON.

Logic
Dark + Motion Detected
          ↓
        ESP32
          ↓
       Light ON

If there is no motion or the environment is bright, the light remains OFF.
🌀 Automatic Fan Control

The DHT22 sensor measures the temperature.

The fan is controlled using two temperature thresholds:

Temperature ≥ 30°C
        ↓
     Fan ON
Temperature ≤ 28°C
        ↓
     Fan OFF

The difference between the ON and OFF thresholds helps prevent rapid switching when the temperature is close to the threshold.

🚨 Security System

The security system can be controlled using a push button.

Security States
Button Press
     ↓
 ┌───────────────┐
 │               │
 ▼               ▼
ARMED          DISARMED

When the system is ARMED and motion is detected:

Security ARMED
       +
Motion Detected
       ↓
 ┌─────┴─────┐
 ▼           ▼
LED ON     Buzzer ON
       ↓
     ALARM

When the security system is DISARMED, motion does not activate the alarm.

📺 OLED Display

The system uses an SSD1306 128×64 I2C OLED display to provide real-time system information.

The display automatically switches between two pages.

Page 1
SMART HOME
----------------
Temp : 28.5 C
Hum  : 52 %
Light: ON
Motion: YES
Page 2
SMART HOME
----------------
Fan     : OFF
Security: ARMED
Alarm   : OFF
System  : OK

The OLED also displays a startup screen when the ESP32 begins operation.

SMART
HOME


SYSTEM READY
🖥️ Serial Monitor

The Serial Monitor provides detailed information about the current system state.

Example:

------------------------------------------
Temperature : 28.5 C
Humidity    : 52 %
LDR         : 850
Motion      : DETECTED
Light       : ON
Fan         : OFF
Security    : ARMED
Alarm       : ON
------------------------------------------
🧪 Testing and Results

The complete system was tested under different operating conditions.

Test	Condition	Expected Result	Result
1	Bright + No Motion	Light OFF	✅ Passed
2	Dark + Motion	Light ON	✅ Passed
3	Temperature ≥ 30°C	Fan ON	✅ Passed
4	Temperature ≤ 28°C	Fan OFF	✅ Passed
5	Security DISARMED + Motion	Alarm OFF	✅ Passed
6	Security ARMED + Motion	Alarm ON	✅ Passed
7	OLED Display	System information displayed	✅ Passed
8	Startup	System Ready displayed	✅ Passed
🛠️ Software and Tools
C/C++
ESP32
Wokwi Simulator
Arduino-compatible development environment
DHT Library
Adafruit GFX Library
Adafruit SSD1306 Library

▶️ Simulation

The project can be simulated online using Wokwi.

🔗 Wokwi Project

Open Smart Home Controller Simulation

The simulation demonstrates the complete functionality of the system without requiring physical hardware.

🎯 Project Objectives

The main objectives of this project are:

To understand ESP32-based embedded system development.
To integrate multiple sensors with a microcontroller.
To implement automatic appliance control.
To develop a basic security monitoring system.
To display real-time sensor and system information.
To understand the integration of sensors, actuators, and user interfaces.
To design and test a complete smart home prototype using simulation.
🚀 Future Improvements

The system can be further enhanced by adding:

📱 Mobile application control
🌐 IoT/cloud connectivity
📊 Web-based monitoring dashboard
🔔 Remote security notifications
🏠 Control of additional home appliances
⚡ Energy consumption monitoring
🤖 AI-based automation and prediction
📡 Remote sensor monitoring
📚 Learning Outcomes

Through this project, the following concepts were practiced:

ESP32 programming
Embedded C/C++ programming
Digital and analog sensor interfacing
GPIO control
Sensor-based automation
Temperature-based control logic
Security system implementation
OLED/I2C communication
Serial communication
Embedded system simulation
Hardware-software integration
👩‍💻 Author

Devika KS

B.Tech – Computer Science with Data Science

⭐ Acknowledgement

This project was developed as an embedded systems project using the ESP32 and tested using the Wokwi online simulation platform.

⭐ If you found this project useful, consider giving the repository a star!
