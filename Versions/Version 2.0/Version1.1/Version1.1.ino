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

int speed_m = 200;

long duration =0; 
long distance =0;
int req_distance =25  ; //we assume the required distance from the object is 30cm
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




int mil =500;



static int protothreading_line_follower(struct pt *pt1){


  static unsigned long lastTimeChecked = 0;
  PT_BEGIN(pt1);
  while(1){
    
    lastTimeChecked = millis();
    PT_WAIT_UNTIL(pt1, millis() - lastTimeChecked > 10); 
    IR_left_state = analogRead(IR_left);
    IR_right_state = analogRead(IR_right);

    
    while(IR_right_state > 500 && IR_left_state < 500){
      right(100);
    }
    while(IR_right_state < 500 && IR_left_state > 500){
      left(100);
    }
    
    if (IR_right_state <500 && IR_left_state<500){
      backwards(5);
      right(5);
      
      
    }
  }
  PT_END(pt1);
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
  
  
}

void loop() {
  
  //In case Gordan does not understand (I love you sweetheart), Kaan will susbtitute the serial prints with the functions to control the motors
  if(distance_calculator(trigPin_center, echoPin_center)<req_distance){
    stop_m();
    Serial.println("1");
    backwards(mil);
    //delay(mil);
    right(mil/2);
    
  }else if(distance_calculator(trigPin_left, echoPin_left)<req_distance){
    
    stop_m();
    backwards(mil);
    

    if(ch ==0){
      right(mil/2);
      //delay(mil/2);
      ch =1;
    }else{
      left(mil/2);
      ch =0;
    }
    
  }else if(distance_calculator(trigPin_right, echoPin_right)<req_distance){

    stop_m();
    backwards(mil/2);
  
    left(mil*2);
   
    
    
  }else{
    
    forwards();
  }


  //forwards();

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

 digitalWrite(M1, speed_m);
  digitalWrite(M2, speed_m);
  
  digitalWrite(motor1_1, LOW);   //M1
  digitalWrite(motor1_2, HIGH);    //M1

  digitalWrite(motor2_1, HIGH);   //M2
  digitalWrite(motor2_2, LOW);    //M2
}


void backwards(int mil)
{

  analogWrite(M1, speed_m);
  analogWrite(M2,speed_m);

  digitalWrite(motor1_1, HIGH);   //M1
  digitalWrite(motor1_2, LOW);    //M1

  digitalWrite(motor2_1, LOW);   //M2
  digitalWrite(motor2_2, HIGH);  

  delay(mil);
}

void left(int mil)
{

  analogWrite(M1, speed_m);
  analogWrite(M2,speed_m);
 
  digitalWrite(motor1_1, LOW);   //M1
  digitalWrite(motor1_2, HIGH);    //M1

  digitalWrite(motor2_1, LOW);   //M2
  digitalWrite(motor2_2, HIGH);    //M2

  delay(mil);
}

void right(int mil)
{

  analogWrite(M1, speed_m);
  analogWrite(M2,speed_m);
  
  digitalWrite(motor1_1, HIGH);   //M1
  digitalWrite(motor1_2, LOW);    //M1

  digitalWrite(motor2_1, HIGH);   //M2
  digitalWrite(motor2_2, LOW);   //M2

  delay(mil);
}
