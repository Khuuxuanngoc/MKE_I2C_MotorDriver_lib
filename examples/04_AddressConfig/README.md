# Example 04: I2C Address Configuration / Cấu Hình Địa Chỉ I2C

[English](#english) | [Tiếng Việt](#tiếng-việt)

---

<a name="english"></a>
## 🇬🇧 English

### Overview
This example demonstrates how to read module metadata (Module ID, Firmware Version, and current I2C address) and reconfigure the I2C slave address to allow cascading multiple motor drivers on the same I2C bus.

### Key Points
- **Default Address:** `0x40` (64 decimal).
- **Supported Range:** `0x01` to `0x7E` (1 to 126 decimal).
- **Persistent Storage:** The new address is written directly into on-board EEPROM and remains saved across power cycles.
- **Factory Reset:** If you forget the assigned address, press and hold the on-board push button for **3 seconds** to reset the module to `0x40`.

### Expected Serial Output (9600 baud)
```text
MakerEdu I2C Motor Driver - Address Configuration
Module ID      : 3
Firmware Ver.  : 260331
Current Address: 0x40

Changing I2C address to 0x41...
New Address    : 0x41
Done! Use address 0x41 in your subsequent sketches.
```

---

<a name="tiếng-việt"></a>
## 🇻🇳 Tiếng Việt

### Tổng quan
Ví dụ này hướng dẫn cách đọc thông tin nhận diện module (ID Module, Phiên bản Firmware, Địa chỉ hiện tại) và đổi địa chỉ I2C để có thể kết nối nhiều mạch điều khiển động cơ trên cùng một đường truyền I2C.

### Lưu ý quan trọng
- **Địa chỉ mặc định:** `0x40` (64 trong hệ thập phân).
- **Dải địa chỉ hỗ trợ:** `0x01` đến `0x7E` (1 đến 126).
- **Lưu trữ vĩnh viễn:** Địa chỉ mới được lưu trực tiếp vào bộ nhớ EEPROM trên mạch và không bị mất khi tắt nguồn.
- **Khôi phục cài đặt gốc:** Nếu quên địa chỉ I2C, chỉ cần **nhấn giữ nút nhấn trên mạch trong 3 giây**, mạch sẽ tự động khôi phục về địa chỉ mặc định `0x40`.
