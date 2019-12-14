//define variables needed for the purpose
#include <pt.h>
#include <stdio.h> 
#include <stdlib.h> 
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



int IR_left_state = 1000;
int IR_right_state = 1000;

int speed_m = 200;

long duration =0; 
long distance =0;
int req_distance =25  ; //we assume the required distance from the object is 30cm
int ch = 0;
//function to calculate distance, return the distance in cm

int distance_calculator(int tPin, int ePin);

int mil =100;



static int protothreading_line_follower(struct pt *pt1){


  static unsigned long lastTimeChecked = 0;
  PT_BEGIN(pt1);
  while(1){
    
    lastTimeChecked = millis();
    PT_WAIT_UNTIL(pt1, millis() - lastTimeChecked > 10); //in this case, the thread would be called every seconds. We do not want that.
    IR_left_state = analogRead(IR_left);
    IR_right_state = analogRead(IR_right);

    
    if(IR_right_state > 500 && IR_left_state < 500){
      right();
    }
    if(IR_right_state < 500 && IR_left_state > 500){
      left();
    }
    
    /*
     * Do something baby 
     * Oh yeah baby, did you check if I was following the line?
     */
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
    backwards();
    delay(mil);
    right();
    delay(mil/2);
  }else if(distance_calculator(trigPin_left, echoPin_left)<req_distance){
    Serial.println(2);
    stop_m();
    backwards();
    delay(mil);

    if(ch ==0){
      right();
      delay(mil/2);
      ch =1;
    }else{
      left();
      delay(mil/2);
      ch =0;
    }
    
  }else if(distance_calculator(trigPin_right, echoPin_right)<req_distance){
    Serial.println(3);
    stop_m();
    backwards();
    delay(mil/2);
    left();
    delay(mil);
    
    
  }else{
    Serial.println("I GO FORWARD");
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
// Prints the distance on the Serial Monitor
  //Serial.print("Distance: ");
  //Serial.print(distance_left);
  //Serial.println(" CM");
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


void backwards()
{

  analogWrite(M1, speed_m);
  analogWrite(M2,speed_m);
  
  /*analogWrite(motor1_1, -speed_m);   //M1
  analogWrite(motor1_2, speed_m);  

  analogWrite(motor2_1,-speed_m);   //M2
  analogWrite(motor2_2, speed_m);*/
  digitalWrite(motor1_1, HIGH);   //M1
  digitalWrite(motor1_2, LOW);    //M1

  digitalWrite(motor2_1, LOW);   //M2
  digitalWrite(motor2_2, HIGH);  

  delay(500);
}

void left()
{

  analogWrite(M1, speed_m);
  analogWrite(M2,speed_m);
 
  digitalWrite(motor1_1, LOW);   //M1
  digitalWrite(motor1_2, HIGH);    //M1

  digitalWrite(motor2_1, LOW);   //M2
  digitalWrite(motor2_2, HIGH);    //M2

  delay(1000);
}

void right()
{

  analogWrite(M1, speed_m);
  analogWrite(M2,speed_m);
  
  digitalWrite(motor1_1, HIGH);   //M1
  digitalWrite(motor1_2, LOW);    //M1

  digitalWrite(motor2_1, HIGH);   //M2
  digitalWrite(motor2_2, LOW);   //M2

  delay(1000);
}
