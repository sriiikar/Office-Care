#include<Servo.h>
Servo welc; // Welcome Door
Servo sanitizer; // Sanitizer Dispenser
Servo pass; // Pass Door

void setup() 
{
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(13,OUTPUT);
  welc.attach(5);
  sanitizer.attach(6);
  pass.attach(9);
  Serial.begin(9600); // Initialize serial communication
}

void loop() 
{
  // Ultrasonic sensor for the working of welcome door
  long duration1, cm1;

  pinMode(7, OUTPUT);
  digitalWrite(7, LOW);
  delayMicroseconds(2);
  digitalWrite(7, HIGH);
  delayMicroseconds(5);
  digitalWrite(7, LOW);

  pinMode(7, INPUT);
  duration1 = pulseIn(7, HIGH);

  cm1 = duration1 / 29 / 2;
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  delay(100);
  
  // Controlling Welcome Door
  if(cm1 <=100) 
  {
    welc.write(90);
    Serial.println("Welcome");
  }
  else
  {
    welc.write(0);
  }
  
  
  // Ultrasonic sensor for Sanitizer dispensing
  long duration2, cm2;

  pinMode(8, OUTPUT);
  digitalWrite(8, LOW);
  delayMicroseconds(2);
  digitalWrite(8, HIGH);
  delayMicroseconds(5);
  digitalWrite(8, LOW);

  pinMode(8, INPUT);
  duration2 = pulseIn(8, HIGH);

  cm2 = duration2 / 29 / 2;
  
  // Sanitizer Dispensing
  sanitizer.write(0); // Set the motor angle to 0
  if(cm2 <= 50)
  {
    sanitizer.write(90);
    Serial.println("Sanitizer Dispensed");
    delay(3000);
    sanitizer.write(0);
  }
  else
  {
    sanitizer.write(0);
    delay(10);
  }
  
  // Pass Door
  pass.write(0); // Set the motor angle to 0
  if(cm2 <=50)
  {
    delay(3000);
    pass.write(90);
    Serial.println("PASS DOOR OPEN");
    
      digitalWrite(11,LOW); // RED LED LOW
      digitalWrite(13,LOW); // BUZZER LOW
    
      digitalWrite(10,HIGH); // GREEN LED BLINK THRICE
      delay(1500);
      digitalWrite(10,LOW);
      delay(1500);
      digitalWrite(10,HIGH);
      delay(1500);
      digitalWrite(10,LOW);
      delay(1500);
      digitalWrite(10,HIGH);
      delay(1500);
      digitalWrite(10,LOW);
    delay(1000);
    
    pass.write(0);
      digitalWrite(10,LOW);
      digitalWrite(11,HIGH);
      digitalWrite(13,HIGH);
      Serial.println("DOOR CLOSED!");
    delay(1000);
  }
}
