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

const unsigned int mspeed = 170;//motor speed forward
const unsigned int mspeed_rot = 230; //motot speed when adjust the robot position
const unsigned int mdelay = 120; //waiting time for a new loop to start.
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

  // Wait for Serial Monitor to be opened
  while (!Serial)
  {
    //do nothing
  }

  // Set initial speed for both motors
  motors.setSpeed(200);
}

void loop(){
  //printing values of the sensors to the serial monitor
  Serial.println("-----");
  Serial.print("L:");
  Serial.println(digitalRead(left));
  Serial.print("C:");
  Serial.println(digitalRead(center));
  Serial.print("R:");
  Serial.println(digitalRead(right));

  //line not detected by both
  if(digitalRead(left)==1 && digitalRead(right)==1){
    Serial.println("line not detected by both");
    //Forward
    motors.setSpeed(mspeed);
    motors.forward();
    
  }
  //line detected by left sensor
  else if(digitalRead(left)==0 && digitalRead(right)==1){
    Serial.println("line detected by left");
    //turn left
    motors.setSpeed(mspeed_rot);
    motors.forwardA();
    motors.backwardB();    
  }
  //line detected by right sensor
  else if(digitalRead(left)==1 && digitalRead(right)==0){
    Serial.println("line detected by right");
    //turn right
    motors.setSpeed(mspeed_rot);
    motors.forwardB();
    motors.backwardA();   
  }
  //line detected by both
  else if(digitalRead(left)==0 && digitalRead(right)==0){
    Serial.println("stop");
    //stop
    motors.stop();   
  }
  delay(mdelay);
  motors.stop();
  printSomeInfo();
}

/*
Print some informations in Serial Monitor
*/
void printSomeInfo()
{
  Serial.print("Motor A is moving = ");
  Serial.print(motors.isMovingA() ? "YES" : "NO");
  Serial.print(" at speed = ");
  Serial.println(motors.getSpeedA());
  Serial.print("Motor B is moving = ");
  Serial.print(motors.isMovingB() ? "YES" : "NO");
  Serial.print(" at speed = ");
  Serial.println(motors.getSpeedB());
}
