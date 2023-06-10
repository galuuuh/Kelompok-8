/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 https://www.arduino.cc/en/Tutorial/LibraryExamples/Sweep
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int trigPin = 10;
int echoPin = 11;
int led = 13;
int buzz = 9;
long duration;
int distance;
int vcc = 2;

void setup() {
  myservo.attach(3);  // attaches the servo on pin 9 to the servo object
  pinMode (led, OUTPUT);
  pinMode (trigPin, OUTPUT);
  pinMode (echoPin, INPUT);
  pinMode (buzz, OUTPUT);
  pinMode (vcc, OUTPUT);
  digitalWrite(vcc, 1);
}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  distance= duration*0.034/2;


  if (distance <= 5){
      digitalWrite(led, 1);
      digitalWrite(buzz, 1);
  } else {
    digitalWrite(led, 0);
    digitalWrite(buzz, 0);
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
    }
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15 ms for the servo to reach the position
    }
  }
  
}
