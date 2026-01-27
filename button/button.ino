#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978


const int red_pin = 13;
const int yellow_pin = 12;
const int green_pin = 11; 
const int buzzer_pin = 10;
const int trigger = 8;
const int echo = 9;
const float limiar_distance_green = 300;
const float limiar_distance_yellow = 150;
const float limiar_distance_red = 50;
const float limiar_colision = 10;
const int second = 1000;


void setup() {
  pinMode(red_pin, OUTPUT);
  pinMode(yellow_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  
  pinMode(trigger, OUTPUT); //pino de saída
  pinMode(echo, INPUT); //pino de entrada
  
  pinMode(buzzer_pin,OUTPUT);
  
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
  
  
  if(distance > limiar_distance_yellow){
    // turn on green light
    digitalWrite(green_pin, HIGH);
    digitalWrite(yellow_pin, LOW);
    digitalWrite(red_pin, LOW);
    int duration_time = second / 2;

    Serial.println("cheguei no verde");

    // high frequency
    buzzer(NOTE_B1, duration_time, 6);
    

    
   
  }else if (distance > limiar_distance_red){
    // turn on yellow light
    digitalWrite(green_pin, LOW);
    digitalWrite(yellow_pin, HIGH);
    digitalWrite(red_pin, LOW);
    int duration_time = second / 3;
    Serial.println("cheguei no amarelo");
    // medium frequency
    buzzer(NOTE_A4, duration_time, 3);

    
  }else if(distance <= limiar_colision){ // lack just the correct condition
    digitalWrite(green_pin, HIGH);
    digitalWrite(yellow_pin, HIGH);
    digitalWrite(red_pin, HIGH);
    int duration_time = second / 1;
  Serial.println("cheguei no colision");
    
    // low frequency
    buzzer(NOTE_C7, duration_time, 1);
    digitalWrite(green_pin, LOW);
    digitalWrite(yellow_pin, LOW);
    digitalWrite(red_pin, LOW);



  }else{
    // turn on RED light
    digitalWrite(green_pin, LOW);
    digitalWrite(yellow_pin, LOW);
    digitalWrite(red_pin, HIGH);
    int duration_time = second / 4;
    Serial.println("cheguei no vermelho");

    // low frequency
    buzzer(NOTE_C7, duration_time, 1);
    delay(100);
  }

  
  

}


void buzzer(int frequency, int duration, int m_pause){
  tone(buzzer_pin, frequency, duration);
  int pause = duration * m_pause;
  delay(pause);
  noTone(buzzer_pin);
}