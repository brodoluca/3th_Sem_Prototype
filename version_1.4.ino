//include some libraries
#include <pt.h>
#include <stdio.h> 
#include <stdlib.h> 
//define variables needed for the purpose
#define trigPin_left  13
#define echoPin_left  2

#define trigPin_center  8
#define echoPin_center  10

#define trigPin_right  11
#define echoPin_right 12

#define M1 3    //Enable pin for the 1.Motor
#define M2 9    //Enable pin for the 2.Motor
#define motor1_1 4
#define motor1_2 5


#define motor2_1 6
#define motor2_2 7


#define IR_left  A0
#define IR_right  A1


//just for testing
int IR_left_state = 1000;
int IR_right_state = 1000;

int speed_m = 180;

long duration =0; 
long distance =0;
int req_distance =25  ; //we assume the required distance from the object is 25cm
int ch = 0;

/*function to calculate distance, 
 * return the distance in cm,
 * tPin is the triggering pin, ePin is the echo pin
 */


int distance_calculator(int tPin, int ePin);

/*functions to move motors in different directions
 * mil is the delay, so how much should they rotate
 */

void forwards(int mil);
void backwards(int mil);
void left(int mil);
void right(int mil);
void both(int mil);


long time_left;
long time_center;
long time_right;
long time_ob;

int mil =500;
int time_de = 900;
int obstacle = 0;
static struct pt pt1;
static unsigned long lastTimeChecked = 0;
static int protothreading_object(struct pt *pt1){
  PT_BEGIN(pt1);
  while(1){
    
    lastTimeChecked = millis();
    PT_WAIT_WHILE(pt1, millis() <50+ lastTimeChecked);
    Serial.println("DE");
    //In case Gordan does not understand (I love you sweetheart), Kaan will susbtitute the serial prints with the functions to control the motors
  if(distance_calculator(trigPin_center, echoPin_center)<req_distance){
    stop_m();
    obstacle =1;
    //backwards(5);
    //forwards();

    //right(mil/2);
    obstacle_detected(time_de);



  }else if(distance_calculator(trigPin_left, echoPin_left)<req_distance){
    
    stop_m();
    //right(mil/2);
    obstacle = 1;
    obstacle_detected(time_de);
    
  }else if(distance_calculator(trigPin_right, echoPin_right)<req_distance){


    stop_m();
    //left(mil/2);
    obstacle = 1;
    obstacle_detected(time_de);
    
    
  }else{
    obstacle =0 ;
    //forwards();
    
  }
  
  PT_END(pt1);
  }
}


void setup() {
  pinMode(trigPin_left, OUTPUT);
  pinMode(echoPin_left, INPUT);
  pinMode(trigPin_center, OUTPUT); 
  pinMode(echoPin_center, INPUT);
  pinMode(trigPin_right, OUTPUT);
  pinMode(echoPin_right, INPUT);
  pinMode(IR_left, INPUT);
  pinMode(IR_right, INPUT);
  Serial.begin(9600);
  delay(500);
  PT_INIT(&pt1);
  protothreading_object(&pt1);
  backwards(50);
}



void loop() {
  // put your main code here, to run repeatedly:
  protothreading_object(&pt1);
  IR_left_state =digitalRead(IR_left);
  IR_right_state = digitalRead(IR_right);
  Serial.println(IR_right_state);
  if(IR_right_state ==0 && IR_left_state == 1 && obstacle!=1) {
      left(1);
  }
  else if (IR_right_state ==1 && IR_left_state == 0 &&obstacle!=1){
      right(1);
  }
  else if(obstacle!=1){
      forwards();
  }else if(IR_right_state ==1 && IR_left_state == 1 &&obstacle!=1){
    both(50);
    
  }

}






void stop_m(){
  digitalWrite(M1, HIGH);
  digitalWrite(M2, HIGH);
  analogWrite(motor2_1,0);   //M2
  analogWrite(motor2_2, 0);
  analogWrite(motor1_1, 0);   //M1
  analogWrite(motor1_2, 0);
}

