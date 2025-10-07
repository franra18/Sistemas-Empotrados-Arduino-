const int pinNPN = 2;
unsigned long ultimoPeriodo = -5000; //Para q entre en el if la primera vez
unsigned long periodo = 5000;
byte estadoNPN = LOW ;

void setup()
{
  pinMode(pinNPN, OUTPUT);
}

void loop()
{
  unsigned long num = millis();
  if(num - ultimoPeriodo >= periodo){
    ultimoPeriodo += periodo;
    digitalWrite(pinNPN, estadoNPN);
    estadoNPN = !estadoNPN;
  }
}