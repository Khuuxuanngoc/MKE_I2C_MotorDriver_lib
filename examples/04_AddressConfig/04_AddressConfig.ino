/*
 * Example 04: I2C Address Configuration
 *
 * Allows connecting multiple MakerEdu I2C Motor Driver modules to the same I2C
 * bus. Default Address: 0x40 (64). Valid Range: 0x01 to 0x7E (1 to 126).
 *
 * Note: The new address is permanently saved to on-board EEPROM and takes
 * effect immediately. Factory Reset: Press and hold the on-board push button
 * for 3 seconds to restore 0x40.
 */

#include <MKE_I2C_MotorDriver.h>
#include <Wire.h>

// Connect to module currently at default address 0x40
MKE_I2C_MotorDriver motorDriver;

void setup() {
  Serial.begin(9600);
  Wire.begin();            // Initialize I2C Bus on Master
  motorDriver.begin(0x40); // Bind to current address 0x40
  Serial.println(F("MakerEdu I2C Motor Driver - Address Configuration"));
  delay(1500);

  // --- Read module information ---
  Serial.print(F("Module ID      : "));
  Serial.println(motorDriver.getModuleId());
  Serial.print(F("Firmware Ver.  : "));
  Serial.println(motorDriver.getFirmwareVersion());
  Serial.print(F("Current Address: 0x"));
  Serial.println(motorDriver.getAddress(), HEX);

  // --- Change I2C address from 0x40 to 0x41 ---
  Serial.println(F("\nChanging I2C address to 0x41..."));
  motorDriver.setAddress(0x41); // Save new address to EEPROM

  // The motorDriver object automatically updates its target address to 0x41
  Serial.print(F("New Address    : 0x"));
  Serial.println(motorDriver.getAddress(), HEX);
  Serial.println(F("Done! Use address 0x41 in your subsequent sketches."));
}

void loop() {
  // Idle
}
