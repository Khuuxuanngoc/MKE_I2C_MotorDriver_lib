#ifndef MKE_I2C_MOTOR_DRIVER_H
#define MKE_I2C_MOTOR_DRIVER_H

#include "Arduino.h"
#include <Wire.h>

// ============================================================
// Địa chỉ I2C mặc định
// ============================================================
#define MKE_MOTOR_DEFAULT_ADDRESS (64) // 0x40

// ============================================================
// Mã lệnh I2C (modeId) - Phải đồng bộ với firmware Slave
// ============================================================
#define MKE_MOTOR_CMD_SET_ADDRESS (1)
#define MKE_MOTOR_CMD_GET_ID_MODULE (2)
#define MKE_MOTOR_CMD_GET_FW_VERSION (4)
#define MKE_MOTOR_CMD_GET_PRODUCT_CODE (6)
#define MKE_MOTOR_CMD_SET_PRODUCT_CODE (7)
#define MKE_MOTOR_CMD_GET_LASTUNIXTIME_TEST (9)
#define MKE_MOTOR_CMD_GET_ADDRESS (10)

#define MKE_MOTOR_CMD_SET_PWM_A1 (100)
#define MKE_MOTOR_CMD_SET_PWM_A2 (101)
#define MKE_MOTOR_CMD_SET_PWM_B1 (102)
#define MKE_MOTOR_CMD_SET_PWM_B2 (103)
#define MKE_MOTOR_CMD_SET_FREQ (104)

#define MKE_MOTOR_CMD_SET_MA_CW (106)
#define MKE_MOTOR_CMD_SET_MA_CCW (107)
#define MKE_MOTOR_CMD_SET_MB_CW (108)
#define MKE_MOTOR_CMD_SET_MB_CCW (109)
#define MKE_MOTOR_CMD_STOP_MA (110)
#define MKE_MOTOR_CMD_STOP_MB (111)
#define MKE_MOTOR_CMD_GET_VIN (112)

#define MKE_MOTOR_CMD_ADMIN_MODE (200)
#define MKE_MOTOR_ADMIN_KEY (0xA5A5A5A5UL)

// addr_kxn_rx: phân vùng điều khiển motor
#define MKE_MOTOR_I2C_REGION (5)

// ============================================================
// Lớp thư viện chính
// ============================================================
class MKE_I2C_MotorDriver {
public:
  // Constructor không tham số
  MKE_I2C_MotorDriver();

  // Khởi tạo: Truyền địa chỉ I2C và đối tượng Wire (mặc định 0x40 & Wire)
  void begin(uint8_t address = MKE_MOTOR_DEFAULT_ADDRESS, TwoWire &wire = Wire);

  // ---- Điều khiển Motor A ----
  // Chạy thuận (CW). duration_ms = 0: chạy vô hạn đến khi có lệnh stop
  void motorA_CW(uint8_t speed, uint16_t duration_ms = 0);
  // Chạy ngược (CCW)
  void motorA_CCW(uint8_t speed, uint16_t duration_ms = 0);
  // Dừng Motor A
  void stopMotorA();

  // ---- Điều khiển Motor B ----
  void motorB_CW(uint8_t speed, uint16_t duration_ms = 0);
  void motorB_CCW(uint8_t speed, uint16_t duration_ms = 0);
  void stopMotorB();

  // Dừng cả 2 Motor
  void stopAll();

  // ---- Cài đặt PWM & Điều khiển chân thô ----
  // Đặt tần số PWM (Hz). Mặc định firmware: 500Hz. Khuyến nghị: 500 - 2000Hz
  void setPwmFrequency(uint32_t frequency_hz);

  // Xuất giá trị PWM thô trực tiếp ra các chân in trên mạch (MA1, MA2, MB1,
  // MB2)
  void setPwmMA1(uint8_t value);
  void setPwmMA2(uint8_t value);
  void setPwmMB1(uint8_t value);
  void setPwmMB2(uint8_t value);

  // ---- Đọc thông tin ----
  // Đọc điện áp Vin đầu vào, trả về đơn vị mV (mili-volt)
  uint32_t getVin();
  // Đọc địa chỉ I2C hiện tại đang lưu trong EEPROM
  uint8_t getAddress();
  // Đọc phiên bản firmware
  uint32_t getFirmwareVersion();
  // Đọc ID loại module
  uint8_t getModuleId();
  // Đọc mã sản phẩm
  uint32_t getProductCode();

  // ---- Quản lý địa chỉ I2C ----
  // Đặt địa chỉ mới (1 - 126). Lưu vào EEPROM, có hiệu lực ngay.
  void setAddress(uint8_t newAddress);

  // ---- Admin Mode ----
  void enableAdminMode();

private:
  uint8_t _address;
  TwoWire *_wire;

  // Gửi lệnh Write (không cần phản hồi)
  void _sendCommand(uint8_t modeId, uint32_t payload = 0);

  // Gửi lệnh Read và nhận về 4 byte (uint32_t)
  uint32_t _readCommand(uint8_t modeId);

  // Đóng gói payload: (duration_ms << 16) | speed
  uint32_t _packPayload(uint8_t speed, uint16_t duration_ms);
};

// ============================================================
// ============================================================
// Tạo Alias tên Class để hỗ trợ đầy đủ các mã sản phẩm MakerEdu
// ============================================================
using MKE_I2C_MotorDriver_L9110 = MKE_I2C_MotorDriver;
using MKE_I2C_MotorDriver_BD62130 = MKE_I2C_MotorDriver;
using MKE_M17_MotorDriver = MKE_I2C_MotorDriver;
using MKE_M18_MotorDriver = MKE_I2C_MotorDriver;

#endif // MKE_I2C_MOTOR_DRIVER_H