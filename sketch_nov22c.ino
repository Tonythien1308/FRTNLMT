// --- KHAI BÁO BLUETOOTH ---
#include <SoftwareSerial.h>
SoftwareSerial BT(11, 10); // BT_RX, BT_TX

// --- KHAI BÁO L298N ---
int IN1 = 4;
int IN2 = 3;

int IN3 = 2;
int IN4 = 1;

char command;   // ký tự nhận từ app

void setup() {
  // Motor pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Bluetooth
  BT.begin(9600);

  // Tốc độ PWM mặc định
  //analogWrite(ENA, 200);
  //analogWrite(ENB, 200);

  Serial.begin(9600);
  Serial.println("Bluetooth Car Ready!");
}

void loop() {
  if (BT.available()) {
    command = BT.read();
    Serial.print("Command: ");
    Serial.println(command);

    switch (command) {

      case 'F':  // Tiến
        forward();
        //delay(1000);
        break;

      case 'B':  // Lùi
        backward();
        //delay(1000);
        break;

      case 'L':  // Rẽ trái
        left();
        //delay(1000);
        break;

      case 'R':  // Rẽ phải
        right();
        //delay(1000)
        break;

      case 'S':  // Dừng
        stopMotors();
        break;

      // Tăng giảm tốc độ
      //case '1': setSpeed(120); break;
      //case '2': setSpeed(160); break;
      //case '3': setSpeed(200); break;
      //case '4': setSpeed(255); break;
    }
  }
}

// ====== HÀM ĐIỀU KHIỂN ======

void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void left() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void right() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

//void setSpeed(int speedVal) {
  //analogWrite(ENA, speedVal);
  //analogWrite(ENB, speedVal);
//}
