#include "DHT.h"

#define DHTPIN 2       // 온습도 센서 핀
#define DHTTYPE DHT11
#define PIR_PIN 3      // 인체감지 센서 핀 (인터럽트)

DHT dht(DHTPIN, DHTTYPE);
volatile int motionStatus = 0; // 움직임 감지 여부 (0:없음, 1:있음)

// 인터럽트 함수 (움직임 감지되면 1로 바꿈)
void detectMotion() {
  motionStatus = 1;
}

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(PIR_PIN, INPUT);
  // PIR 센서 인터럽트 설정 (움직임 있으면 detectMotion 실행)
  attachInterrupt(digitalPinToInterrupt(PIR_PIN), detectMotion, RISING);
}

void loop() {
  // 2초 대기 (이 동안 움직임이 있으면 motionStatus가 1로 변해있음)
  delay(2000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) return;

  // 데이터 전송: 습도,온도,감지여부
  Serial.print(h);
  Serial.print(",");
  Serial.print(t);
  Serial.print(",");
  Serial.println(motionStatus);

  // 전송 후 감지 상태 초기화 (다음 2초를 위해)
  motionStatus = 0; 
}