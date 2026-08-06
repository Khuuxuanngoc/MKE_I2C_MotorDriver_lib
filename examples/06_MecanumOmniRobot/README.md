# Example 06: Mecanum Omnidirectional Robot / Robot Mecanum 4 Bánh Đa Hướng

[English](#english) | [Tiếng Việt](#tiếng-việt)

---

<a name="english"></a>
## 🇬🇧 English

### Overview
This example demonstrates how to build and control a **4-Wheel Mecanum Omnidirectional Robot** using two **MakerEdu I2C Dual DC Motor Drivers** (MKE-M17 or MKE-M18) connected in parallel to the same I2C bus.

### Hardware Setup & Pinout
1. **Driver 1 (Front Wheels):** Keep default I2C Address `0x40`.
   - `Motor A` -> Front-Left (FL) Wheel
   - `Motor B` -> Front-Right (FR) Wheel
2. **Driver 2 (Rear Wheels):** Change I2C Address to `0x41` using Example 04 (`04_AddressConfig`).
   - `Motor A` -> Rear-Left (RL) Wheel
   - `Motor B` -> Rear-Right (RR) Wheel
3. **I2C Bus Connection:** Connect `SDA`, `SCL`, `VCC`, and `GND` of both drivers in parallel to the Master board (Arduino Uno / ESP32).
4. **Power Jumper:** Set **`J1 = OFF`** on both drivers.

### Mecanum Movement Kinematics (X-Configuration)
| Motion Direction | FL Motor | FR Motor | RL Motor | RR Motor |
|:---|:---:|:---:|:---:|:---:|
| **Forward** | `+V` | `+V` | `+V` | `+V` |
| **Backward** | `-V` | `-V` | `-V` | `-V` |
| **Slide Left (Strafe)** | `-V` | `+V` | `+V` | `-V` |
| **Slide Right (Strafe)** | `+V` | `-V` | `-V` | `+V` |
| **Spin Left (CCW)** | `-V` | `+V` | `-V` | `+V` |
| **Spin Right (CW)** | `+V` | `-V` | `+V` | `-V` |
| **Diagonal Up-Right** | `+V` | `0` | `0` | `+V` |
| **Diagonal Down-Left** | `-V` | `0` | `0` | `-V` |

### Expected Serial Output (9600 baud)
```text
========================================
  MakerEdu Mecanum 4WD Robot Demo       
========================================
Driver Front (0x40) Vin: 8.35 V
Driver Rear  (0x41) Vin: 8.34 V
-> Move FORWARD
-> Move BACKWARD
-> Slide LEFT (Strafe)
-> Slide RIGHT (Strafe)
-> Spin LEFT (CCW)
-> Spin RIGHT (CW)
-> Diagonal UP-RIGHT
-> Diagonal DOWN-LEFT
-> STOP
```

---

<a name="tiếng-việt"></a>
## 🇻🇳 Tiếng Việt

### Tổng quan
Ví dụ này hướng dẫn cách điều khiển **Robot 4 bánh Mecanum đa hướng** bằng cách ghép song song 2 mạch **MakerEdu I2C Dual DC Motor Driver** (MKE-M17 hoặc MKE-M18) trên cùng một đường truyền I2C của vi điều khiển.

### Kết nối phần cứng
1. **Mạch 1 (Bánh trước):** Giữ nguyên địa chỉ mặc định **`0x40`**.
   - `Motor A` nối Bánh trước - Trái (FL)
   - `Motor B` nối Bánh trước - Phải (FR)
2. **Mạch 2 (Bánh sau):** Đổi địa chỉ I2C thành **`0x41`** bằng code ví dụ 04 (`04_AddressConfig`).
   - `Motor A` nối Bánh sau - Trái (RL)
   - `Motor B` nối Bánh sau - Phải (RR)
3. **Đường truyền I2C:** Nối song song các chân `SDA`, `SCL`, `VCC`, `GND` của cả 2 mạch vào Arduino/ESP32 qua mạch Shield mở rộng.
4. **Jumper nguồn:** Luôn gạt **`J1 = OFF`** trên cả 2 mạch.

### Ma trận chuyển động Mecanum
- **Tiến / Lùi:** Cả 4 bánh quay cùng chiều (+ / -).
- **Dạt ngang Trái (Slide Left):** Bánh FL lùi (-), FR tiến (+), RL tiến (+), RR lùi (-).
- **Dạt ngang Phải (Slide Right):** Bánh FL tiến (+), FR lùi (-), RL lùi (-), RR tiến (+).
- **Xoay tròn tại chỗ (Spin):** 2 bánh bên trái quay ngược chiều với 2 bánh bên phải.
- **Đi chéo 45 độ:** 2 bánh trên 1 đường chéo quay, 2 bánh trên đường chéo còn lại đứng yên.
