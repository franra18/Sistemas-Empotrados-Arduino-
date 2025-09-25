const int ledRojo = 3;
const int ledVerde = 4;
byte estadoLedRojo = LOW;
byte estadoLedVerde = LOW;
const int periodoRojo = 5000;
const int periodoVerde = 400;
unsigned long siguienteRojo = 5000;
unsigned long siguienteVerde = 0;
float multiplicadores[] = { 0, 0.2, 0.4, 0.6, 0.8, 1 };
int i = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledRojo, OUTPUT);
  pinMode(ledVerde, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long num = millis();
  if (num >= siguienteVerde) {
    estadoLedVerde = !estadoLedVerde;
    siguienteVerde += periodoVerde;
    digitalWrite(ledVerde, estadoLedVerde);
  }

  if ( <= periodo * multiplicadores[i]) {
    digitalWrite(ledRojo, HIGH);
  } else {
    digitalWrite(ledRojo, LOW);
  }

  if (num >= siguienteRojo) {
    i = (i + 1) % 6;
    siguienteRojo += periodoRojo;
  }
}
