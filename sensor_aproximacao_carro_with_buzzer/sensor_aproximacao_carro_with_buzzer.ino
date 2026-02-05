#include <Servo.h>

#include <Stepper.h>

// C++ code
//

#define NOTE_D6  1175

const int led_pin = 13;
const int button_pin = 12;
const int ldr_pin = A1;
const int buzzer_pin = 8;

const int trigger_pin = 10;
const int echo_pin = 11;

const int green_pin = 9;
const int yellow_pin = 7;



//Ultrasonic ultrasonic(trigger_pin, echo_pin);

enum State{
  VERDE,
  VERMELHO,
  AMARELO
}state;



int ultrasonic(){
  digitalWrite(trigger_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_pin, LOW);
  int duration = pulseIn(echo_pin, HIGH);
  float distance = duration * 0.034 / 2;
  return distance;
}

void setup()
{
  pinMode(led_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  pinMode(yellow_pin, OUTPUT);
  
  pinMode(button_pin, INPUT_PULLUP);
  pinMode(buzzer_pin, OUTPUT);
  
  pinMode(echo_pin, INPUT);
  pinMode(trigger_pin, OUTPUT);
  
  Serial.begin(9600);
}

void loop()
{
  
  float ultrasonic_response = ultrasonic();
  
  if(ultrasonic_response > 200){
    // green light on
  	digitalWrite(green_pin, HIGH);
    digitalWrite(led_pin, LOW);
    digitalWrite(yellow_pin, LOW);
    tone(buzzer_pin, NOTE_D6, 500);
    delay(1000);
    noTone(buzzer_pin);
  
  }else if (ultrasonic_response < 100){
  	//yellow light on
    digitalWrite(green_pin, LOW);
    digitalWrite(led_pin, LOW);
    digitalWrite(yellow_pin, HIGH);
    tone(buzzer_pin, NOTE_D6, 250);
    delay(1000);
    noTone(buzzer_pin);
  
  }else{
  //red light on
    digitalWrite(green_pin, LOW);
    digitalWrite(led_pin, HIGH);
    digitalWrite(yellow_pin, LOW);
    tone(buzzer_pin, NOTE_D6, 100);
    delay(1000);
    noTone(buzzer_pin);
  
  }
  
  
  
  
}