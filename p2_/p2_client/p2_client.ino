#include <ESP32Servo.h>
#include <WiFi.h>
#define NOTE_C7 2093

//Display Segmento
#define A 16
#define B 17
#define C 19
#define D 18
#define E 5
#define F 4
#define G 32

const char* ssid = "Softex_Conv";
const char* password = "Softex2023";

//const char* host = "www.google.com";
const char* host = "192.168.158.21";  //[IP SERVER]

const int port_ = 1919; //port

const int buzzer_pin = 27;
const int led_red = 12;
const int button = 26;
const int motor_pin = 14;
const int light_pin = 35;
const int touch_pin = 15;


int incorrect_password = 0;
const int time_limit = 9;
int count_time = 0;
int password_ = 123;
String user_name;
int current_stepper_engine_degrees = 0;



Servo myservo;

enum State {
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
  { 1, 1, 1, 1, 1, 1, 0 },  // = Digito 0
  { 0, 1, 1, 0, 0, 0, 0 },  // = Digito 1
  { 1, 1, 0, 1, 1, 0, 1 },  // = Digito 2
  { 1, 1, 1, 1, 0, 0, 1 },  // = Digito 3
  { 0, 1, 1, 0, 0, 1, 1 },  // = Digito 4
  { 1, 0, 1, 1, 0, 1, 1 },  // = Digito 5
  { 1, 0, 1, 1, 1, 1, 1 },  // = Digito 6
  { 1, 1, 1, 0, 0, 0, 0 },  // = Digito 7
  { 1, 1, 1, 1, 1, 1, 1 },  // = Digito 8
  { 1, 1, 1, 1, 0, 1, 1 },  // = Digito 9
};

void escreverNumero(int numero) {
  bool* display = sete_segmentos[numero];
  digitalWrite(A, display[0]);
  digitalWrite(B, display[1]);
  digitalWrite(C, display[2]);
  digitalWrite(D, display[3]);
  digitalWrite(E, display[4]);
  digitalWrite(F, display[5]);
  digitalWrite(G, display[6]);
}

void test_touch_pin_with_led() {
  int touch = touchRead(touch_pin);
  Serial.println(touch);
  delay(500);


  int touch_detection = 360;
}

void test_button_with_led() {

  int button_pressed = digitalRead(button);

  Serial.println(button_pressed);

  if (button_pressed == LOW) {
    digitalWrite(led_red, HIGH);
    delay(1000);


  } else {
    digitalWrite(led_red, LOW);
    delay(1000);
  }
}


void buzzer_function(int pin, int frequency, int duration, int m_pause) {

  tone(pin, frequency, duration);
  int pause = duration * m_pause;
  delay(pause);
  noTone(pin);
}

void test_display_7_s() {

  for (int i = 0; i < 10; i++) {
    Serial.println(i);
    escreverNumero(i);
    delay(1000);
  }
}

void test_servo_motor() {
  //sentido horário
  for (int pos = 0; pos <= 180; pos++) {
    myservo.write(pos);
  }

  //sentido horário
  for (int pos = 180; pos >= 0; pos--) {
    myservo.write(pos);
  }
}

void move_servo_positive(int degrees) {
  for (int pos = 0; pos <= degrees; pos++) {
    myservo.write(pos);
    current_stepper_engine_degrees = pos;
  }
}

void move_servo_negative(int degrees) {
  for (int pos = degrees; pos >= 0; pos--) {
    myservo.write(pos);
    current_stepper_engine_degrees = pos;
  }
}

void test_ldr() {
  int value_light_pin = analogRead(light_pin);
  float voltage = value_light_pin * (5.0 / 1023.0);

  Serial.println(voltage);

  if (voltage >= 0.70) {
    digitalWrite(led_red, HIGH);
    delay(1000);

    // state = WAITFORPRESENCE;
    Serial.println("Estado WAITFORPRESENCE");
  } else {
    digitalWrite(led_red, LOW);
    delay(1000);
  }
}

