const int ledRojo = 3;
const int ledVerde = 4;
byte estadoLedRojo = LOW;
byte estadoLedVerde = LOW;
const int periodoRojo = 512;
const int periodoVerde = 729;
unsigned long siguienteRojo = 0;
unsigned long siguienteVerde = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledRojo, OUTPUT);
  pinMode(ledVerde, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long num = millis();
  if(num >= siguienteRojo) {
    estadoLedRojo = !estadoLedRojo;
    siguienteRojo += periodoRojo;
    digitalWrite(ledRojo, estadoLedRojo);
  } else if (num >= siguienteVerde) {
    estadoLedVerde = !estadoLedVerde;
    siguienteVerde += periodoVerde;
    digitalWrite(ledVerde, estadoLedVerde);
  }
}
 