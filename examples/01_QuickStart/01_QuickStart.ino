/*
 * Example 01: Quick Start - Basic Motor A and Motor B Control
 * 
 * Hardware:
 *   - Arduino Uno/Mega/ESP32 (Master)
 *   - MakerEdu I2C Dual DC Motor Driver Module
 *   - SDA --> A4 (Uno) or SDA (Mega/ESP32)
 *   - SCL --> A5 (Uno) or SCL (Mega/ESP32)
 *   - External power supply 6V-12V connected to Vin
 */

#include <MKE_I2C_MotorDriver.h>
#include <Wire.h>

MKE_I2C_MotorDriver motorDriver;

void setup() {
  Serial.begin(9600);
  Wire.begin();        // Initialize I2C Bus on Master
  motorDriver.begin(); // Bind to default address 0x40 (64)
  Serial.println(F("MakerEdu I2C Motor Driver - Quick Start"));
  delay(500);
}

void loop() {
  Serial.println(F("Motor A: Forward 50% speed..."));
  motorDriver.motorA_CW(127); // Motor A Clockwise at 50% speed
  delay(2000);

  Serial.println(F("Motor A: Forward 100% speed..."));
  motorDriver.motorA_CW(255); // Motor A Clockwise at 100% speed
  delay(2000);

  Serial.println(F("Motor A: Stop"));
  motorDriver.stopMotorA();
  delay(1000);

  Serial.println(F("Motor A: Backward 50% speed..."));
  motorDriver.motorA_CCW(127); // Motor A Counter-Clockwise at 50% speed
  delay(2000);

  Serial.println(F("Motor B: Forward 100% + Motor A: Backward 100%..."));
  motorDriver.motorA_CCW(255);
  motorDriver.motorB_CW(255);
  delay(2000);

  Serial.println(F("All Motors Stop!"));
  motorDriver.stopAll(); // Stop both motors
  delay(3000);
}
