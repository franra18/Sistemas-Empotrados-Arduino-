// Cada 1000 ms toma muestra de temperatura
// Led Verde encendido cuando t entre 36-40
// Cada 5000 ms si T < 38 enciende bombilla
// Led Rojo encendido si Bombilla encendida
// Cada 1000 ms enviamos valor t y estado bombilla(0 o 1)

const int pinNPN = 2;
const int pinRojo = 3;
const int pinVerde = 5;
const int pinTemp = A0;
unsigned long ultimaLectura = -1000;
unsigned long periodoLectura = 1000;
unsigned long ultimoControl = -5000;
unsigned long periodoControl = 5000;
byte estadoNPN = LOW;
float sensorValue = 0;

void setup()
{
  pinMode(pinNPN, OUTPUT);
  pinMode(pinRojo, OUTPUT);
  pinMode(pinVerde, OUTPUT);
  Serial.begin(9600);
}


float celsius(float sensorValue) {
  float a, b, rtmp;
  a = (1.0 / (25.0 + 273.15));
  rtmp = ((1023.0 * 10e4) / sensorValue) - 10e4;
  b = (1.0 / 3977.0) * log(rtmp / 10e4);
  return (1.0/(a+b))-273.15;
}


void loop()
{
  unsigned long num = millis();

  if(num - ultimaLectura >= periodoLectura) {
    sensorValue = analogRead(pinTemp);
    ultimaLectura += periodoLectura;
    if (celsius(sensorValue) >= 4 && celsius(sensorValue) <= 8) { // El 4 y el 8 serían 36 y 40
      digitalWrite(pinVerde, HIGH);
    } else {
      digitalWrite(pinVerde, LOW);
    }
    Serial.print(celsius(sensorValue));
    Serial.print(" ");
    Serial.println(digitalRead(pinRojo) == HIGH? 1 : 0);
  }
  
  if(num - ultimoControl >= periodoControl){
    ultimoControl += periodoControl;
    if(celsius(sensorValue) < 6){ // El 6 sería el 38
      digitalWrite(pinRojo, HIGH);
      digitalWrite(pinNPN, HIGH);
    } else {
      digitalWrite(pinRojo, LOW);
      digitalWrite(pinNPN, LOW);
    }
  }
  
}