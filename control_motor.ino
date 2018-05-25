
#define MOTOR 10
#define POTENCIOMETRO A0
#define VELOCIDAD_MAX 100
#define RELE3 3
#define RELE4 5
String palabra_clave;
String estado;
int estado_rele3;
int estado_rele4;

typedef enum {
  ON = LOW,
  OFF = HIGH
} estado_t;

void acelerar_adelante ();
void desacelerar (int rueda,int velocidad);
void acelerar (int rueda, int velocidad);
void invertir_sentido (int pin_apagar, int pin_prender);
void detener ();

void setup()
{
  pinMode(RELE3,OUTPUT);
  pinMode(RELE4,OUTPUT);
  digitalWrite(RELE3,OFF);
  estado_rele3 = OFF;
  digitalWrite(RELE4,OFF);
  estado_rele4 = OFF;
 Serial.begin(9600);
}


void loop()
{ 
 //int level = analogRead(POTENCIOMETRO);
 //acelerar_desacelerar(level);
 if(Serial.available()){
    palabra_clave = Serial.readString();
    Serial.println(palabra_clave);
    if(palabra_clave == "adelante"){
      acelerar_adelante();
    }
    else if(palabra_clave == "atras"){
      acelerar_atras(); 
    }
    else{
      detener(); 
    }
  }
}

void acelerar_adelante () {
  if (estado_rele3 == ON) {
    desacelerar (RELE3, VELOCIDAD_MAX);
  }
  invertir_sentido (RELE3, RELE4);
  estado_rele4 = ON;
  estado_rele3 = OFF;
  acelerar (RELE4,VELOCIDAD_MAX);
}

void acelerar_atras () {
  if (estado_rele4 == ON) {
    desacelerar (RELE4, VELOCIDAD_MAX);
  }
  invertir_sentido (RELE4, RELE3);
  estado_rele3 = ON;
  estado_rele4 = OFF;
  acelerar (RELE3,VELOCIDAD_MAX);
}

void desacelerar (int rueda, int velocidad) {
  for (size_t i = velocidad; i > 0; i--)
    analogWrite (rueda, i);
}

void acelerar (int rueda, int velocidad) {
  for (size_t i = 0; i < velocidad; i++)
    analogWrite (rueda, i);
}

void invertir_sentido (int pin_apagar, int pin_prender) {
    digitalWrite (pin_apagar, OFF);
    digitalWrite (pin_prender, ON);
}

void detener () {
  if (estado_rele3 == ON) {
    desacelerar (RELE3, VELOCIDAD_MAX);
    digitalWrite (RELE3, OFF);
    estado_rele3 = OFF;
  }
  else if (estado_rele4 == ON) {
    desacelerar (RELE4, VELOCIDAD_MAX);
    digitalWrite (RELE4, OFF);
    estado_rele4 = OFF;
  }
  
}

