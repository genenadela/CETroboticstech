#include <Servo.h>

/*Robotics Technology Final Project
 * Autonomous Robot
 * Group 6
 * Gene Nadela
 */

const int enaPinL = 11; // Green
const int in1PinL = 10; //Blue
const int in2PinL = 9; //Purple

const int enaPinR = 8; //Green
const int in1PinR = 7; //Blue
const int in2PinR = 6; //Purple

//Encoder Setup
const int encoderOut = 4; //Encoder Pin
const int numReadings = 10;
int encoderValue = 0;
int average;


//Arm Setup
int gripperPin = 5;
int armPin = 3;
Servo gripperServo;
Servo armServo;
int armCurrentPosition;

char command;

void setup() {
  Serial.begin(9600);
  pinMode(enaPinL, OUTPUT);
  pinMode(in1PinL, OUTPUT);
  pinMode(in2PinL, OUTPUT);
  pinMode(enaPinR, OUTPUT);
  pinMode(in1PinR, OUTPUT);
  pinMode(in2PinR, OUTPUT);
  //pinMode(encoderOut, OUTPUT);

  gripperServo.attach(gripperPin);
  armServo.attach(armPin);

  gripperOn(); //resets gripper to closed state
  armChangePosition(10);
  armCurrentPosition = 0;

  

}

void loop() {
  // put your main code here, to run repeatedly:

  
  
  
  if(Serial.available()){
    command = Serial.read();
  }

  switch (command) {
    case  '1': //Full Rotation CW
    setMotorLeft(255, true);
    setMotorRight(255, true);
    break;
    
    case '2': //
    setMotorLeft(255, true);
    setMotorRight(255, false);
    break;
    
    case '3': //Full Rotation CCW
    setMotorLeft(255, false);
    setMotorRight(255, false);
    break;
    
    case '4':
    setMotorLeft(255, false);
    setMotorRight(255, true);
    break;

    case '5':
    
    break;

    case '0':
    setMotorLeft(0, false);
    setMotorRight(0, false);
    break;
    
    default:
    // do nothing for other command values
    break;
  }

//encoderValue = encoderValue+digitalRead(encoderOut);

/*
for (int i=0; i<11; i++) {
  encoderValue = encoderValue+digitalRead(encoderOut);
  delay(100);
  if (i==10) {
    average=encoderValue/10;
    i=0;
  }
}
*/





Serial.print("Total: ");
Serial.print(encoderValue);
Serial.print("  Average: ");
Serial.println(average);

}

void armChangePosition(int finalposition) {
  
  //int armDifference = position - armCurrentPosition;

  if (finalposition >= armCurrentPosition){
    int armDifference = finalposition - armCurrentPosition;
    for (int i = 0; i <= armDifference; i++) {
      armServo.write(i);
      delay(50);
    }
  }
  else if (armCurrentPosition > finalposition) {
    int armDifference = armCurrentPosition - finalposition;
    for (int i = armCurrentPosition; i <= armDifference; i--) {
      armServo.write(i);
      delay(50);
    }
  }
  armCurrentPosition = finalposition;
  
}

void gripperOn() {
  gripperServo.write(10);
}

void gripperOff() {
  gripperServo.write(50);
}

void setMotorLeft(int speed, boolean reverse){
  analogWrite(enaPinL, speed);
  digitalWrite(in1PinL, !reverse);
  digitalWrite(in2PinL, reverse);
}

void setMotorRight(int speed, boolean reverse){
  analogWrite(enaPinR, speed);
  digitalWrite(in1PinR, !reverse);
  digitalWrite(in2PinR, reverse);
}
