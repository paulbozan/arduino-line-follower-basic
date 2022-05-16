/*
L298 Lib Source  : https://github.com/AndreaLombardo/L298N/
*/

#include <L298NX2.h>

// Pin definition
const unsigned int EN_A = 6;
const unsigned int IN1_A = 5;
const unsigned int IN2_A = 4;

const unsigned int IN1_B = 3;
const unsigned int IN2_B = 2;
const unsigned int EN_B = 9;

const unsigned int mspeed = 180;//motor speed forward
const unsigned int mspeed_rot = 235; //motot speed when adjust the robot position
const unsigned int mdelay = 1; //waiting time for a new loop to start.
//defining pins and variables
#define left A1
#define center A2
#define right A3


// Initialize both motors
L298NX2 motors(EN_A, IN1_A, IN2_A, EN_B, IN1_B, IN2_B);

void setup()
{
  //declaring pin types
  pinMode(left,INPUT);
  pinMode(right,INPUT);
  
  // Used to display information
  Serial.begin(9600);
  // Set initial speed for both motors
  motors.setSpeed(200);
}

void loop(){
  //line not detected by both
  if(digitalRead(left)==1 && digitalRead(right)==1){
    motors.setSpeed(mspeed);
    motors.forward();
    
  }
  //line detected by left sensor
  else if(digitalRead(left)==0 && digitalRead(right)==1){
    motors.setSpeed(mspeed_rot);
    motors.forwardA();
    motors.backwardB();    
  }
  //line detected by right sensor
  else if(digitalRead(left)==1 && digitalRead(right)==0){
    motors.setSpeed(mspeed_rot);
    motors.forwardB();
    motors.backwardA();   
  }
  //line detected by both
  else if(digitalRead(left)==0 && digitalRead(right)==0){
    motors.stop();   
  }
  delay(mdelay);
  motors.stop();
}
