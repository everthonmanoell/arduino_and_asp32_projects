const int buzzer_pin = 27;
const int led_pin = 13;
const int button_pin = 26;
const int motor_pin = 14;

#define NOTE_C7  2093

//Display Segmento
#define A 18
#define B 5
#define C 4
#define D 16
#define E 17
#define F 19
#define G 21


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



void setup() {

  pinMode(led_pin, OUTPUT);
  pinMode(button_pin, INPUT_PULLUP);


  Serial.begin(115200);

}

void loop() {
  
   buzzer_function(buzzer_pin, NOTE_C7, 250, 1);

}
