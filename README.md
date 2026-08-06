# MKE_I2C_MotorDriver

Arduino library for MakerEdu **MKE-M17** (L9110) and **MKE-M18** (BD62130) I2C Dual DC Motor Drivers.

## Features
- Control 2 DC motors (A & B) with direction (CW/CCW), speed (0–255), and optional duration (ms).
- Adjust PWM frequency (500Hz – 2000Hz).
- Direct raw PWM control on channels MA1, MA2, MB1, and MB2.
- Read power supply input voltage (`getVin()`).
- Dynamic I2C address modification saved into EEPROM.

## Hardware Compatibility
- MKE-M17 (L9110 I2C Driver Module)
- MKE-M18 (BD62130 I2C Driver Module)
- Compatible with standard Arduino microcontrollers (UNO, Mega, ESP32, ESP8266, RP2040).

## Installation
1. Download the ZIP file of this repository.
2. Open Arduino IDE and select **Sketch > Include Library > Add .ZIP Library...**.
3. Select the downloaded ZIP file.

## Quick Start Example

```cpp
#include <Arduino.h>
#include <Wire.h>
#include <MKE_I2C_MotorDriver.h>

MKE_I2C_MotorDriver motor;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  // Initialize motor driver with default address (0x40)
  motor.begin();

  // Set PWM Frequency to 1000 Hz
  motor.setPwmFrequency(1000);
}

void loop() {
  // Read Vin Voltage in mV
  uint32_t vin = motor.getVin();
  Serial.print("Vin Voltage: ");
  Serial.print(vin);
  Serial.println(" mV");

  // Motor A forward at speed 200 for 2000ms (2 seconds)
  motor.motorA_CW(200, 2000);
  
  // Motor B reverse at speed 150 continuously
  motor.motorB_CCW(150);

  delay(3000);

  // Stop all motors
  motor.stopAll();
  delay(2000);
}
```