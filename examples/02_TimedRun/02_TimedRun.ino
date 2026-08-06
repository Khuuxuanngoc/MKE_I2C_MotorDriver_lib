/*
 * Example 02: Timed Run & Watchdog Safety Demo
 * 
 * Features:
 *   - Auto-stop timeout: The motor automatically stops after a preset duration
 *     without requiring an explicit stop command from the Master.
 *   - PID Watchdog keep-alive: If the Master crashes or connection is lost,
 *     the motor automatically stops safely after the duration expires.
 */

#include <MKE_I2C_MotorDriver.h>
#include <Wire.h>

MKE_I2C_MotorDriver motorDriver;

void setup() {
  Serial.begin(9600);
  Wire.begin();        // Initialize I2C Bus on Master
  motorDriver.begin(); // Bind to default address 0x40 (64)
  Serial.println(F("MakerEdu I2C Motor Driver - Timed Run Demo"));
  delay(500);
}

void loop() {
  // 1. Motor B backward at speed 200, auto-stops after 3000 ms (3 seconds)
  Serial.println(F("Motor B: Backward (speed=200), auto-stop after 3s..."));
  motorDriver.motorB_CCW(200, 3000); // speed=200, duration_ms=3000
  delay(5000);                       // Master waits 5s before next action

  // 2. Motor A forward at speed 127, auto-stops after 1500 ms (1.5 seconds)
  Serial.println(F("Motor A: Forward (speed=127), auto-stop after 1.5s..."));
  motorDriver.motorA_CW(127, 1500);  // speed=127, duration_ms=1500
  delay(4000);

  // 3. PID Watchdog / Keep-alive Demo
  // Send PID command every 100ms with duration=200ms
  // If Master hangs or wires disconnect, motor safely stops after 200ms.
  Serial.println(F("PID Watchdog demo: streaming 10 commands at 100ms interval..."));
  for (int i = 0; i < 10; i++) {
    int pidOutput = 180 + random(-10, 10); // Simulated PID output
    motorDriver.motorA_CW(pidOutput, 200); // duration=200ms > interval=100ms
    delay(100);
  }

  Serial.println(F("Watchdog stream finished. Stopping motors."));
  motorDriver.stopAll();
  delay(3000);
}
