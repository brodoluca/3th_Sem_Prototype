#include <pt.h>

/*
 * Simplest object dqetection algorithm. 
 * The program collects distances from the three ultrasound sensors on the front and checks wheter they are smaller than 30 cm
 * if so, it goes back for like 1s and then will turn either left or right. Simplest object recognition ever. Dont be Ledi Please. 
 * TO DO:
 * -Implement motor control functions
 * -line detection
 * - protothreading
 * -Please rasberry, give me some info (raspberry pi connection baby baby)
 * 
 * PLEASE DO NOT TOUCH THE PROTOTHREAD FUNCTION, WORK IN PROGRESS.Regarding the rest of the code, feel free to modify whatever you want (except
 * Kaan's face, my fists will be responsible for that:)))))) )
 * 
 */



// defines pins numbers for all three ultrasound
#define trigPin_left  5
#define echoPin_left  6

#define trigPin_center  8
#define echoPin_center  9

#define trigPin_right  11
#define echoPin_right 12

//define variables needed for the purpose
long duration =0; 
long distance =0;
int req_distance =29; //we assume the required distance from the object is 30cm

//function to calculate distance, return the distance in cm

int distance_calculator(int tPin, int ePin);

/*DO NOT FUCKING TOUCH, LUCA
static struct pt pt1;


static int protothreading_line_follower(struct pt *pt1){


  static unsigned long lastTimeChecked = 0;
  PT_BEGIN(pt);
  while(1){
    
    lastTimeChecked = millis();
    PT_WAIT_UNTIL(pt, millis() - lastTimeChecked > 1000); //in this case, the thread would be called every seconds. We do not want that.
    /*
     * Do something baby 
     * Oh yeah baby, did you check if I was following the line?
     
  }
  PT_END(pt);
}
*/



void setup() {
  pinMode(trigPin_left, OUTPUT);
  pinMode(echoPin_left, INPUT);
  pinMode(trigPin_center, OUTPUT); 
  pinMode(echoPin_center, INPUT);
  pinMode(trigPin_right, OUTPUT);
  pinMode(echoPin_right, INPUT);
  Serial.begin(9600);
  
}

void loop() {
  //In case Gordan does not understand (I love you sweetheart), Kaan will susbtitute the serial prints with the functions to control the motors
  if(distance_calculator(trigPin_center, echoPin_center)<req_distance){
    Serial.println("I GO BACK");
    delay(2000);
    Serial.println("NOW I GO RIGHT"); //can be either right or left, it doesn't matter.
    delay(1000);
  }else if(distance_calculator(trigPin_left, echoPin_left)<req_distance){
    Serial.println("I GO BACK");
    delay(1000);
    Serial.println("I GO RIGHT");
  }else if(distance_calculator(trigPin_right, echoPin_right)<req_distance){
    Serial.println("I GO BACK");
    delay(1000);
    Serial.println("I GO LEFT");
  }else{
    Serial.println("I GO FORWARD");
  }

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