// Função para buscar dados no servidor
// Retorna a String com a resposta (ex: "Joao Silva") ou vazio se falhar
String searchUserInServer(String id_usuario) {

  WiFiClient client;          // Cria um cliente temporário
  const int httpPort = port_;  // Porta do Python

  // 1. Tenta Conectar
  if (!client.connect(host, httpPort)) {
    Serial.println("Falha ao conectar no Python!");
    return "";
  }

  // 2. Envia o Pedido com o ID
  // Envia: GET / id_usuario
  client.print(String("GET /") + id_usuario + "\r\n\r\n");

  // 3. Espera chegar dados (com timeout de 2s)
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 15000) {
      Serial.println(">>> Timeout: Servidor demorou responder!");
      client.stop();
      return "";
    }
  }

  // 4. Lê a resposta
  // Lê tudo o que o servidor mandou de uma vez
  String response = client.readString(); 
  
  // Limpa espaços em branco ou quebras de linha que possam vir junto
  response.trim();
  client.stop();  // Fecha a conexão
  return response;
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

  while (WiFi.status() != WL_CONNECTED) {
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


void sloop() {
  // int value_light_pin = analogRead(light_pin);
  // Serial.println(value_light_pin);
  // for(int i = 0; i<10; i++){
  //   escreverNumero(i);
  // }
  // buzzer_function(buzzer_pin, NOTE_C7, 250, 1);
  // digitalWrite(led_red, HIGH);
  // Serial.println("led high");
  // delay(1000);
  // digitalWrite(led_red, LOW);
  // Serial.println("led low");
  // int button_pressed = digitalRead(button);
  // Serial.println(button_pressed);

  // Serial.println("Digite a senha: ");

  // int serial = Serial.available();


  // if (serial > 0) {
  //   int password = Serial.parseInt();
  //   String result = searchUserInServer(String(password));
  //   Serial.println(result);
  //   if (result != "" && result != "error2times") {  // if this is true, the autentication was true and return the name of user
  //     delay(1000);
  //     user_name = result;  //save the user name
  //     incorrect_password = 0;
      
  //   }
  // }


  // move to -90 degrees with current_stepper_engine_degrees relative
    Serial.println("-90");
    for (int i = current_stepper_engine_degrees; i >= -90; i-- ){
      myservo.write(i);
      current_stepper_engine_degrees = i;
    }

    delay(500);
    Serial.println("123");
    move_servo_positive(123);
    delay(500);

}
void loop() {

  switch (state) {

    case SYSTEMOFF:
      {
        //move_servo_negative(90);
        //myservo.write(-90);

        // move to -90 degrees with current_stepper_engine_degrees relative
        for (int i = current_stepper_engine_degrees; i >= -90; i-- ){
          myservo.write(i);
          Serial.println(i);
          current_stepper_engine_degrees = i;
        }
        Serial.println("SYSTEMOFF STATE");
        escreverNumero(0);
        count_time = 0;

        int state_button = digitalRead(button);

        if (state_button == LOW) {
          state = SYSTEMON;
          
        }

        break;
      }


    case SYSTEMON:
      {

        Serial.println("SYSTEMON STATE");

        for (int second = 0; second < 10; second++) {
          
          digitalWrite(led_red, LOW);
          delay(500);
          digitalWrite(led_red, HIGH);
          Serial.println(second);
          escreverNumero(second);
          delay(500);

        }

        digitalWrite(led_red, LOW);

        delay(1000);

        state = ALARMON;
        Serial.println("Estado ALARMON");

        break;
      }


    case ALARMON:
      {
        
        move_servo_positive(116);
        state = WAITFORPRESENCE;
        break;

      }


    case WAITFORPRESENCE:
      {
        Serial.println("Estado WAITFORPRESENCE");
        int value_light_pin = analogRead(light_pin);
        float voltage = value_light_pin * (3.3 / 4095.0);
        int value_touch_pin = touchRead(touch_pin);

        //delay(1000);

        if (voltage >= 0.20 || value_touch_pin < 1000) {
          delay(1000);

          for (int buzzer_count = 0; buzzer_count < 2; buzzer_count++) {
            buzzer_function(buzzer_pin, NOTE_C7, 250, 1);
            delay(200);
          }

          state = ASKFORPASSWORD;
          
          Serial.println("Estado ASKFORPASSWORD");
        }

        

        
        


        break;
      }


    case ASKFORPASSWORD:
      {
        Serial.println("Digite a senha: ");

        int serial = Serial.available();


        if (serial > 0) {
          int password = Serial.parseInt();
          String result = searchUserInServer(String(password));
          if (result != "" && result != "error2times") {  // if this is true, the autentication was true and return the name of user
            delay(1000);
            user_name = result;  //save the user name in global variable
            incorrect_password = 0;
            state = CORRECTPASSWORD;
          } else {
            incorrect_password++;

            delay(1000);

            state = SHOWERRORMESSAGE;
          }


        } else {  // occur when don't put any password try in the serial output

          if (count_time == time_limit) {

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


    case SHOWERRORMESSAGE:
      {
        Serial.println("Senha incorreta ou tempo expirado!!");

        if (incorrect_password < 2) {
          count_time = 0;

          delay(2000);

          state = ASKFORPASSWORD;
        }

        else if (incorrect_password > 1)  // occur when the limite try is over
        {
          delay(1000);

          state = SHOWFINALERRORMESSAGE;
        }

        break;
      }

    case SHOWFINALERRORMESSAGE:
      {
        delay(1000);
        String result = searchUserInServer("1111");
        Serial.println(result);
        state = PLAYINGBUZZERANDLEDBLINKINGFOREVER;

        break;
      }

    case CORRECTPASSWORD:
      {
        Serial.println("Senha correta!!");
        Serial.print("O usuario: [ ");
        Serial.print(user_name);
        Serial.println(" ] desligou o alarme.");
        state = SYSTEMOFF;
      }


    case PLAYINGBUZZERANDLEDBLINKINGFOREVER:
      {
        buzzer_function(buzzer_pin, NOTE_C7, 250, 1);

        digitalWrite(led_red, LOW);
        delay(1000);
        digitalWrite(led_red, HIGH);
      }
  }
}
