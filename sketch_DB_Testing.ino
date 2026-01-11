#include "DHT.h"
#define DHTPIN 2       
#define DHTTYPE DHT11
#define PIR_PIN 3      

DHT dht(DHTPIN, DHTTYPE);
volatile int motionStatus = 0; 

void detectMotion() {
  motionStatus = 1; // 인터럽트 발생 시 1로 변경
}

void setup() {
  Serial.begin(115200); // ⭐ 중요: 115200 속도
  dht.begin();
  pinMode(PIR_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(PIR_PIN), detectMotion, RISING);
}

void loop() {
  delay(2000); 

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // 데이터 오류 방지
  if (isnan(h)) h = 0.0;
  if (isnan(t)) t = 0.0;

  // CSV 포맷 전송: 습도,온도,감지(0or1)
  Serial.print(h);
  Serial.print(",");
  Serial.print(t);
  Serial.print(",");
  Serial.println(motionStatus);

  motionStatus = 0; // 상태 초기화
}
