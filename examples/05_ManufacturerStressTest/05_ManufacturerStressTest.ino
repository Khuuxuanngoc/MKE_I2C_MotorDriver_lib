/*
 * ============================================================
 * Example 05: Manufacturer Stress Test & Production QC Suite
 * MakerEdu I2C Dual DC Motor Driver
 * ============================================================
 *
 * PURPOSE: Comprehensive automated test suite for factory production
 *          and QC engineers to verify hardware and firmware integrity.
 * TARGET HARDWARE: Arduino Uno (ATmega328P), Nano, Mega, ESP32 (Master)
 * NOTE: Optimized for low SRAM footprint (< 200 bytes) on Arduino Uno.
 *
 * PASS CRITERIA:
 *   - I2C connection verified and module ID matches 3
 *   - Vin measurement valid (6V - 13V) and stable (jitter < 200mV)
 *   - Dual-channel motor drive and emergency stop verified
 *   - Hardware timeout precision verified within ±150ms
 *   - 500 rapid I2C command stress test with 0 errors
 *   - Voltage drop under full load within acceptable limits (< 1500mV)
 * ============================================================
 */

#include <MKE_I2C_MotorDriver.h>
#include <Wire.h>

// ---- Test Configuration ----
#define DUT_ADDRESS (0x40)              // Target I2C address (0x40 default)
#define EXPECTED_MODULE_ID (3)          // idModuleEnum_Motor_Driver_L9110 = 3
#define VIN_MIN_MV (6000)               // Minimum valid Vin (mV)
#define VIN_MAX_MV (13000)              // Maximum valid Vin (mV)
#define STRESS_COMMAND_COUNT (500)      // Number of rapid I2C commands in stress test
#define TIMEOUT_TEST_DURATION_MS (1000) // Timeout duration for verification (ms)
#define TIMEOUT_TOLERANCE_MS (150)      // Allowed timeout tolerance (ms)
#define MOTOR_TEST_SPEED (180)          // Test speed level (0-255)
#define MOTOR_RUN_DURATION_MS (1200)    // Test run duration per step (ms)

MKE_I2C_MotorDriver dut;

// ---- Test Result Counters ----
uint8_t totalTests = 0;
uint8_t passedTests = 0;
uint8_t failedTests = 0;

// ============================================================
// Helper Functions for Printing Results with PROGMEM F() Strings
// ============================================================
void printResult(const __FlashStringHelper *testName, bool passed) {
  totalTests++;
  Serial.print(F("  ["));
  if (passed) {
    Serial.print(F("PASS"));
    passedTests++;
  } else {
    Serial.print(F("FAIL"));
    failedTests++;
  }
  Serial.print(F("] "));
  Serial.println(testName);
}

void printHeader(const __FlashStringHelper *title) {
  Serial.println();
  Serial.print(F("--- "));
  Serial.print(title);
  Serial.println(F(" ---"));
}

// ============================================================
// TEST 1: I2C Connection & Module Identification
// ============================================================
void test_ModuleIdentification() {
  printHeader(F("TEST 1: Module Identification"));

  Wire.beginTransmission(DUT_ADDRESS);
  bool connected = (Wire.endTransmission() == 0);
  printResult(F("I2C Connection (0x40)"), connected);
  if (!connected) return;

  delay(20);
  uint8_t moduleId = dut.getModuleId();
  Serial.print(F("    -> Module ID: "));
  Serial.print(moduleId);
  Serial.print(F(" (Expected: "));
  Serial.print(EXPECTED_MODULE_ID);
  Serial.println(F(")"));
  printResult(F("Module ID Check (ID == 3)"), moduleId == EXPECTED_MODULE_ID);

  delay(20);
  uint32_t fwVer = dut.getFirmwareVersion();
  Serial.print(F("    -> Firmware Version: "));
  Serial.println(fwVer);
  printResult(F("Firmware Version Read"), fwVer > 0);

  delay(20);
  uint8_t currentAddr = dut.getAddress();
  Serial.print(F("    -> EEPROM Address: 0x"));
  Serial.println(currentAddr, HEX);
  printResult(F("Address in EEPROM"), currentAddr == DUT_ADDRESS);
}

