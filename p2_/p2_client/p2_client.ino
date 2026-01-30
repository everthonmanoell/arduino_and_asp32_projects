#include <ESP32Servo.h>
#include <WiFi.h>
#define NOTE_C7  2093

//Display Segmento
#define A 16
#define B 17
#define C 19
#define D 18
#define E 5
#define F 4
#define G 32

const char* ssid     = "Softex_Conv";
const char* password = "Softex2023";

//const char* host = "www.google.com"; 
const char* host = ""; //[IP]

const int buzzer_pin = 27;
const int led_red = 13;
const int button = 26;
const int motor_pin = 14;
const int light_pin = 12;
const int touch_pin = 33;


int incorrect_password = 0;
const int time_limit = 9;
int count_time = 0;
int password_ = 123;



Servo myservo;
WiFiClient client;

enum State{
  SYSTEMOFF,
  SYSTEMON,
  ALARMON,
  WAITFORPRESENCE,
  ASKFORPASSWORD,
  SHOWERRORMESSAGE,
  SHOWFINALERRORMESSAGE,
  PLAYINGBUZZERANDLEDBLINKINGFOREVER,
  CORRECTPASSWORD

} state;



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

void test_touch_pin_with_led(){
  int touch = touchRead(touch_pin);
  Serial.println(touch);
  delay(500);

  
  int touch_detection = 360;
}

void test_button_with_led(){

  int button_pressed = digitalRead(button);

    Serial.println(button_pressed);

    if(button_pressed == LOW)
    {
      digitalWrite(led_red, HIGH);
      delay(1000);


    } else {
      digitalWrite(led_red, LOW);
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

void move_servo_positive(int degrees){
  for(int pos = 0; pos <= degrees; pos++){
            myservo.write(pos);
          }

}

void move_servo_negative(int degrees){
  for(int pos = degrees; pos >= 0; pos--){
            myservo.write(pos);
          }

}

void test_ldr(){
  int value_light_pin = analogRead(light_pin);
  float voltage = value_light_pin * (5.0 / 1023.0);

  Serial.println(voltage);

  if(voltage >= 0.70) 
  {
    digitalWrite(led_red, HIGH);
    delay(1000);
    
    // state = WAITFORPRESENCE;
    Serial.println("Estado WAITFORPRESENCE");
  }else{
    digitalWrite(led_red, LOW);
    delay(1000);
    
  }
}


void wifi_connect(){

  delay(5000);

    Serial.print("connecting to ");
    Serial.println(host);

    // Use WiFiClient class to create TCP connections

    const int httpPort = 8080;
    if (!client.connect(host, httpPort)) {
        Serial.println("connection failed");
        return;
    }

    client.print(String("GET /") + " \r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            Serial.println(">>> Client Timeout !");
            client.stop();
            return;
        }
    }

    // Read all the lines of the reply from server and print them to Serial
    while(client.available()) {
        String line = client.readStringUntil('\r');
        Serial.print(line);
    }
    client.stop();
    Serial.println();
    Serial.println("closing connection");

}

void setup() {


  pinMode(led_red, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  pinMode(light_pin, INPUT);

  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);

  myservo.attach(motor_pin);
  escreverNumero(0);


  Serial.begin(115200);
  delay(10);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print('.');
  }
  Serial.println("");
  Serial.println("Wifi connected");

  state = SYSTEMOFF;

}

// void test_all(){
//   //test_display_7_s();
//   //test_button_with_led();
//   //buzzer_function(buzzer_pin, NOTE_C7, 250, 1);
//   // test_servo_motor();
//   // test_ldr();
//   //test_touch_pin_with_led();
// }



void loop()
{
  
  switch(state){

    case SYSTEMOFF: {
      //move_servo_negative(90);
      myservo.write(-90);
      Serial.println("systemoff motor negative");
      escreverNumero(0);
      count_time = 0;

      int state_button = digitalRead(button);
      
      if(state_button == LOW)
      {
        state = SYSTEMON;
        Serial.println("Estado SYSTEMON_");
      }
      
      break;

    }
    

    case SYSTEMON: {

      Serial.println("entrei no systemon");
      
      for(int second = 0; second < 10; second++)
      {
        
        digitalWrite(led_red, LOW);
        delay(1000);
        digitalWrite(led_red, HIGH);
        Serial.println(second);
        escreverNumero(second);

      }
       
      digitalWrite(led_red, LOW);
        
      delay(1000);
      
      state = ALARMON;
      Serial.println("Estado ALARMON");

      break;
      
    }

    
    case ALARMON: {
      int value_light_pin = analogRead(light_pin);
      float voltage = value_light_pin * (5.0 / 1023.0);
      //move_servo_positive(90);
      myservo.write(116);
      if(voltage >= 0.70) 
      {
        delay(1000);
        
        state = WAITFORPRESENCE;
        Serial.println("Estado WAITFORPRESENCE");
      }

      break;

    }


    case WAITFORPRESENCE: {

      for(int buzzer_count = 0; buzzer_count < 2; buzzer_count++)
      {
        buzzer_function(buzzer_pin ,NOTE_C7,250,1);
        delay(200);
        
      }
      
      //delay(1000);

      state = ASKFORPASSWORD;
      Serial.println("Estado ASKFORPASSWORD");


      break;

    }


    case ASKFORPASSWORD: { //HE'RE HERE
      Serial.println("Digite a senha: ");
      
      int serial = Serial.available();
 
      
      if(serial > 0){
          int password = Serial.parseInt();
        
        if(password == password_)
        {
          delay(1000);
          state = SYSTEMOFF;
          Serial.println("Senha correta, alarme desativado");
          incorrect_password = 0;
        }
        
        else if(password != password_)
        {
          incorrect_password++;
          
          delay(1000);
          
          state = SHOWERRORMESSAGE;
        }
        
          
      }else{
        
        if (count_time == time_limit)
        {
          
          incorrect_password++;
          state = SHOWERRORMESSAGE;
            
        }
        
        Serial.println(count_time);
        escreverNumero(count_time);
        count_time++;
        delay(1000);
        
        
      }
     
     
      break;
      
    }

    
    case SHOWERRORMESSAGE: {
      Serial.println("Senha incorreta ou tempo expirado!!");
      
      if(incorrect_password < 2)
      {
        count_time = 0;
        
        delay(2000);
        
        state = ASKFORPASSWORD;
      }
      
      else if(incorrect_password > 1)
      {
        delay(1000);

        state = PLAYINGBUZZERANDLEDBLINKINGFOREVER;
      }
    
      break;

    }

    
    case PLAYINGBUZZERANDLEDBLINKINGFOREVER: {  
      buzzer_function(buzzer_pin, NOTE_C7, 250, 1);

      digitalWrite(led_red, LOW);
      delay(1000);
      digitalWrite(led_red, HIGH);

    }


  }
  
}


