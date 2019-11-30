  int vSpeed = 110;        // Can be edited, max speed 255
  int turn_speed = 230;    // Can be edited, max speed 255
  int turn_delay = 10;     // Do not edit the delay
  
// Motor   
  const int motor1_1      = 8;  
  const int motor1_2      = 10; 
  const int motor1_speed  = 9;
  const int motor2_1      = 12; 
  const int motor2_2      = 13; 
  const int motor2_speed  = 11;

// IR Connection
  const int IR_left = A0;
  const int IR_right = A1;
  int IR_left_state;
  int IR_right_state;


// Primary Initiation
void setup() {
  pinMode(motor1_1, OUTPUT);
  pinMode(motor1_2, OUTPUT);
  pinMode(motor2_1, OUTPUT);
  pinMode(motor2_2, OUTPUT);

  Serial.begin(9600);

  delay(3000);
  
}




// #Start Loop Initiation
void loop() {

// IR Input
IR_left_state = analogRead(IR_left);
IR_right_state = analogRead(IR_right);



// Motor Functions Dependant on the IR Input

// Forward 
if(IR_right_state > 500 && IR_left_state > 500)
{
  Serial.println("forward");

  digitalWrite (motor1_2,LOW);
  digitalWrite(motor1_1,HIGH);                       
  digitalWrite (motor2_2,HIGH);
  digitalWrite(motor2_1,LOW);

  analogWrite (motor1_speed, vSpeed);
  analogWrite (motor2_speed, vSpeed);

  delay(turn_delay);
  
}

//  Right
if(IR_right_state > 500 && IR_left_state < 500)
{
  Serial.println("right");

  digitalWrite (motor1_1,LOW);
  digitalWrite(motor1_2,HIGH);                       
  digitalWrite (motor2_1,LOW);
  digitalWrite(motor2_2,HIGH);

  analogWrite (motor1_speed, vSpeed);
  analogWrite (motor2_speed, turn_speed);
  
}

// Left
if(IR_right_state < 500 && IR_left_state > 500)
{
  Serial.println("turning left");
  
  digitalWrite (motor1_1,HIGH);
  digitalWrite(motor1_2,LOW);                       
  digitalWrite (motor2_1,HIGH);
  digitalWrite(motor2_2,LOW);

  analogWrite (motor1_speed, turn_speed);
  analogWrite (motor2_speed, vSpeed);

  delay(turn_delay);
}

// Break
if(IR_right_state < 500 && IR_left_state < 500)
{ 
  Serial.println("stop");
  
  analogWrite (motor1_speed, 0);
  analogWrite (motor2_speed, 0);
  
}

// #End Loop Initiation
 
}
