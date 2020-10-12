
#include <Pixy2.h>


#include <VarSpeedServo.h>
#include <math.h>

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
const float encoderConstant = 76.5;
const float encoderConstantAngle = 22;
const int encoderOut = 4; //Encoder Pin
int encoderValue = 0;
int average;


//Arm Setup
int gripperPin = 5;
int armPin = 3;
VarSpeedServo gripperServo;
VarSpeedServo armServo;
int armCurrentPosition;

char command;

class Vector2
{
  public:
  float x; // x-coordinate
  float y; //y-coordinate
  float yaw; //orientation
  
};


float waypoints [4][2] = {
  {0,0},
  {0, 0.35},
  {-0.35, 0.35},
  {-0.35, 0},
};

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
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
  armChangePosition(15);
  

}

void loop() {

  
  if(Serial1.available()){
    command = Serial1.read();
  }

  switch (command) {
    case  '1': //Waypoint Demo
      waypointDemo();
      
    break;
    
    case '2': //Move Forward 35cm
      translate(0.35);
    break;
    
    case '3': //Move Backward 35cm
      translateBackwards(0.35);
    break;
    
    case '4': //Rotate 90 deg CCW
      rotate(1.57);
    break;

    case '5': //Rotate 90 deg CW
      rotate(-1.57);
    break;

    case '6': //Arm Position 30
      armChangePosition(80);
    break;

    case '7': //Arm Position 10
      armChangePosition(20);
    break;

    case '8':
      gripperOn();
    break;

    case '9':
      gripperOff();
    break;

    case '0':
    fullStop();
    break;
    
    default:
    // do nothing for other command values
    break;
  }








Serial.print("Total: ");
Serial.print(encoderValue);

}

void waypointDemo() {
  Vector2 A,B;
  A.yaw=PI/2.0; //initial robot orientation is 90 degress (1.57 radians) wrt positive x-axis

  for(int i=0;i<3;i++) {
    //obtain starting points
    A.x = waypoints[i][0];
    A.y = waypoints[i][1];

    //obtain ending points
    B.x = waypoints[i+1][0];
    B.y = waypoints[i+1][1];

    A.yaw = waypointStep(A,B);
  }
}

float waypointStep(Vector2 A, Vector2 B) {
  float angle_at_destination = 0;
  angle_at_destination = atan2((B.y-A.y),(B.x-A.x));
  float diff_rotation = angle_at_destination-A.yaw;
  if (diff_rotation > PI) {
    diff_rotation=diff_rotation-2*PI;
  }
  if (diff_rotation < -PI) {
    diff_rotation=diff_rotation+2*PI;
  }

  float distance_to_destination = sqrt(((B.x-A.x)*(B.x-A.x))+((B.y-A.y)*(B.y-A.y)));
  rotate(diff_rotation);
  translate(distance_to_destination);
  return angle_at_destination;
}

void translate(float dist) { //moves robot forward in meters

  float encoderGoal = dist*encoderConstant;
  encoderValue = 0; //initialize encoder value

  while(encoderValue < encoderGoal) {
    moveForward();
    encoderValue = encoderValue+digitalRead(encoderOut);
    delay(10);
  }
  fullStop();
}

void translateBackwards(float dist) { //moves robot forward in meters

  float encoderGoal = dist*encoderConstant;
  encoderValue = 0; //initialize encoder value

  while(encoderValue < encoderGoal) {
    moveBackward();
    encoderValue = encoderValue+digitalRead(encoderOut);
    delay(10);
  }
  fullStop();
}

void rotate(float angle) { //rotate robot in radians
  
  float encoderGoal = fabs(angle*encoderConstantAngle);
  encoderValue = 0;
  
  if (angle >= 0) {
    while (encoderValue < encoderGoal) {
      rotateCCW();
      encoderValue = encoderValue+digitalRead(encoderOut);
      delay(10);
    }
  }
  else {
    while (encoderValue < encoderGoal) {
      rotateCW();
      encoderValue = encoderValue+digitalRead(encoderOut);
      delay(10);
    }
  }
  fullStop();
  
}

void moveTest() {
  moveForward();
  delay(2000);
  fullStop();
 
}

void moveForward() {
  setMotorLeft(255, true);
  setMotorRight(255, false);
}

void moveBackward() {
  setMotorLeft(255, false);
  setMotorRight(255, true);
}

void rotateCW() {
  setMotorLeft(255, true);
  setMotorRight(255, true);
}

void rotateCCW() {
  setMotorLeft(255, false);
  setMotorRight(255, false);
}

void fullStop() {
  setMotorLeft(0, false);
  setMotorRight(0, false);
}

void armChangePosition(int finalposition) {
      armServo.write(finalposition, 20, true);
}

void gripperOn() {
  gripperServo.write(10, 20, true);
}

void gripperOff() {
  gripperServo.write(50, 20, true);
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
