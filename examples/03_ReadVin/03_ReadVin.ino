/*
 * Example 03: Reading Supply Voltage (Vin Monitoring)
 * 
 * The MakerEdu I2C Motor Driver features an on-board ADC voltage divider (10kΩ/1kΩ)
 * to measure the external motor supply voltage (Vin).
 * 
 * Return Value: Voltage in milli-volts (mV).
 * Example: 8400 mV = 8.40 Volts.
 */

#include <MKE_I2C_MotorDriver.h>
#include <Wire.h>

MKE_I2C_MotorDriver motorDriver;

void setup() {
  Serial.begin(9600);
  Wire.begin();        // Initialize I2C Bus on Master
  motorDriver.begin(); // Bind to default address 0x40 (64)
  Serial.println(F("MakerEdu I2C Motor Driver - Read Vin Demo"));
  Serial.println(F("Monitoring battery/power voltage every 1 second..."));
  delay(500);
}

void loop() {
  uint32_t vin_mV = motorDriver.getVin();

  // Print results
  Serial.print(F("Vin: "));
  Serial.print(vin_mV);
  Serial.print(F(" mV  (~"));
  Serial.print(vin_mV / 1000.0, 2); // Convert to Volts (2 decimal places)
  Serial.print(F(" V)"));

  // Battery low-voltage alert (e.g., 2S Li-ion battery below 6.5V)
  if (vin_mV > 0 && vin_mV < 6500) {
    Serial.print(F("  [WARNING: Low Battery!]"));
  }
  Serial.println();

  delay(1000);
}