int distance_calculator(int tPin, int ePin){
  digitalWrite(tPin, LOW);
  delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(tPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(tPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(ePin, HIGH);
// Calculating the distance
  distance= duration*0.034/2;

  return distance;

}




void forwards()
{

 analogWrite(M1, speed_m + 40);
  //analogWrite(M2, speed_m);
  analogWrite(M2, speed_m);
  digitalWrite(motor1_1, LOW);   //M1
  digitalWrite(motor1_2, HIGH);    //M1
    //analogWrite(motor1_1, 255);
    //analogWrite(motor2_2, 255);
    digitalWrite(motor2_1, HIGH);   //M2
    digitalWrite(motor2_2, LOW); 
  //M2
}


void backwards(int mil)
{
  
  analogWrite(M1, speed_m);
  analogWrite(M2,speed_m);

  digitalWrite(motor1_1, HIGH);   //M1
  digitalWrite(motor1_2, LOW);    //M1

  digitalWrite(motor2_1, LOW);   //M2
  digitalWrite(motor2_2, HIGH);  

  //delay(mil);
  
}

void left(int mil)
{
  time_left = millis();
  while(millis()<mil + time_left){
    
    analogWrite(M1, int((speed_m + 30) * 80/100));
    analogWrite(M2,int(speed_m*50/100) );
 
    digitalWrite(motor1_1, LOW);   //M1
    digitalWrite(motor1_2, HIGH);    //M1

    digitalWrite(motor2_1,  LOW ); //M2
    digitalWrite(motor2_2, HIGH);    //M2
  }
  
  
}

void right(int mil)
{
  time_right = millis();
   while(millis()<mil+time_right){
    analogWrite(M1, int((speed_m+30)*50/100));
    analogWrite(M2,int(speed_m *80/100));
  
    digitalWrite(motor1_1, HIGH);   //M1
    digitalWrite(motor1_2, LOW);    //M1

    digitalWrite(motor2_1, HIGH);   //M2
    digitalWrite(motor2_2, LOW);   //M2

  }
  

}




void obstacle_detected(int time_delay){
  time_ob = millis();
  while(millis()<time_delay + time_ob){
    
    analogWrite(M1, speed_m);
  analogWrite(M2,speed_m);

  digitalWrite(motor1_1, HIGH);   //M1
  digitalWrite(motor1_2, LOW);    //M1

  digitalWrite(motor2_1, HIGH);   //M2
  digitalWrite(motor2_2, LOW);  

  }
}

void both(int mil)
{ 
  // Uses the time_left variable, but this part is moves tha car forwards a bit
  time_left = (millis())/2;
  while(millis()<mil + time_left){
    
    analogWrite(M1, speed_m + 40);
  //analogWrite(M2, speed_m);
  analogWrite(M2, speed_m);
  digitalWrite(motor1_1, LOW);   //M1
  digitalWrite(motor1_2, HIGH);    //M1
    //analogWrite(motor1_1, 255);
    //analogWrite(motor2_2, 255);
    digitalWrite(motor2_1, HIGH);   //M2
    digitalWrite(motor2_2, LOW); 
  //M2
  
  }

  // time_right and time_left are reset
  time_left = millis();
  time_right = millis();
  int alternator = 0;
  if (alternator == 0){
  while(millis()<mil+time_right){
    analogWrite(M1, int(speed_m*65/100));
    analogWrite(M2,speed_m);
  
    digitalWrite(motor1_1, HIGH);   //M1
    digitalWrite(motor1_2, LOW);    //M1

    digitalWrite(motor2_1, HIGH);   //M2
    digitalWrite(motor2_2, LOW);   //M2
    
    }
  
  alternator = 1;
  }
  
  else
  {
    while(millis()<mil + time_left){
    
    analogWrite(M1, speed_m);
    analogWrite(M2,int(speed_m*65/100) );
 
    digitalWrite(motor1_1, LOW);   //M1
    digitalWrite(motor1_2, HIGH);    //M1

    digitalWrite(motor2_1,  HIGH ); //M2
    digitalWrite(motor2_2, LOW);    //M2
    }
  
  alternator = 0;
  }
  
}
  
  //delay(mil);
  
