void servoInit()
{
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);    // standard 50 hz servo
  myservo.attach(servoPin, 500, 2400); // attaches the servo on pin 18 to the servo object
  // using default min/max of 1000us and 2000us
  // different servos may require different min/max settings
  // for an accurate 0 to 180 sweep
}


void servoAngle(int pos)
{
  myservo.write(last); 
  delay(100);
if(last<=pos)
  {
  for (last;last <= pos;last += 1) 
  {
    Serial.println(last);
    Serial.println(pos);
    myservo.write(last);   
    delay(10);        
  }
  }
  else if(last>pos)
  {
    for (last;last >= pos;last -= 1) 
  {
    Serial.println(last);
    Serial.println(pos);
    myservo.write(last);   
    delay(10);             
  }
  } 
  last=pos; 
}
