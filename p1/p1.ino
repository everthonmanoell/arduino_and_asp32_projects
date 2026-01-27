#define NOTE_C7  2093

#define A 5
#define B 4
#define C 8
#define D 2
#define E 3
#define F 6
#define G 7

const int led_red = 13;
const int button = 11;
const int light_pin = A0;
const int buzzer_pin = 10;

int incorrect_password = 0;
const int time_limit = 9;
int count_time = 0;
int password_ = 123;


enum State{
  SYSTEMOFF,
  SYSTEMON,
  ALARMON,
  WAITFORPRESENCE,
  ASKFORPASSWORD,
  SHOWERRORMESSAGE,
  PLAYINGBUZZERANDLEDBLINKINGFOREVER
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

void buzzer_function(int frequency, int duration, int m_pause){
  tone(buzzer_pin, frequency, duration);
  int pause = duration * m_pause;
  delay(pause);
  noTone(buzzer_pin);
  
}


void setup()
{
  state = SYSTEMOFF;

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
    
  Serial.begin(9600);

}

void loop()
{

  switch(state){

    case SYSTEMOFF: {

      escreverNumero(0);
      count_time = 0;

      int state_button = digitalRead(button);
      
      if(state_button == HIGH)
      {
        state = SYSTEMON;
        Serial.println("Estado SYSTEMON");
      }
      
      break;

    }
    

    case SYSTEMON: {
      
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
        buzzer_function(NOTE_C7,250,1);
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
      buzzer_function(NOTE_C7, 250, 1);

      digitalWrite(led_red, LOW);
      delay(1000);
      digitalWrite(led_red, HIGH);

    }


  }
  
}