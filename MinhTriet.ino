#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>

#include <SoftwareSerial.h>
SoftwareSerial BT(11,10); // RX, TX

// Motor pins (PWM capable)
int IN1 = 5;
int IN2 = 6;
int IN3 = 9;
int IN4 = 10;

void setup() {
  Serial.begin(9600);
  BT.begin(9600);

  Dabble.begin(BT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void moveMotor(int leftSpeed, int rightSpeed) {
  // LEFT motor
  if (leftSpeed >= 0) {
    analogWrite(IN1, leftSpeed);
    analogWrite(IN2, 0);
  } else {
    analogWrite(IN1, 0);
    analogWrite(IN2, -leftSpeed);
  }

  // RIGHT motor
  if (rightSpeed >= 0) {
    analogWrite(IN3, rightSpeed);
    analogWrite(IN4, 0);
  } else {
    analogWrite(IN3, 0);
    analogWrite(IN4, -rightSpeed);
  }
}

void loop() {
  Dabble.processInput();

  int x = GamePad.getx_axis();  // -7 → +7
  int y = GamePad.gety_axis();  // -7 → +7

  // Chuyển giá trị joystick sang tốc độ PWM
  int speedY = map(abs(y), 0, 7, 0, 255);
  int speedX = map(abs(x), 0, 7, 0, 255);

  int leftMotor = 0;
  int rightMotor = 0;

  // Điều khiển theo vector JoyStick
  if (y > 1) { // Tiến
    leftMotor  = speedY;
    rightMotor = speedY;
  } else if (y < -1) { // Lùi
    leftMotor  = -speedY;
    rightMotor = -speedY;
  }

  if (x > 1) { // Phải
    rightMotor -= speedX;
    leftMotor  += speedX;
  } else if (x < -1) { // Trái
    rightMotor += speedX;
    leftMotor  -= speedX;
  }

  moveMotor(leftMotor, rightMotor);
}
