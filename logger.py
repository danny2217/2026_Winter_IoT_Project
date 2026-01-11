import serial
import pymysql
import time

# 1. DB 연결
db = pymysql.connect(
    host='localhost', user='root', password='root',
    db='iot_db', charset='utf8'
)

# 2. 시리얼 연결 (115200)
PORT = '/dev/ttyACM0' 
try:
    ser = serial.Serial(PORT, 115200, timeout=1)
    ser.flush()
    print(f"✅ 포트 연결 성공: {PORT}")
except:
    print("❌ 포트 연결 실패")
    exit()

print("⏳ 안정화 대기중...")
time.sleep(3)
ser.read_all()

try:
    while True:
        if ser.in_waiting > 0:
            # 디코딩 에러 무시
            line = ser.readline().decode('utf-8', errors='ignore').rstrip()
            if line:
                try:
                    data = line.split(',')
                    if len(data) == 3:
                        hum, temp, motion = data
                        
                        # DB Insert
                        cursor = db.cursor()
                        sql = "INSERT INTO sensors (humidity, temperature, is_motion) VALUES (%s, %s, %s)"
                        cursor.execute(sql, (hum, temp, motion))
                        db.commit()
                        
                        status = "🚨침입!" if motion == '1' else "안전"
                        print(f"💾 [저장] 온:{temp} 습:{hum} 감지:{status}")
                except:
                    pass
        time.sleep(0.1)

except KeyboardInterrupt:
    db.close()
    ser.close()
