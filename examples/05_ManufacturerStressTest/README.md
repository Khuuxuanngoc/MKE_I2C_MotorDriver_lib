# Example 05: Manufacturer & QC Stress Test / Kiểm Thử Sản Xuất & Đánh Giá Chất Lượng

[English](#english) | [Tiếng Việt](#tiếng-việt)

---

<a name="english"></a>
## 🇬🇧 English

### Overview
This automated test suite is exclusively designed for **Factory Production Testing and QC Engineers**. It thoroughly verifies hardware integrity, firmware stability, and power reliability of the **MakerEdu I2C Dual DC Motor Driver** before shipment.

### Test Suite Coverage
1. **TEST 1 - Module Identification:** I2C ping, verify `Module ID == 3`, read Firmware Version, and verify EEPROM address.
2. **TEST 2 - Vin Measurement & Jitter:** 5-sample average Vin check within 6V - 13V range, and 10-sample jitter stability (< 200mV).
3. **TEST 3 - Motor A Control:** Ramping clockwise and counter-clockwise speeds (64 → 127 → 180 → 255) + Emergency Stop test.
4. **TEST 4 - Motor B Control:** Ramping speeds and direction control on Motor B.
5. **TEST 5 - Dual Motor Simultaneous Load:** Full load test with both channels running concurrently.
6. **TEST 6 - Command Timeout Precision:** Verifies auto-stop timer tolerance within ±150ms.
7. **TEST 7 - I2C Communication Stress Test:** Burst transmission of **500 rapid I2C commands (~2kHz)**; requires **0 errors** for PASS.
8. **TEST 8 - Dynamic Vin Drop under Full Load:** Measures battery voltage drop under 100% duty cycle (acceptable drop < 1500mV).

### Pass Criteria
- All 8 sub-tests must report `[PASS]`.
- Output footer must conclude: `>>> OVERALL RESULT: [PASS] - BOARD OK FOR SHIPMENT <<<`.

---

<a name="tiếng-việt"></a>
## 🇻🇳 Tiếng Việt

### Tổng quan
Bộ test tự động này được thiết kế dành riêng cho **Kỹ sư Nhà máy & Bộ phận QC Kiểm tra Chất lượng**. Chương trình sẽ tự động đánh giá toàn diện phần cứng, độ ổn định của firmware và khả năng chịu tải của mạch **MakerEdu I2C Dual DC Motor Driver** trước khi xuất xưởng.

### 8 Hạng mục Kiểm tra Chi tiết
1. **TEST 1 - Nhận diện Module:** Quét bus I2C, đối chiếu `Module ID == 3`, đọc phiên bản Firmware và địa chỉ EEPROM.
2. **TEST 2 - Độ chính xác & Dao động nguồn Vin:** Đo trung bình 5 lần (khoảng 6V - 13V), kiểm tra độ dao động Jitter (< 200mV).
3. **TEST 3 - Điều khiển Motor A:** Kiểm tra chạy tăng dần tốc độ thuận/nghịch (64 → 127 → 180 → 255) và kiểm tra dừng khẩn cấp.
4. **TEST 4 - Điều khiển Motor B:** Kiểm tra tương tự cho kênh động cơ B.
5. **TEST 5 - Tải đồng thời 2 Motor:** Chạy cùng lúc cả 2 kênh để kiểm tra độ ổn định đường nguồn công suất.
6. **TEST 6 - Độ chính xác Hẹn giờ Timeout:** Kiểm tra tính năng tự ngắt với sai số cho phép ±150ms.
7. **TEST 7 - Stress Test Giao tiếp I2C tốc độ cao:** Truyền liên tục **500 gói tin I2C tần suất cao (~2kHz)**; yêu cầu **0 lỗi** I2C.
8. **TEST 8 - Độ sụt áp nguồn khi tải nặng:** Đo sụt áp khi 2 motor chạy 100% công suất (sụt áp cho phép < 1500mV).

### Tiêu chuẩn Đạt (PASS)
- Toàn bộ 8 bài test phải đạt `[PASS]`.
- Kết luận cuối cùng: `>>> OVERALL RESULT: [PASS] - BOARD OK FOR SHIPMENT <<<`.
