/*
 * Example 06: Mecanum Omnidirectional Robot (4WD / Dual Drivers)
 * 
 * Demonstrates controlling a 4-Wheel Mecanum Robot using 2x MakerEdu I2C Motor Drivers
 * connected in parallel to the same I2C bus:
 * 
 * - Driver 1 (Front Wheels) at I2C Address: 0x40
 *     + Motor A -> Front-Left Wheel (FL)
 *     + Motor B -> Front-Right Wheel (FR)
 * - Driver 2 (Rear Wheels)  at I2C Address: 0x41
 *     + Motor A -> Rear-Left Wheel (RL)
 *     + Motor B -> Rear-Right Wheel (RR)
 * 
 * Compatible with Arduino Uno, Nano, Mega, ESP32, ESP8266, STM32.
 */

#include <MKE_I2C_MotorDriver.h>
#include <Wire.h>

// Define I2C Addresses for the two driver modules
#define ADDR_DRIVER_FRONT (0x40) // Default address (Driver 1)
#define ADDR_DRIVER_REAR  (0x41) // Configured address (Driver 2)

// Create two driver instances
MKE_I2C_MotorDriver driverFront;
MKE_I2C_MotorDriver driverRear;

// Enum for standard Mecanum movement directions
enum MecanumDirection {
  MOVE_FORWARD,
  MOVE_BACKWARD,
  MOVE_SLIDE_LEFT,
  MOVE_SLIDE_RIGHT,
  MOVE_SPIN_LEFT,
  MOVE_SPIN_RIGHT,
  MOVE_DIAG_UP_LEFT,
  MOVE_DIAG_UP_RIGHT,
  MOVE_DIAG_DOWN_LEFT,
  MOVE_DIAG_DOWN_RIGHT,
  MOVE_STOP
};

// ============================================================
// Helper: Drive a single motor channel with signed speed (-255 to 255)
// ============================================================
void driveMotor(MKE_I2C_MotorDriver &driver, bool isMotorA, int speedSigned) {
  uint8_t speed = constrain(abs(speedSigned), 0, 255);
  
  if (speed == 0) {
    if (isMotorA) driver.stopMotorA();
    else          driver.stopMotorB();
  } else if (speedSigned > 0) {
    if (isMotorA) driver.motorA_CW(speed);
    else          driver.motorB_CW(speed);
  } else {
    if (isMotorA) driver.motorA_CCW(speed);
    else          driver.motorB_CCW(speed);
  }
}

// ============================================================
// Set speeds for all 4 wheels individually (-255 to 255)
// ============================================================
void set4WheelSpeeds(int speedFL, int speedFR, int speedRL, int speedRR) {
  // Front Driver (0x40): MA = Front-Left, MB = Front-Right
  driveMotor(driverFront, true, speedFL);
  driveMotor(driverFront, false, speedFR);

  // Rear Driver (0x41): MA = Rear-Left, MB = Rear-Right
  driveMotor(driverRear, true, speedRL);
  driveMotor(driverRear, false, speedRR);
}

// ============================================================
// Move Mecanum Robot in standard omnidirectional patterns
// ============================================================
void mecanumMove(MecanumDirection dir, uint8_t speed) {
  switch (dir) {
    case MOVE_FORWARD:
      set4WheelSpeeds(speed, speed, speed, speed);
      break;
    case MOVE_BACKWARD:
      set4WheelSpeeds(-speed, -speed, -speed, -speed);
      break;
    case MOVE_SLIDE_LEFT: // Strafe Left
      set4WheelSpeeds(-speed, speed, speed, -speed);
      break;
    case MOVE_SLIDE_RIGHT: // Strafe Right
      set4WheelSpeeds(speed, -speed, -speed, speed);
      break;
    case MOVE_SPIN_LEFT: // Rotate Counter-Clockwise
      set4WheelSpeeds(-speed, speed, -speed, speed);
      break;
    case MOVE_SPIN_RIGHT: // Rotate Clockwise
      set4WheelSpeeds(speed, -speed, speed, -speed);
      break;
    case MOVE_DIAG_UP_LEFT:
      set4WheelSpeeds(0, speed, speed, 0);
      break;
    case MOVE_DIAG_UP_RIGHT:
      set4WheelSpeeds(speed, 0, 0, speed);
      break;
    case MOVE_DIAG_DOWN_LEFT:
      set4WheelSpeeds(-speed, 0, 0, -speed);
      break;
    case MOVE_DIAG_DOWN_RIGHT:
      set4WheelSpeeds(0, -speed, -speed, 0);
      break;
    case MOVE_STOP:
    default:
      driverFront.stopAll();
      driverRear.stopAll();
      break;
  }
}

// ============================================================
// Setup
// ============================================================
void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println(F("========================================"));
  Serial.println(F("  MakerEdu Mecanum 4WD Robot Demo       "));
  Serial.println(F("========================================"));

  // 1. Initialize I2C Bus on Master
  Wire.begin();

  // 2. Initialize Driver instances
  driverFront.begin(ADDR_DRIVER_FRONT);
  driverRear.begin(ADDR_DRIVER_REAR);

  // 3. Check Battery Voltage on both drivers
  Serial.print(F("Driver Front (0x40) Vin: "));
  Serial.print(driverFront.getVin() / 1000.0, 2);
  Serial.println(F(" V"));

  Serial.print(F("Driver Rear  (0x41) Vin: "));
  Serial.print(driverRear.getVin() / 1000.0, 2);
  Serial.println(F(" V"));

  // Ensure motors are stopped initially
  mecanumMove(MOVE_STOP, 0);
  delay(1000);
}

// ============================================================
// Main Loop: Demo Omnidirectional Motion Sequences
// ============================================================
void loop() {
  uint8_t speed = 180;

  // 1. Move Forward (2s)
  Serial.println(F("-> Move FORWARD"));
  mecanumMove(MOVE_FORWARD, speed);
  delay(2000);

  // 2. Move Backward (2s)
  Serial.println(F("-> Move BACKWARD"));
  mecanumMove(MOVE_BACKWARD, speed);
  delay(2000);

  // 3. Slide Left (Strafe 90 deg) (2s)
  Serial.println(F("-> Slide LEFT (Strafe)"));
  mecanumMove(MOVE_SLIDE_LEFT, speed);
  delay(2000);

  // 4. Slide Right (Strafe 90 deg) (2s)
  Serial.println(F("-> Slide RIGHT (Strafe)"));
  mecanumMove(MOVE_SLIDE_RIGHT, speed);
  delay(2000);

  // 5. Spin Left (Rotate in-place) (1.5s)
  Serial.println(F("-> Spin LEFT (CCW)"));
  mecanumMove(MOVE_SPIN_LEFT, speed);
  delay(1500);

  // 6. Spin Right (Rotate in-place) (1.5s)
  Serial.println(F("-> Spin RIGHT (CW)"));
  mecanumMove(MOVE_SPIN_RIGHT, speed);
  delay(1500);

  // 7. Diagonal Up-Right (45 deg) (2s)
  Serial.println(F("-> Diagonal UP-RIGHT"));
  mecanumMove(MOVE_DIAG_UP_RIGHT, speed);
  delay(2000);

  // 8. Diagonal Down-Left (45 deg) (2s)
  Serial.println(F("-> Diagonal DOWN-LEFT"));
  mecanumMove(MOVE_DIAG_DOWN_LEFT, speed);
  delay(2000);

  // 9. Stop & Rest (3s)
  Serial.println(F("-> STOP"));
  mecanumMove(MOVE_STOP, 0);
  delay(3000);
}
