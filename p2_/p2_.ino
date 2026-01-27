const int buzzer_pin = 27;
const int led_pin = 13;
const int button_pin = 26;
const int motor_pin = 14;
const int ldl_pin = 12;
#include <ESP32Servo.h>
Servo myservo;

#define NOTE_C7  2093

//Display Segmento
#define A 18
#define B 5
#define C 4
#define D 16
#define E 17
#define F 19
#define G 21

bool sete_segmentos[10][7] = { 
  { 1,1,1,1,1,1,0 }, // = Digito 0
  { 0,1,1,0,0,0,0 }, // = Digito 1
  { 1,1,0,1,1,0,1 }, // = Digito 2
  { 1,1,1,1,0,0,1 }, // = Digito 3
  { 0,1,1,0,0,1,1 }, // = Digito 4
  { 1,0,1,1,0,1,1 }, // = Digito 5
  { 1,0,1,1,1,1,1 }, // = Digito 6
  { 1,1,1,0,0,0,0 }, // = Digito 7
  { 1,1,1,1,1,1,1 }, // = Digito 8
  { 1,1,1,1,0,1,1 }, // = Digito 9
};

void escreverNumero(int numero) {
  bool* display = sete_segmentos[numero];
  digitalWrite(A,display[0]);
  digitalWrite(B,display[1]);
  digitalWrite(C,display[2]);
  digitalWrite(D,display[3]);
  digitalWrite(E,display[4]);
  digitalWrite(F,display[5]);
  digitalWrite(G,display[6]);

}


void test_button_with_led(){

  int button_pressed = digitalRead(button_pin);

    Serial.println(button_pressed);

    if(button_pressed == LOW)
    {
      digitalWrite(led_pin, HIGH);
      delay(1000);


    } else {
      digitalWrite(led_pin, LOW);
      delay(1000);

    }

}


void buzzer_function(int pin, int frequency, int duration, int m_pause){

  tone(pin, frequency, duration);
  int pause = duration * m_pause;
  delay(pause);
  noTone(pin);
  
}

void test_display_7_s(){
  
  for(int i = 0; i < 10; i++)
  {
    Serial.println(i);
    escreverNumero(i);
    delay(1000);
  }

}

void test_servo_motor(){
  //sentido horário
  for(int pos = 0; pos <= 180; pos++){
            myservo.write(pos);
          }

  //sentido horário
  for(int pos = 180; pos >= 0; pos--){
    myservo.write(pos);
  }
}

void test_ldr(){
  int value_light_pin = analogRead(ldl_pin);
  float voltage = value_light_pin * (5.0 / 1023.0);

  Serial.println(voltage);

  if(voltage >= 0.70) 
  {
    digitalWrite(led_pin, HIGH);
    delay(1000);
    
    // state = WAITFORPRESENCE;
    Serial.println("Estado WAITFORPRESENCE");
  }else{
    digitalWrite(led_pin, LOW);
    delay(1000);
    
  }
}

void setup() {

  pinMode(led_pin, OUTPUT);
  pinMode(button_pin, INPUT_PULLUP);

  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);

  myservo.attach(motor_pin);


  Serial.begin(115200);

}

void loop() {
    // test_servo_motor();
    test_ldr();

}
