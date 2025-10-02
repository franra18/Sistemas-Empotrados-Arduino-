const int sensorPin = A0;
float sensorValue = 0;
int pinLed = 3;

void setup() {
  Serial.begin(9600);
  pinMode(pinLed, OUTPUT);
}

void loop() {
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);

  // La resolución del ADC es de 10 bits (0-1023)
  // para una referencia de 255

  float intensidad = 1023 - (sensorValue * (255.0 / 1023.0));
  analogWrite(pinLed, intensidad);
  Serial.println(intensidad);
}