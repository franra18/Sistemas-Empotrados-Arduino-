const int ledRojo = 3;
const int ledVerde = 4;
byte estadoLedRojo = LOW;
byte estadoLedVerde = LOW;
const int periodoRojo = 5000;
const int periodoVerde = 400;
const int periodoImpresion = 1000;
unsigned long ultimoRojo = 0;
unsigned long ultimoVerde = 0;
unsigned long ultimaImpresion = 0;
float multiplicadores[] = { 0, 0.2, 0.4, 0.6, 0.8, 1 };
int i = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledRojo, OUTPUT);
  pinMode(ledVerde, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long num = millis();
  if (num - ultimoVerde >= periodoVerde) {
    estadoLedVerde = !estadoLedVerde;
    ultimoVerde += periodoVerde;
    digitalWrite(ledVerde, estadoLedVerde);
  }

  if (num - ultimoRojo <= periodoRojo * multiplicadores[i]) {
    estadoLedRojo = HIGH;
  } else {
    estadoLedRojo = LOW;
  }
  
  digitalWrite(ledRojo, estadoLedRojo);

  if (num - ultimoRojo >= periodoRojo) {
    i = (i + 1) % 6;
    ultimoRojo += periodoRojo;
  }
  
  if (num - ultimaImpresion >= periodoImpresion) {
 	Serial.print("\nEl estado del LED es: ");
    Serial.print(estadoLedRojo==HIGH?1:0);
    ultimaImpresion += periodoImpresion;
  }
}