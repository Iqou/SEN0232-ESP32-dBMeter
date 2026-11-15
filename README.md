# SEN0232 Sound dB Meter (ESP32 Implementation)

A cleaner, non-blocking, and ESP32-friendly `.ino` implementation for the **DFRobot Gravity SEN0232 Analog Sound Level Meter**.

---

## What is this repository?

This repository contains my `.ino` code for the DFRobot SEN0232 Analog Sound Level Meter to measure sound intensity in decibels (dB). While researching the sensor, I decided to share my own implementation since it's slightly different from the original datasheet example because they only assume a 5V reference.

The original example was designed for the Arduino Uno, so I made a few adjustments to make it more suitable for the ESP32 and much easier to integrate into larger projects or other microcontrollers. yeah.

### Key Adjustments & Improvements

- **Calibrated ESP32 ADC Readings:** Instead of manually calculating the voltage using `analogRead()` and a fixed 5V reference, this implementation uses `analogReadMilliVolts()` to obtain calibrated voltage readings supported by the ESP32 ADC. I also configured the ADC resolution to 12-bit and the attenuation to `ADC_11db` to properly accommodate the sensor's analog output.
- **Non-Blocking Timer:** Replaced the blocking `delay(125)` with a non-blocking `millis()` timer. This allows the sensor to be read periodically without unnecessarily stopping the rest of the program, making it way easier to integrate with other sensors, Wi-Fi, MQTT, or other background tasks.
- **Modular Structure:** Separated the sensor reading and serial output into individual functions, making the code easier to modify and reuse. The output is kept strictly numeric for straightforward plotting and data logging.

> **Note on Accuracy:** The goal isn't to make the sensor itself more accurate, but to provide a cleaner, reusable, and ESP32-friendly implementation that can be integrated into larger microcontroller projects with minimal modifications.

---

## How It Works & Hardware Setup

The SEN0232 is actually quite simple to set up and use. It relies on an analog input to measure sound intensity and converts it to decibels using a straightforward formula.

- **Hardware Used:** At the time I wrote this code, I tested it on an **Aurora LoRa V3** (a local board designed from an Indonesian company featuring an ESP32 microcontroller and a few built-in sensors. It's basically an Arduino x ESP32 hybrid).
- **Conversion Formula:** Since DFRobot has already handled A-weighting and calibration on the board itself, the formula used is a simple multiplication by 50 to convert the voltage value to decibels:

  <p align="center">$\text{dBA} = \text{Voltage (V)} \times 50$</p>

- **Real-World Testing:** The sensor still uses DFRobot's original conversion principle, so the measurement logic remains unchanged. I tested it side-by-side against an actual SPL meter and it's surprisingly accurate which is usually within $\pm 1\text{ dB}$, or even identical.

---

## Sensor Specifications

The Gravity SEN0232 Sound Level Meter is an electronic sensor module designed to measure sound intensity in decibels (dB).

| Parameter                | Specification                        |
| :----------------------- | :----------------------------------- |
| **Measuring Range**      | $30\text{ dBA} \sim 130\text{ dBA}$  |
| **Measurement Error**    | $\pm 1.5\text{ dB}$                  |
| **Frequency Weighted**   | A-Weighted                           |
| **Frequency Response**   | $31.5\text{ Hz} \sim 8.5\text{ kHz}$ |
| **Time Characteristics** | $125\text{ ms}$                      |
| **Input Voltage**        | $3.3\text{V} \sim 5.0\text{ V}$      |
| **Input Current**        | $22\text{mA} \sim 14\text{mA}$       |
| **Output Voltage**       | $0.6\text{V} \sim 2.6\text{ V}$      |
| **Module Size**          | $60\text{ mm} \times 43\text{ mm}$   |

---

## Handling Notes

> - **Protect the Microphone:** The film on the microphone is sensitive, so don't go around touching it with anything if possible.
> - **Prevent Short Circuits:** Don't place the module directly on conductive materials or surfaces as it may short the board. Hang it in the air or place it on an insulator instead.
