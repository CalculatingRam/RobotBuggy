#include <Servo.h>
#include <NewPing.h>

#define in1 4 //Motor1  L298
#define in2 5 //Motor1  L298
#define in3 6 //Motor2  L298
#define in4 7 //Motor2  L298
#define enA 3 //Enable1 L298
#define enB 8 //Enable2 L298
#define LeftIR A3 //IR sensor on the left
#define RightIR A4 //IR sensor on the right
#define ECHO_PIN A2 //Echo Pin
#define TRIGGER_PIN A1 //Trigger Pin
#define MAX_DISTANCE 250 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 250cm.

int Set=15;
int distance_L, distance_F, distance_R; 
Servo servo_motor;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup(){
Serial.begin(9600);
pinMode(RightIR, INPUT); // declare IR sensor on the right as input  
pinMode(LeftIR, INPUT); // declare IR sensor on the left as input
pinMode(ECHO_PIN, INPUT );// declare ultrasonic sensor Echo pin as input
pinMode(TRIGGER_PIN, OUTPUT); // declare ultrasonic sensor Trigger pin as output  
pinMode(in1, OUTPUT); // declare L298 Pin in1 as output  
pinMode(in2, OUTPUT); // declare L298 Pin in2 as output  
pinMode(in3, OUTPUT); // declare L298 Pin in3 as output    
pinMode(in4, OUTPUT); // declare L298 Pin in4 as output 
pinMode(enA, OUTPUT); // declare L298 Pin enA as output   
pinMode(enB, OUTPUT); // declare L298 Pin enB as output  
analogWrite(enA, 200); // Motor1 Speed 
analogWrite(enB, 200); // Motor2 Speed 
servo_motor.attach(10); //attaches the servo motor to pin 10

for (int angle = 70; angle <= 140; angle += 5)  {
   servo_motor.write(angle);
   }
for (int angle = 140; angle >= 0; angle -= 5)  {
   servo_motor.write(angle);
   }
for (int angle = 0; angle <= 70; angle += 5)  {
   servo_motor.write(angle);
   }
distance_F = readPing();
delay(500);
}
void loop(){  
distance_F = readPing();
Serial.print("D F=");
Serial.println(distance_F);
//if Right Sensor and Left Sensor are at White color then it will call forward function
 if((digitalRead(RightIR) == 0)&&(digitalRead(LeftIR) == 0)){
  if(distance_F > Set){
    forward();
    }
  else{
    Check_side();
  }  
 
 }  
 
//if Right Sensor is Black and Left Sensor is White then it will call turn Right function
else if((digitalRead(RightIR) == 1)&&(digitalRead(LeftIR) == 0)){
  turnRight();
  }  
//if Right Sensor is White and Left Sensor is Black then it will call turn Left function
else if((digitalRead(RightIR) == 0)&&(digitalRead(LeftIR) == 1)){
  turnLeft();
  } 
    
delay(10);
}


long readPing(){          //Ultrasonic Sensor
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  long time = pulseIn (ECHO_PIN, HIGH);
  return time / 29 / 2;
}
void compareDistance(){
    if(distance_L > distance_R){
      turnLeft();
      delay(500);
      forward();
     delay(600);
      turnRight();
      delay(500);
     forward();
     delay(600);
     turnRight();
     delay(400);
    }else{
        turnRight();
        delay(500);
        forward();
        delay(600);
        turnLeft();
        delay(500);
        forward();
        delay(600);  
        turnLeft();
        delay(400);
    }
}
void Check_side(){
    stop();
    delay(100);
 for (int angle = 70; angle <= 140; angle += 5)  {
   servo_motor.write(angle);
  }
  delay(300);
  distance_R = readPing();
  Serial.print("D R=");
  Serial.println(distance_R);
  delay(100);
  for (int angle = 140; angle >= 0; angle -= 5)  {
   servo_motor.write(angle);
  }
  delay(500);
  distance_L = readPing();
  Serial.print("D L=");
  Serial.println(distance_L);
  delay(100);
 for (int angle = 0; angle <= 70; angle += 5)  {
   servo_motor.write(angle);
  }
  delay(300);
  compareDistance();
}
void forward(){  //To move forward
digitalWrite(in1, LOW); //Left Motor backward Pin 
digitalWrite(in2, HIGH); //Left Motor forward Pin 
digitalWrite(in3, HIGH); //Right Motor forward Pin 
digitalWrite(in4, LOW); //Right Motor backward Pin 
}
void backward(){ //To move backward
digitalWrite(in1, HIGH); //Left Motor backward Pin 
digitalWrite(in2, LOW); //Left Motor forward Pin 
digitalWrite(in3, LOW); //Right Motor forward Pin 
digitalWrite(in4, HIGH); //Right Motor backward Pin 
}
void turnRight(){ //To turn right
digitalWrite(in1, LOW); //Left Motor backward Pin 
digitalWrite(in2, HIGH); //Left Motor forward Pin 
digitalWrite(in3, LOW); //Right Motor forward Pin 
digitalWrite(in4, HIGH); //Right Motor backward Pin 
}
void turnLeft(){ //To turn left
digitalWrite(in1, HIGH); //Left Motor backward Pin 
digitalWrite(in2, LOW); //Left Motor forward Pin 
digitalWrite(in3, HIGH); //Right Motor forward Pin 
digitalWrite(in4, LOW); //Right Motor backward Pin 
}
void stop(){ //To stop
digitalWrite(in1, LOW); //Left Motor backward Pin 
digitalWrite(in2, LOW); //Left Motor forward Pin 
digitalWrite(in3, LOW); //Right Motor forward Pin 
digitalWrite(in4, LOW); //Right Motor backward Pin 
}