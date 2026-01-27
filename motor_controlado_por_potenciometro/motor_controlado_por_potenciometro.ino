const int motor = 5;
const int potenciometro_pin = A0;


void setup() {
  // put your setup code here, to run once:

  pinMode(motor, OUTPUT);
  pinMode(potenciometro_pin, INPUT);
  Serial.begin(9600);


}

void loop() {
  // put your main code here, to run repeatedly:
  int timPotenciometro = analogRead(potenciometro_pin);
  int valorPWM = map(timPotenciometro, 0, 1023, 0, 255);

  analogWrite(motor, valorPWM );

  delay(10);







}
