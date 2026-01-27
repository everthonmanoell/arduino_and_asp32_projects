#include <Servo.h>

const int trigger = 13;
const int echo = 12;
const int step_motor = 5;

const float limiar_open = 70;
const float limiar_close = 70;

int memory = 0;

Servo myservo;
int pos = 0;
void setup() {
  myservo.attach(step_motor);

  pinMode(trigger, OUTPUT); //pino de saída
  pinMode(echo, INPUT); //pino de entrada

  Serial.begin(9600);
}
void loop() {

  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);//deixa TRIGGER em HIGH por 10ms
  digitalWrite(trigger, LOW);
  int duration = pulseIn(echo, HIGH); //quanto tempo ECHO== HIGH
  float distance = duration * 0.034 / 2;

  if (distance < limiar_close){
    for (pos = memory; pos <= 180; pos += 1) {
    myservo.write(pos);
    //Serial.print("open: ");
    Serial.println(pos);
    memory = pos;
    delay(15);
    }

  }else{

      for (pos = memory; pos >= 0; pos -= 1) {
        myservo.write(pos);
        memory = pos;
        delay(15);
    }
    
  }
  
}
