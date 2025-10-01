const byte BOTON1PIN = 2;
const byte ledRojo = 3;
const byte ledVerde = 4;
int estadoBoton = 0;
int contador = 0;
int ultimoPulsado = 0;
int ultimoSoltado = 0;

void setup ()
{
  Serial.begin(9600);
  pinMode ( BOTON1PIN , INPUT );
  pinMode ( ledRojo , OUTPUT );
  pinMode ( ledVerde , OUTPUT );
}

void cambiarEstadoLedVerde(){
  digitalWrite(ledVerde, !digitalRead(ledVerde));
}

void loop ()
{
  int est_bot = digitalRead ( BOTON1PIN );
  digitalWrite ( ledRojo , est_bot );
  int num = millis();
  
  if(estadoBoton == 0 && est_bot==HIGH && num - ultimoPulsado >= 20){
    cambiarEstadoLedVerde();
    contador++;
    Serial.println(contador);
    ultimoPulsado = num;
    estadoBoton = est_bot;
  }
  if (estadoBoton == 1 && est_bot==LOW && num-ultimoSoltado >= 20){
    ultimoSoltado = num;
    estadoBoton = est_bot;
  }  
  
}