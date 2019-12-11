#define M1 3    //Enable pin for the 1.Motor
#define M2 9    //Enable pin for the 2.Motor
#define motor1_1 4
#define motor1_2 5
#define motor2_1 6
#define motor2_2 7

char connection;

void setup() 
{
  Serial.begin(9600);
  
  pinMode(M1, OUTPUT);
  pinMode(motor1_1, OUTPUT);
  pinMode(motor1_2, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(motor2_1, OUTPUT);
  pinMode(motor2_2, OUTPUT);

}

void loop() 
{

  if(Serial.available())
  {
    connection=Serial.read();
  
}

    switch (connection)
  {
    case '1':
    forwards();
    break;
    
    case '2':
    backwards();
    break;

    case '3':
    right();
    break;
    
    case'4':
    left();
    break;

    case'5':
   diagonal_left_forward();
   break;

    case'6':
   diagonal_right_forward();
    break;

    case'7':
    diagonal_left_backwards();
    break;

    case'8':
   diagonal_right_backwards();
    break;
    
    default:
    break;
  }

}



void forwards()
{

  digitalWrite(M1, HIGH);
  digitalWrite(M2, HIGH);
  
  digitalWrite(motor1_1, HIGH);   //M1
  digitalWrite(motor1_2, LOW);    //M1

  digitalWrite(motor2_1, HIGH);   //M2
  digitalWrite(motor2_2, LOW);    //M2
}


void backwards()
{

  digitalWrite(M1, HIGH);
  digitalWrite(M2, HIGH);
  
  digitalWrite(motor1_1, LOW);   //M1
  digitalWrite(motor1_2, HIGH);    //M1

  digitalWrite(motor2_1, LOW);   //M2
  digitalWrite(motor2_2, HIGH);    //M2
}

void left()
{

  digitalWrite(M1, HIGH);
  digitalWrite(M2, HIGH);
  
  digitalWrite(motor1_1, HIGH);   //M1
  digitalWrite(motor1_2, LOW);    //M1

  digitalWrite(motor2_1, LOW);   //M2
  digitalWrite(motor2_2, HIGH);    //M2
}

void right()
{

  digitalWrite(M1, HIGH);
  digitalWrite(M2, HIGH);
  
  digitalWrite(motor1_1, LOW);   //M1
  digitalWrite(motor1_2, HIGH);    //M1

  digitalWrite(motor2_1, HIGH);   //M2
  digitalWrite(motor2_2, LOW);    //M2
}

void diagonal_left_forward()
{
    digitalWrite(M1, HIGH);
    digitalWrite(M2, HIGH);
  
    analogWrite(motor1_1,255 );   
     analogWrite(motor1_2,0);    

     analogWrite(motor2_1,100 ); //CHECK THE SPEED LUCA <3
     analogWrite(motor2_2,0);    
}

void diagonal_right_forward()
{
     analogWrite(motor1_1,100 );   
     analogWrite(motor1_2,0);    

     analogWrite(motor2_1,255); //CHECK THE SPEED LUCA <3
     analogWrite(motor2_2,0);
}

void diagonal_left_backwards()
{
     analogWrite(motor1_1,0 );   
     analogWrite(motor1_2,255);    

     analogWrite(motor2_1,0 ); //CHECK THE SPEED LUCA <3
     analogWrite(motor2_2,100);
}

void diagonal_right_backwards()
{
       analogWrite(motor1_1,0 );   
     analogWrite(motor1_2,100);    

     analogWrite(motor2_1,0 ); //CHECK THE SPEED LUCA <3
     analogWrite(motor2_2,255);
}
