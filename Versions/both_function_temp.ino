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
