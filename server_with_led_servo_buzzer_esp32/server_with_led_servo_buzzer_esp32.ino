

#include <WiFi.h>
#include <ESP32Servo.h>
Servo myservo;
const char *ssid = "Softex";
const char *password = "SoftexUFP3!!";
const int button_pin = 27;


// const char *ssid = "CINGUESTS";
// const char *password = "acessocin";
const int motor = 14;
const int LED = 13;
const int ldl = 12;
WiFiServer server(80);



void setup()
{
    Serial.begin(115200);
    pinMode(LED, OUTPUT);
    myservo.attach(motor);
    myservo.write(0);
    delay(10);
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    server.begin();

}



void loop(){
 WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
           // client.println("HTTP/1.1 200 OK");
            client.println("LED_ON");
          /*  client.println();
            client.print("Hello World");
            client.println();
           */ 
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
        Serial.println(currentLine);
       if (currentLine.endsWith("LED_ON")) {
          digitalWrite(LED, HIGH);               // GET /H turns the LED on
          client.println("Acendendo o LED");

          tone(buzzer_pin, NOTE_C7, 250);
          delay(5);
          noTone(buzzer_pin);
        }
         else if (currentLine.endsWith("LED_OFF")) {
          digitalWrite(LED, LOW);                // GET /L turns the LED off
          client.println("LED OFF");
        }else if(currentLine.endsWith("LDL")){
          int value_ldl = analogRead(ldl);
          client.println(value_ldl);

        }else if (currentLine.endsWith("MOTOR_2")) {
          //sentido horário
          for(int pos = 0; pos <= 180; pos++){
            myservo.write(pos);
          }
        }else if (currentLine.endsWith("MOTOR_1")) {
          //sentido horário
          for(int pos = 180; pos >= 0; pos--){
            myservo.write(pos);
          }
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
