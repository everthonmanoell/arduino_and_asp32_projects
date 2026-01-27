#include <Servo.h>
#define REDUCTION 64

const int fullStepRevolution = 32;
Stepper myStepper(fullStepRevolution, 8,10,9,11);
const int potenciometro_pin = A0;



void setup(){
  myStepper.setSpeed(120);
  pinMode(potenciometro_pin, INPUT);
  pinMode(button_pin, INPUT_PULLUP);
}


void loop(){
  int potenciometro_value = analogRead(potenciometro_pin);
  int value = map(potenciometro_value, 0, 1023, 120, 520);
  myStepper.setSpeed(value);
  int buttonPressed = digitalRead(button_pin);

  if(buttonPressed == LOW){ //LOW
  //Gira o motor no sentido horario
    giraMotor(1);
    delay(500);

  }else{
     //Gira o motor no sentido anti-horario
      giraMotor(-1);
      delay(500);
  }
  
  
  
}


void giraMotor(int sentido) {

  for (int i = 0; i<fullStepRevolution; i++){
    myStepper.step(REDUCTION * sentido);
  }

}