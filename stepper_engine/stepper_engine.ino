
#include <Stepper.h>
#define REDUCTION 64

const int fullStepRevolution = 32;
const int l1 = 5;
const int l2 = 6;
const int l3 = 7;
const int l4 = 8;

Stepper myStepper(fullStepRevolution, l1, l3, l2, l4);

void moveEngine(int sense){
  for(int i = 0; i < fullStepRevolution; i++){
    myStepper.step(REDUCTION * sense);
  }
}



void setup() {
  // put your setup code here, to run once:

  myStepper.setSpeed(120);

}

void loop() {
  





}
