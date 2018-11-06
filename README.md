# codal-stm32-iot-node

Codal target for the [B-L475E-IOT01A](http://www.st.com/en/evaluation-tools/b-l475e-iot01a.html) Discovery kit for IoT node. Codal is the core set of drivers, mechanisms and types that make up the runtime for a board in Makecode.

## Overview

The codal runtime provides an easy to use environment for programming the board in the C/C++ language, written by Lancaster University. It contains device drivers for all the hardware capabilities, and also a suite of runtime mechanisms to make programming the easier and more flexible. These range from control of the LED matrix display to peer-to-peer radio communication and secure Bluetooth Low Energy services.

Codal-core must be implemented by third party developper to support new hardware target. This repository constain the codal implementation for the [B-L475E-IOT01A](http://www.st.com/en/evaluation-tools/b-l475e-iot01a.html) Discovery kit for IoT node.

## Board Information  

The [B-L475E-IOT01A](http://www.st.com/en/evaluation-tools/b-l475e-iot01a.html) Discovery kit for IoT node allows users to develop applications with direct connection to cloud servers.

The Discovery kit enables a wide diversity of applications by exploiting low-power communication, multiway sensing and Arm® Cortex® -M4 core-based STM32L4 Series features.

The support for Arduino Uno V3 and PMOD connectivity provides unlimited expansion capabilities with a large choice of specialized add-on boards.

<img src="https://pxt.azureedge.net/blob/7490df2fec08171c631b815eac97dae0dae5a8a0//static/boards/stm32-iot-node/board.simplified.svg" width="600px" />

## Feature List (and if implemented in codal)

- [x] 64-Mbit Quad-SPI (Macronix) Flash memory
- [x] Bluetooth® V4.1 module (SPBTLE-RF)
- [ ] Sub-GHz (868 or 915 MHz) low-power-programmable RF module (SPSGRF-868 or SPSGRF-915)
- [ ] Wi-Fi® module Inventek ISM43362-M3G-L44 (802.11 b/g/n compliant)
- [ ] Dynamic NFC tag based on M24SR with its printed NFC antenna
- [ ] 2 digital omnidirectional microphones (MP34DT01)
- [ ] USB OTG FS
- [x] Capacitive digital sensor for relative humidity and temperature (HTS221)
- [x] High-performance 3-axis magnetometer (LIS3MDL)
- [x] 3D accelerometer and 3D gyroscope (LSM6DSL)
  - [x] 3D Accelerometer (Complete)
  - [x] 3D Gyroscope (Complete)
  - [x] Temperature (Complete)
- [x] 260-1260 hPa absolute digital output barometer (LPS22HB)
- [x] Time-of-Flight and gesture-detection sensor (VL53L0X)
- [x] 2 push-buttons (user and reset)
- [x] GPIO
- [x] ADC 12 bits
- [~] FAT Storage over the flash memory
- [~] Expansion connectors:
  - [x] Arduino™ Uno V3
  - [ ] PMOD