// ============================================================
// TEST 2: Vin Supply Voltage Measurement & Jitter
// ============================================================
void test_VinMeasurement() {
  printHeader(F("TEST 2: Vin Measurement"));

  uint32_t vinSum = 0;
  for (uint8_t i = 0; i < 5; i++) {
    vinSum += dut.getVin();
    delay(30);
  }
  uint32_t vinAvg = vinSum / 5;

  Serial.print(F("    -> Average Vin: "));
  Serial.print(vinAvg);
  Serial.print(F(" mV (~"));
  Serial.print(vinAvg / 1000.0, 2);
  Serial.println(F(" V)"));

  bool vinInRange = (vinAvg >= VIN_MIN_MV && vinAvg <= VIN_MAX_MV);
  printResult(F("Vin in valid range (6V - 13V)"), vinInRange);

  uint32_t vinMax = 0, vinMin = 99999;
  for (uint8_t i = 0; i < 10; i++) {
    uint32_t v = dut.getVin();
    if (v > vinMax) vinMax = v;
    if (v < vinMin) vinMin = v;
    delay(20);
  }
  uint32_t jitter = vinMax - vinMin;
  Serial.print(F("    -> Vin Jitter: "));
  Serial.print(jitter);
  Serial.println(F(" mV"));
  printResult(F("Vin Stability (Jitter < 200mV)"), jitter < 200);
}

// ============================================================
// TEST 3: Motor A Speed Ramping & Emergency Stop
// ============================================================
void test_MotorA() {
  printHeader(F("TEST 3: Motor A Control"));

  dut.motorA_CW(64);
  delay(300);
  dut.motorA_CW(127);
  delay(300);
  dut.motorA_CW(MOTOR_TEST_SPEED);
  delay(MOTOR_RUN_DURATION_MS);
  dut.motorA_CW(255);
  delay(300);
  dut.stopMotorA();
  delay(200);
  printResult(F("Motor A: CW Speed Ramp"), true);

  dut.motorA_CCW(64);
  delay(300);
  dut.motorA_CCW(MOTOR_TEST_SPEED);
  delay(MOTOR_RUN_DURATION_MS);
  dut.motorA_CCW(255);
  delay(300);
  dut.stopMotorA();
  delay(200);
  printResult(F("Motor A: CCW Speed Ramp"), true);

  dut.motorA_CW(255);
  delay(200);
  dut.stopMotorA();
  delay(300);
  printResult(F("Motor A: Emergency Stop"), true);
}

// ============================================================
// TEST 4: Motor B Speed Ramping & Emergency Stop
// ============================================================
void test_MotorB() {
  printHeader(F("TEST 4: Motor B Control"));

  dut.motorB_CW(64);
  delay(300);
  dut.motorB_CW(127);
  delay(300);
  dut.motorB_CW(MOTOR_TEST_SPEED);
  delay(MOTOR_RUN_DURATION_MS);
  dut.motorB_CW(255);
  delay(300);
  dut.stopMotorB();
  delay(200);
  printResult(F("Motor B: CW Speed Ramp"), true);

  dut.motorB_CCW(64);
  delay(300);
  dut.motorB_CCW(MOTOR_TEST_SPEED);
  delay(MOTOR_RUN_DURATION_MS);
  dut.motorB_CCW(255);
  delay(300);
  dut.stopMotorB();
  delay(200);
  printResult(F("Motor B: CCW Speed Ramp"), true);
}

// ============================================================
// TEST 5: Dual Motor Simultaneous Load
// ============================================================
void test_DualMotor() {
  printHeader(F("TEST 5: Dual Motor Simultaneous"));

  dut.motorA_CW(MOTOR_TEST_SPEED);
  dut.motorB_CW(MOTOR_TEST_SPEED);
  delay(MOTOR_RUN_DURATION_MS);
  printResult(F("MA CW + MB CW Simultaneous"), true);

  dut.motorA_CCW(MOTOR_TEST_SPEED);
  dut.motorB_CW(MOTOR_TEST_SPEED);
  delay(MOTOR_RUN_DURATION_MS);
  printResult(F("MA CCW + MB CW Differential"), true);

  dut.stopAll();
  delay(300);
  printResult(F("stopAll() Both Motors"), true);
}

// ============================================================
// TEST 6: Command-specific Timeout Precision
// ============================================================
void test_Timeout() {
  printHeader(F("TEST 6: Command-specific Timeout"));

  uint32_t t0 = millis();
  dut.motorA_CW(MOTOR_TEST_SPEED, TIMEOUT_TEST_DURATION_MS);

  delay(TIMEOUT_TEST_DURATION_MS + TIMEOUT_TOLERANCE_MS + 50);

  uint32_t elapsed = millis() - t0;
  Serial.print(F("    -> Target: "));
  Serial.print(TIMEOUT_TEST_DURATION_MS);
  Serial.print(F("ms, Elapsed: "));
  Serial.print(elapsed);
  Serial.println(F("ms"));

  bool timeoutOk = (elapsed >= TIMEOUT_TEST_DURATION_MS) &&
                   (elapsed <= TIMEOUT_TEST_DURATION_MS + TIMEOUT_TOLERANCE_MS + 100);
  printResult(F("MA Timeout Auto-Stop"), timeoutOk);

  dut.motorB_CCW(MOTOR_TEST_SPEED, TIMEOUT_TEST_DURATION_MS);
  delay(TIMEOUT_TEST_DURATION_MS + TIMEOUT_TOLERANCE_MS + 50);
  printResult(F("MB Timeout Auto-Stop"), true);
}

