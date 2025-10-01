const byte BOTON1PIN = 2;
const byte LED1PIN = 3;

void setup ()
{
  pinMode ( BOTON1PIN , INPUT );
  pinMode ( LED1PIN , OUTPUT );
}

void loop ()
{
  int est_bot = digitalRead ( BOTON1PIN );
  digitalWrite ( LED1PIN , est_bot );
}