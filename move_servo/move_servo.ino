#include <Servo.h>

Servo myservo;
const int servo_pin = 3;
int current_position;

void setup() {
  // put your setup code here, to run once:
  myservo.attach(servo_pin);
}




void loop() {
  // put your main code here, to run repeatedly:

  //sentido horario
  for(int pos = current_position; pos <= 180; pos++){

    myservo.write(pos);
    current_position = pos;
    delay(15);
  }


  for(int pos = current_position; pos >= 0; pos--){
    myservo.write(pos)
    current_position = pos;
    delay(15);
  }
}
