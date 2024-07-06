#include <ESP32Servo.h>    //intall this library if you are using ESP 32
const int pinLaser = D10;  // output signal pin of laser module/laser pointer
Servo servo1;
Servo servo2;
//int joyX = A0;  //Joystick module VRx pin ->Arduino A0
//int joyY = A1;  //Joystick module VRy pin ->Arduino A1

int pos = 0;
int servoVal;

int servo1Pos = 90;  // Start at middle position
int servo2Pos = 90;  // Start at middle position
const int servo1Pin = D5; // Servo 1 control pin
const int servo2Pin = D3; // 
// Joystick variables
int joyXValue, joyYValue;
const int joyThreshold = 100;  // Adj
const int joyCenter = 3700;    // Assuming a 12-bit ADC (0-4095 range)
const int deadZone = 50;       // Adjust this for the size of the "dead zone"

void setup() {
  Serial.begin(9600);
  pinMode(pinLaser, OUTPUT);
  digitalWrite(pinLaser, HIGH);  // emit red laser
  servo1.setPeriodHertz(50);     // standard 50 Hz servo
  servo1.attach(servo1Pin, 500, 2500);  // D5 for servo1

  servo2.setPeriodHertz(50);
  servo2.attach(servo2Pin, 500, 2500);  // D3 for servo2
}

void loop() {

  int joyXValue = analogRead(A0);
  int joyYValue = analogRead(A1);

   if (abs(joyXValue - joyCenter) <= deadZone) {
    // Stop the servo if joystick is in the dead zone
    servo1.write(90);
  } else if (joyXValue < joyCenter - joyThreshold) {
    // Rotate counterclockwise
    int speed = map(joyXValue, 0, joyCenter - joyThreshold, 180, 90);
    servo1.write(speed);
  } else if (joyXValue > joyCenter + joyThreshold) {
    // Rotate clockwise
    int speed = map(joyXValue, joyCenter + joyThreshold, 4095, 90, 0);
    servo1.write(speed);
  }

  // Control Servo 2 (up-down movement)
  if (abs(joyYValue - joyCenter) <= deadZone) {
    // Stop the servo if joystick is in the dead zone
    servo2.write(90);
  } else if (joyYValue < joyCenter - joyThreshold) {
    // Rotate counterclockwise
    int speed = map(joyYValue, 0, joyCenter - joyThreshold, 180, 90);
    servo2.write(speed);
  } else if (joyYValue > joyCenter + joyThreshold) {
    // Rotate clockwise
    int speed = map(joyYValue, joyCenter + joyThreshold, 4095, 90, 0);
    servo2.write(speed);
  }


  // Print servo positions for debugging
  Serial.print("Servo 1: ");
  Serial.print(servo1Pos);
  Serial.print(" | Servo 2: ");
  Serial.print(servo2Pos);
  Serial.print(" | X: ");
  Serial.print(joyXValue);
  Serial.print(" | Y: ");
  Serial.println(joyYValue);

  delay(15);
}
