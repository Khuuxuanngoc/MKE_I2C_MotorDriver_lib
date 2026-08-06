# Example 02: Timed Run & Watchdog Safety / Chạy Hẹn Giờ & An Toàn Watchdog

[English](#english) | [Tiếng Việt](#tiếng-việt)

---

<a name="english"></a>
## 🇬🇧 English

### Overview
This example demonstrates the built-in **Command Timeout** feature of the **MakerEdu I2C Dual DC Motor Driver**. When a non-zero `duration_ms` parameter is passed, the on-board MCU automatically cuts motor PWM after the elapsed time without requiring an explicit stop command from the Master.

### Key Benefits
- **Non-blocking Master Logic:** Master sends a single drive command with timeout, then performs other tasks while the motor runs and auto-stops.
- **PID Watchdog Failsafe:** By streaming commands with `duration_ms` slightly greater than the loop cycle (e.g., cycle = 100ms, duration = 200ms), the robot automatically halts safely if the Master controller crashes or I2C wiring disconnects.

### How It Works
```cpp
// Motor runs counter-clockwise at speed 200 and auto-stops after 3000ms
motorDriver.motorB_CCW(200, 3000);
```

### Expected Serial Output (9600 baud)
```text
MakerEdu I2C Motor Driver - Timed Run Demo
Motor B: Backward (speed=200), auto-stop after 3s...
Motor A: Forward (speed=127), auto-stop after 1.5s...
PID Watchdog demo: streaming 10 commands at 100ms interval...
Watchdog stream finished. Stopping motors.
```

---

<a name="tiếng-việt"></a>
## 🇻🇳 Tiếng Việt

### Tổng quan
Ví dụ này minh họa tính năng **Hẹn giờ chạy tự ngắt (Timed Run)** tích hợp trên mạch **MakerEdu I2C Dual DC Motor Driver**. Khi truyền giá trị `duration_ms > 0`, vi điều khiển trên mạch sẽ tự động ngắt xung PWM và dừng động cơ sau đúng thời gian cài đặt mà Master không cần gửi thêm lệnh Stop.

### Lợi ích nổi bật
- **Giải phóng vi điều khiển Master:** Master chỉ cần gửi 1 lệnh duy nhất và có thể tiếp tục thực hiện các tác vụ khác.
- **Cơ chế An toàn Watchdog cho Robot / Vòng lặp PID:** Khi điều khiển xe tự hành hoặc cân bằng PID tần số cao, ta đặt `duration_ms` lớn hơn chu kỳ gửi lệnh (ví dụ gửi mỗi 100ms, đặt duration = 200ms). Nếu Master bị treo hoặc đứt dây I2C, xe sẽ tự động dừng sau 200ms, tránh trường hợp xe mất kiểm soát và lao tự do.

### Cú pháp hàm
```cpp
// Motor B quay ngược tốc độ 200, tự dừng sau 3000ms (3 giây)
motorDriver.motorB_CCW(200, 3000);
```
