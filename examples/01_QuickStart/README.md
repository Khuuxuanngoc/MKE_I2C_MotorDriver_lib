# Example 01: Quick Start / Hướng Dẫn Nhanh

[English](#english) | [Tiếng Việt](#tiếng-việt)

---

<a name="english"></a>
## 🇬🇧 English

### Overview
This example demonstrates how to initialize the **MakerEdu I2C Dual DC Motor Driver** module and perform basic motor control operations (forward, backward, ramp speed, and stop) on Motor A and Motor B.

### Hardware Connection
| Arduino Pin | MakerEdu I2C Motor Driver Pin | Description |
|:-----------:|:-----------------------------:|:------------|
| `5V` / `3.3V` | `5V` / `VCC` | Logic power supply |
| `GND` | `GND` | Ground connection |
| `A4` (Uno) / `SDA` (Mega/ESP32) | `SDA` | I2C Data line |
| `A5` (Uno) / `SCL` (Mega/ESP32) | `SCL` | I2C Clock line |
| External Power (6V - 12V) | `Vin` / `GND` (Screw Terminal) | Motor power supply |
| Motor 1 | `MA` Terminal | DC Motor A |
| Motor 2 | `MB` Terminal | DC Motor B |

### How It Works
1. `Wire.begin()` initializes the I2C bus on the Arduino Master.
2. `motorDriver.begin(0x40)` binds the driver object to default I2C address `0x40`.
3. `motorDriver.motorA_CW(speed)` drives Motor A clockwise with speed (0 to 255).
4. `motorDriver.motorA_CCW(speed)` drives Motor A counter-clockwise.
5. `motorDriver.stopMotorA()` or `motorDriver.stopAll()` brings motors to an immediate stop.

### Expected Serial Output (9600 baud)
```text
MakerEdu I2C Motor Driver - Quick Start
Motor A: Forward 50% speed...
Motor A: Forward 100% speed...
Motor A: Stop
Motor A: Backward 50% speed...
Motor B: Forward 100% + Motor A: Backward 100%...
All Motors Stop!
```

---

<a name="tiếng-việt"></a>
## 🇻🇳 Tiếng Việt

### Tổng quan
Ví dụ này hướng dẫn cách khởi tạo mạch **MakerEdu I2C Dual DC Motor Driver** và thực hiện các thao tác điều khiển động cơ cơ bản (quay thuận, quay ngược, thay đổi tốc độ và dừng) trên cả 2 kênh Motor A và Motor B.

### Sơ đồ đấu nối phần cứng
| Chân Arduino | Chân Mạch I2C Motor Driver | Chức năng / Mô tả |
|:------------:|:--------------------------:|:------------------|
| `5V` hoặc `3.3V` | `5V` / `VCC` | Nguồn nuôi mạch Logic |
| `GND` | `GND` | Chân mass chung |
| `A4` (Uno) / `SDA` (Mega/ESP32) | `SDA` | Đường truyền dữ liệu I2C |
| `A5` (Uno) / `SCL` (Mega/ESP32) | `SCL` | Đường xung clock I2C |
| Nguồn ngoài (6V - 12V) | `Vin` / `GND` (Terminal Bắt vít) | Nguồn cấp cho động cơ |
| Động cơ DC 1 | Cổng `MA` | Kênh Motor A |
| Động cơ DC 2 | Cổng `MB` | Kênh Motor B |

### Nguyên lý hoạt động
1. Gọi `Wire.begin()` để khởi động bus I2C trên Arduino Master.
2. Gọi `motorDriver.begin()` (mặc định địa chỉ `0x40`) để liên kết thư viện với module.
3. Sử dụng `motorDriver.motorA_CW(speed)` / `motorA_CCW(speed)` để quay thuận / ngược với dải tốc độ `0 - 255`.
4. Gọi `motorDriver.stopMotorA()`, `stopMotorB()` hoặc `stopAll()` để dừng động cơ ngay lập tức.
