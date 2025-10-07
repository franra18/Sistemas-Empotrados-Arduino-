#include <math.h>

const int sensorPin = A0;
float sensorValue = 0;
int pinLed = 3;
int ultimaLectura = 0;
int periodoLectura = 1000;

void setup() {
  Serial.begin(9600);
  pinMode(pinLed, OUTPUT);
}

float celsius(float sensorValue) {
  float a, b, rtmp;
  a = (1.0 / (25.0 + 273.15));
  rtmp = ((1023.0 * 10e4) / sensorValue) - 10e4;
  b = (1.0 / 3977.0) * log(rtmp / 10e4);
  return (1.0/(a+b))-273.15;
}

void loop() {
  

  unsigned long num = millis();

  if (num - ultimaLectura >= periodoLectura) {
    sensorValue = analogRead(sensorPin);
    ultimaLectura += periodoLectura;
    if (celsius(sensorValue) >= 36 && celsius(sensorValue) <= 40) {
      digitalWrite(pinLed, HIGH);
    } else {
      digitalWrite(pinLed, LOW);
    }
    Serial.println(celsius(sensorValue));
  }
}