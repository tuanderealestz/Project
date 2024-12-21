#define BLYNK_TEMPLATE_ID "TMPL631-wyQXl"
#define BLYNK_TEMPLATE_NAME "ESP32"
#define BLYNK_AUTH_TOKEN "1IF_EO-6AauemNu33xajORREycxmy0wc"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

#define SENSOR 36             // Chân analog để đọc tín hiệu từ cảm biến AD8232 (GPIO36 là VP)
#define SAMPLE_SIZE 10        // Số lượng mẫu tín hiệu để lọc

// Thông tin WiFi
char ssid[] = "Redmi";    // Tên WiFi của bạn
char pass[] = "tuan12345";     // Mật khẩu WiFi của bạn

BlynkTimer timer;             // Đối tượng Blynk Timer
int samples[SAMPLE_SIZE] = {0}; // Mảng chứa các giá trị mẫu tín hiệu
int sampleIndex = 0;          // Chỉ số trong mảng mẫu
unsigned long counter = 0;    // Bộ đếm số lần gửi dữ liệu
unsigned long lastMillis = 0; // Để kiểm soát chu kỳ lấy mẫu

// Hàm lọc giá trị tín hiệu (moving average)
int getFilteredECG() {
  int raw = analogRead(SENSOR);      // Đọc giá trị thô từ cảm biến
  samples[sampleIndex] = raw;        // Lưu giá trị vào mảng mẫu
  sampleIndex = (sampleIndex + 1) % SAMPLE_SIZE; // Cập nhật vị trí trong mảng (quay vòng)

  // Tính giá trị trung bình của các mẫu
  long sum = 0;
  for (int i = 0; i < SAMPLE_SIZE; i++) {
    sum += samples[i];
  }
  return sum / SAMPLE_SIZE;
}

// Hàm gửi dữ liệu ECG và counter lên Blynk
void sendECG() {
  int ecgValue = getFilteredECG();    // Lấy giá trị ECG đã lọc
  counter++;                          // Tăng bộ đếm mỗi lần gửi dữ liệu
  Blynk.virtualWrite(V0, ecgValue);   // Gửi giá trị ECG lên Virtual Pin V0
  Blynk.virtualWrite(V1, counter);    // Gửi giá trị bộ đếm lên Virtual Pin V1

  // Debug trên Serial
  Serial.print("ECG Value (raw): ");
  Serial.println(analogRead(SENSOR));
  Serial.print("ECG Value (filtered): ");
  Serial.println(ecgValue);
  Serial.print("Counter sent to V1: ");
  Serial.println(counter);
}

void setup() {
  Serial.begin(115200);              // Khởi động giao tiếp Serial
  WiFi.begin(ssid, pass);            // Kết nối WiFi

  while (WiFi.status() != WL_CONNECTED) { // Đợi WiFi kết nối
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected.");

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass); // Kết nối với Blynk

  pinMode(SENSOR, INPUT);            // Cấu hình chân cảm biến là INPUT

  // Đặt thời gian gửi dữ liệu ECG lên Blynk (mỗi 500ms)
  timer.setInterval(500L, sendECG);

  Serial.println("Setup completed. Ready to read ECG.");
}

void loop() {
  // Lấy tín hiệu ECG thô mỗi 10ms
  if (millis() - lastMillis > 10) {
    lastMillis = millis();
    int rawValue = analogRead(SENSOR); // Đọc tín hiệu thô từ cảm biến
    Serial.println(rawValue);         // In giá trị tín hiệu ra Serial Monitor
  }

  Blynk.run();   // Xử lý kết nối và gửi dữ liệu đến Blynk
  timer.run();   // Chạy Blynk Timer
}
