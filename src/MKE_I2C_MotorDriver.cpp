#include "MKE_I2C_MotorDriver.h"

// ============================================================
// Constructor: Rỗng, gán giá trị mặc định cho biến nội bộ
// ============================================================
MKE_I2C_MotorDriver::MKE_I2C_MotorDriver() {
  _address = MKE_MOTOR_DEFAULT_ADDRESS;
  _wire = &Wire;
}

// ============================================================
// Khởi tạo
// ============================================================
void MKE_I2C_MotorDriver::begin(uint8_t address, TwoWire &wire) {
  _address = address;
  _wire = &wire;
}

// ============================================================
// Hàm nội bộ: Gửi lệnh Write
// Cấu trúc 6 byte:
// [addr_kxn_rx][modeId][payload_byte3][payload_byte2][payload_byte1][payload_byte0]
// ============================================================
void MKE_I2C_MotorDriver::_sendCommand(uint8_t modeId,
                                              uint32_t payload) {
  _wire->beginTransmission(_address);
  _wire->write(MKE_MOTOR_I2C_REGION); // addr_kxn_rx = 5
  _wire->write(modeId);
  _wire->write((uint8_t)(payload >> 24));
  _wire->write((uint8_t)(payload >> 16));
  _wire->write((uint8_t)(payload >> 8));
  _wire->write((uint8_t)(payload & 0xFF));
  _wire->endTransmission();
}

// ============================================================
// Hàm nội bộ: Gửi lệnh Read, nhận về uint32_t (4 byte Big Endian)
// ============================================================
uint32_t MKE_I2C_MotorDriver::_readCommand(uint8_t modeId) {
  _sendCommand(modeId, 0); // Gửi lệnh Get trước
  delayMicroseconds(200);  // Chờ Slave xử lý

  _wire->requestFrom(_address, (uint8_t)4);
  uint32_t result = 0;
  if (_wire->available() >= 4) {
    result = ((uint32_t)_wire->read()) << 24;
    result |= ((uint32_t)_wire->read()) << 16;
    result |= ((uint32_t)_wire->read()) << 8;
    result |= ((uint32_t)_wire->read());
  }
  return result;
}

// ============================================================
// Hàm nội bộ: Đóng gói payload có timeout
// ============================================================
uint32_t MKE_I2C_MotorDriver::_packPayload(uint8_t speed,
                                                  uint16_t duration_ms) {
  return ((uint32_t)duration_ms << 16) | (uint32_t)speed;
}

// ============================================================
// Điều khiển Motor A
// ============================================================
void MKE_I2C_MotorDriver::motorA_CW(uint8_t speed,
                                           uint16_t duration_ms) {
  _sendCommand(MKE_MOTOR_CMD_SET_MA_CW, _packPayload(speed, duration_ms));
}

void MKE_I2C_MotorDriver::motorA_CCW(uint8_t speed,
                                            uint16_t duration_ms) {
  _sendCommand(MKE_MOTOR_CMD_SET_MA_CCW, _packPayload(speed, duration_ms));
}

void MKE_I2C_MotorDriver::stopMotorA() {
  _sendCommand(MKE_MOTOR_CMD_STOP_MA, 0);
}

// ============================================================
// Điều khiển Motor B
// ============================================================
void MKE_I2C_MotorDriver::motorB_CW(uint8_t speed,
                                           uint16_t duration_ms) {
  _sendCommand(MKE_MOTOR_CMD_SET_MB_CW, _packPayload(speed, duration_ms));
}

void MKE_I2C_MotorDriver::motorB_CCW(uint8_t speed,
                                            uint16_t duration_ms) {
  _sendCommand(MKE_MOTOR_CMD_SET_MB_CCW, _packPayload(speed, duration_ms));
}

void MKE_I2C_MotorDriver::stopMotorB() {
  _sendCommand(MKE_MOTOR_CMD_STOP_MB, 0);
}

void MKE_I2C_MotorDriver::stopAll() {
  stopMotorA();
  stopMotorB();
}

// ============================================================
// Cài đặt nâng cao & PWM thô (Khớp nhãn MA1, MA2, MB1, MB2)
// ============================================================
void MKE_I2C_MotorDriver::setPwmFrequency(uint32_t frequency_hz) {
  _sendCommand(MKE_MOTOR_CMD_SET_FREQ, frequency_hz);
}

void MKE_I2C_MotorDriver::setPwmMA1(uint8_t value) {
  _sendCommand(MKE_MOTOR_CMD_SET_PWM_A1, (uint32_t)value);
}

void MKE_I2C_MotorDriver::setPwmMA2(uint8_t value) {
  _sendCommand(MKE_MOTOR_CMD_SET_PWM_A2, (uint32_t)value);
}

void MKE_I2C_MotorDriver::setPwmMB1(uint8_t value) {
  _sendCommand(MKE_MOTOR_CMD_SET_PWM_B1, (uint32_t)value);
}

void MKE_I2C_MotorDriver::setPwmMB2(uint8_t value) {
  _sendCommand(MKE_MOTOR_CMD_SET_PWM_B2, (uint32_t)value);
}

// ============================================================
// Đọc thông tin
// ============================================================
uint32_t MKE_I2C_MotorDriver::getVin() {
  return _readCommand(MKE_MOTOR_CMD_GET_VIN);
}

uint8_t MKE_I2C_MotorDriver::getAddress() {
  return (uint8_t)_readCommand(MKE_MOTOR_CMD_GET_ADDRESS);
}

uint32_t MKE_I2C_MotorDriver::getFirmwareVersion() {
  return _readCommand(MKE_MOTOR_CMD_GET_FW_VERSION);
}

uint8_t MKE_I2C_MotorDriver::getModuleId() {
  return (uint8_t)_readCommand(MKE_MOTOR_CMD_GET_ID_MODULE);
}

uint32_t MKE_I2C_MotorDriver::getProductCode() {
  return _readCommand(MKE_MOTOR_CMD_GET_PRODUCT_CODE);
}

// ============================================================
// Quản lý địa chỉ
// ============================================================
void MKE_I2C_MotorDriver::setAddress(uint8_t newAddress) {
  _sendCommand(MKE_MOTOR_CMD_SET_ADDRESS, (uint32_t)newAddress);
  _address = newAddress; // Cập nhật địa chỉ nội bộ sau khi đổi thành công
}

// ============================================================
// Admin Mode
// ============================================================
void MKE_I2C_MotorDriver::enableAdminMode() {
  _sendCommand(MKE_MOTOR_CMD_ADMIN_MODE, MKE_MOTOR_ADMIN_KEY);
}