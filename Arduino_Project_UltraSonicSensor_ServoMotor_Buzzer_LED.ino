#include <Servo.h>
Servo myservo;

const int trigPin = 9;
const int echoPin = 10;
int buzzer = 8;
int pos = 0;
int LedPin = 2;
float timing = 0.0;
float distance = 0.0;

void setup() {
  myservo.attach(3);
  pinMode(trigPin, OUTPUT);
  pinMode(LedPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer,OUTPUT);
  Serial.begin(9600);
}


void distanceSensor(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  timing = pulseIn(echoPin, HIGH);
  distance = (timing * 0.034) / 2;

  if (distance <=30){
    tone(buzzer, 1000);
    digitalWrite(LedPin,HIGH);
    delay(20);
    digitalWrite(LedPin,LOW);

  }
  else{
    noTone(buzzer);       // stop sound

  }
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print("cm | ");
  Serial.print(distance / 2.54);
  Serial.println("in");
  


}
void loop() {

   for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);  
    distanceSensor();                     // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);   
    distanceSensor();                     // waits 15ms for the servo to reach the position
  }
  

}