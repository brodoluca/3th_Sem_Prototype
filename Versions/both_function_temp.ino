void both(int mil)
{ 
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
