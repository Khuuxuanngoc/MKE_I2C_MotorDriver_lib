# Example 03: Reading Supply Voltage / Đo Điện Áp Nguồn Cấp Vin

[English](#english) | [Tiếng Việt](#tiếng-việt)

---

<a name="english"></a>
## 🇬🇧 English

### Overview
This example demonstrates how to read the real-time external supply voltage (**Vin**) of the **MakerEdu I2C Dual DC Motor Driver** module.

### How It Works
1. The module has an internal 10kΩ / 1kΩ precision resistor divider connected to the Vin pin and read by an internal 12-bit ADC with an Exponential Moving Average (EMA) filter.
2. Calling `motorDriver.getVin()` queries the module over I2C and returns the voltage directly in **milli-volts (mV)**.
3. You can convert the value to Volts (`vin_mV / 1000.0`) to display battery status or trigger safety low-voltage cut-offs.

### Expected Serial Output (9600 baud)
```text
MakerEdu I2C Motor Driver - Read Vin Demo
Monitoring battery/power voltage every 1 second...
Vin: 8412 mV  (~8.41 V)
Vin: 8395 mV  (~8.40 V)
Vin: 6380 mV  (~6.38 V)  [WARNING: Low Battery!]
```

---

<a name="tiếng-việt"></a>
## 🇻🇳 Tiếng Việt

### Tổng quan
Ví dụ này hướng dẫn cách đọc điện áp nguồn cấp động cơ (**Vin**) trực tiếp qua giao thức I2C trên mạch **MakerEdu I2C Dual DC Motor Driver**.

### Nguyên lý hoạt động
1. Mạch tích hợp sẵn cầu phân áp 10kΩ / 1kΩ và bộ lọc số EMA trên MCU giúp giá trị đo luôn ổn định, không bị nhiễu bởi xung động cơ.
2. Hàm `motorDriver.getVin()` gửi lệnh đọc qua I2C và trả về giá trị kiểu `uint32_t` đơn vị **mV** (mili-volt).
3. Người dùng dễ dàng quy đổi sang Volt (`vin_mV / 1000.0`) để giám sát dung lượng pin 2S/3S LiPo/Li-ion và đưa ra cảnh báo ngắt tải khi pin yếu.
