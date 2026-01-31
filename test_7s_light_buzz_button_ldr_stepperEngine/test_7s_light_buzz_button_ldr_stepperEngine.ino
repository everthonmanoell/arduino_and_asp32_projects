#include <ESP32Servo.h>
#define NOTE_C7 2093
//Display Segmento
#define A 16
#define B 17
#define C 19
#define D 18
#define E 5
#define F 4
#define G 32

const int button = 26;
const int buzzer_pin = 27;
const int led_pin = 12;
const int touch_pin = 15;
const int motor_pin = 14;
const int ldr_pin = 35;

Servo myservo;

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

void setup() {
  // put your setup code here, to run once:
  pinMode(button, INPUT_PULLUP);
  pinMode(led_pin, OUTPUT);
  Serial.begin(115200);
  
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);

  
  myservo.attach(motor_pin);

}

void loop() {
  // put your main code here, to run repeatedly:

  int ldr_value = analogRead(ldr_pin);
  float ldr_voltage = ldr_value * (3.3 / 4095.0);

  Serial.print("Valor cru do ldr: ");
  Serial.print(ldr_value);
  Serial.print(" || Voltagem: ");
  Serial.println(ldr_voltage);
  delay(500);

  // int touch_result = touchRead(touch_pin);
  // Serial.println(touch_result);
  // delay(600);


  // Test servo ====================
  // for (int i = 0; i <= 180; i++){ // 0 to 180 degrees
  //   myservo.write(i);
  // }

  // delay(1000);

  // for(int i = 180; i >= 0; i--){ // 180 to 0 degrees
  //   myservo.write(i);
  // }
  //==========================

  // int state = digitalRead(button);
  // if (state == LOW){
  //   Serial.println("Botão pressionado");
  //   tone(buzzer_pin, NOTE_C7, 250);
  //   digitalWrite(led_pin, HIGH);
  //   delay(200);

  // }else{
  //   Serial.println("Botão solto");
  //   noTone(buzzer_pin);
  //   digitalWrite(led_pin, LOW);
  // }

  // delay(200);

  // for(int i = 0; i < 10; i++){
  //   escreverNumero(i);
  //   delay(500);
  // }

}