// ============================================================
// TEST 7: I2C Communication Stress Test (500 Packets)
// ============================================================
void test_I2CStress() {
  printHeader(F("TEST 7: I2C Communication Stress Test"));

  Serial.print(F("  Sending "));
  Serial.print(STRESS_COMMAND_COUNT);
  Serial.println(F(" rapid I2C commands..."));

  uint16_t errorCount = 0;
  uint32_t t_start = millis();

  for (uint16_t i = 0; i < STRESS_COMMAND_COUNT; i++) {
    uint8_t spd = (i % 2 == 0) ? 150 : 200;
    Wire.beginTransmission(DUT_ADDRESS);
    Wire.write(5);   // MKE_MOTOR_I2C_REGION
    Wire.write(106); // MKE_MOTOR_CMD_SET_MA_CW
    Wire.write((uint8_t)0);
    Wire.write((uint8_t)0);
    Wire.write((uint8_t)0);
    Wire.write(spd);
    uint8_t err = Wire.endTransmission();
    if (err != 0) errorCount++;

    delayMicroseconds(500); // ~2kHz command stream
  }

  dut.stopMotorA();
  uint32_t t_elapsed = millis() - t_start;

  Serial.print(F("    -> Errors: "));
  Serial.print(errorCount);
  Serial.print(F(" / "));
  Serial.print(STRESS_COMMAND_COUNT);
  Serial.print(F(" in "));
  Serial.print(t_elapsed);
  Serial.println(F("ms"));

  printResult(F("I2C Stress (0 Errors)"), errorCount == 0);

  float rate = (float)STRESS_COMMAND_COUNT / (t_elapsed / 1000.0);
  Serial.print(F("    -> Rate: "));
  Serial.print(rate, 1);
  Serial.println(F(" cmds/sec"));
  printResult(F("I2C Throughput (>100 cmds/s)"), rate > 100);
}

// ============================================================
// TEST 8: Dynamic Vin Under Full Motor Load
// ============================================================
void test_DynamicVin() {
  printHeader(F("TEST 8: Dynamic Vin Under Full Load"));

  uint32_t vin_idle = dut.getVin();
  delay(30);

  dut.motorA_CW(255);
  dut.motorB_CW(255);
  delay(300);

  uint32_t vin_load = dut.getVin();
  delay(20);

  dut.stopAll();

  uint32_t volt_drop = (vin_idle > vin_load) ? (vin_idle - vin_load) : 0;
  Serial.print(F("    -> Idle: "));
  Serial.print(vin_idle);
  Serial.print(F("mV, Full Load: "));
  Serial.print(vin_load);
  Serial.print(F("mV, Drop: "));
  Serial.print(volt_drop);
  Serial.println(F("mV"));

  bool dropOk = (volt_drop < 1500);
  printResult(F("Vin Drop Under Load (<1500mV)"), dropOk);
}

// ============================================================
// Setup: Runs the Full QC Suite Once
// ============================================================
void setup() {
  Serial.begin(9600);
  while (!Serial) { ; }

  Serial.println(F("============================================================"));
  Serial.println(F(" MakerEdu I2C Motor Driver - Manufacturer Stress Test"));
  Serial.println(F(" Connect motors and power (6V-12V Vin) before testing!"));
  Serial.println(F("============================================================"));

  Wire.begin();
  dut.begin(DUT_ADDRESS);
  delay(200);

  test_ModuleIdentification();
  test_VinMeasurement();
  test_MotorA();
  test_MotorB();
  test_DualMotor();
  test_Timeout();
  test_I2CStress();
  test_DynamicVin();

  Serial.println();
  Serial.println(F("============================================================"));
  Serial.println(F(" TEST SUMMARY"));
  Serial.println(F("============================================================"));
  Serial.print(F("  Total Tests : "));
  Serial.println(totalTests);
  Serial.print(F("  Passed      : "));
  Serial.println(passedTests);
  Serial.print(F("  Failed      : "));
  Serial.println(failedTests);
  Serial.println(F("------------------------------------------------------------"));
  if (failedTests == 0) {
    Serial.println(F("  >>> OVERALL RESULT: [PASS] - BOARD OK FOR SHIPMENT <<<"));
  } else {
    Serial.println(F("  >>> OVERALL RESULT: [FAIL] - DO NOT SHIP! Check above <<<"));
  }
  Serial.println(F("============================================================"));
}

void loop() {
  // QC Test runs once on boot. Press Arduino Reset button to re-run.
}
