// Cada 1000 ms toma muestra de temperatura
// Led Verde encendido cuando t entre 36-40
// 
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
float error = 0;
unsigned long tiempoEncendido = 0;
unsigned long encenderDesde = 0;

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

  if(num - ultimaLectura >= periodoLectura) { //Leemos la temperatura cada 1000 ms para ver si esta dentro del rango e imprimirla por pantalla
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
  
  if(num - ultimoControl >= periodoControl){ //Cada periodo de 5000 ms calculamos el error y controlamos el secador y el led Rojo
    ultimoControl += periodoControl;
    error = 6.0 - celsius(sensorValue); //Se pone 6 aunque sería 38
    if(error <= 0){ //Si el error es negativo no hay que encender nada(la temperatura es mayor que la deseada)
      digitalWrite(pinRojo, LOW);
      digitalWrite(pinNPN, LOW);
    } else if(error > 0 && error < 5){ //Si el error está entre 0 y 5 encendemos una parte del periodo el secador
      encenderDesde = num;
      tiempoEncendido = 1000.0 * error;
      digitalWrite(pinNPN, HIGH);
      digitalWrite(pinRojo, HIGH);
    } else { // Para otro caso encendemos todo el periodo el secador(temperatura muy por debajo de la deseada)
      digitalWrite(pinRojo, HIGH);
      digitalWrite(pinNPN, HIGH);
    }
  }
  
  if((num - encenderDesde> tiempoEncendido) && (tiempoEncendido != 0)){ //Controlamos que el tiempo encendido sea distinto de 0 para asegurarnos que el error esta entre 0 y 5.
    // Además controlamos que entre al if cuando ya se ha cumplido la parte del periodo que tenia que permanecer encendido
    digitalWrite(pinNPN, LOW);
    digitalWrite(pinRojo, LOW);
    tiempoEncendido = 0;
  }
  
}