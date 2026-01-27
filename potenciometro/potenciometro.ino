const int ledRed = 8;
const int ldr = A0;
const int limiar = 202;



void setup()
{
  pinMode(ledRed, OUTPUT);
  Serial.begin(9600);

}

//Ligar um led com intervalo de tempo
void loop()
{ 
  int value_ldr = analogRead(ldr);
  Serial.println(value_ldr);
  int value_product_cycle = map(value_ldr, 0, 1023, 0, 255);

  if(value_product_cycle > limiar ){
    analogWrite(ledRed, HIGH);

  }else{
    analogWrite(ledRed, LOW);
  }

  Serial.println(value_product_cycle);
  

}