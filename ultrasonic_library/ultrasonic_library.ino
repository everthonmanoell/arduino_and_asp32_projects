#include <Ultrasonic.h>

#define trigger 12
#define echo 13

// Ultrasonic ultrasonic(trigger, echo);
int distancia;
int duration;

void setup() {
  // put your setup code here, to run once:
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  // distance = ultrasonic.read();
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(triger, HIGH);
  delayMicroseconds(10);
  digitalWrite(triger, LOW)
  duration = pulseIn(echo, HIGH);
  distance = duration * 0.034 / 2;


  
}
