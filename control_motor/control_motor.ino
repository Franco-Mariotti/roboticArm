#define MOTOR 10
#define POTENCIOMETRO A0
#define VELOCIDAD_MAX 200
#define RELE3 3
#define RELE4 5
#define ESTADO_RELE3 8
#define ESTADO_RELE4 12
String palabra_clave;
String estado;

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
  pinMode(ESTADO_RELE3, OUTPUT);
  pinMode(ESTADO_RELE4, OUTPUT);
  analogWrite(RELE3,0);
  digitalWrite (ESTADO_RELE3, OFF);
  analogWrite(RELE4,0);
  digitalWrite (ESTADO_RELE4, OFF);
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
  if (digitalRead (ESTADO_RELE3) == ON) {
    desacelerar (RELE3, VELOCIDAD_MAX);
  }
  invertir_sentido (ESTADO_RELE3, ESTADO_RELE4);
  acelerar (RELE4,VELOCIDAD_MAX);
}

void acelerar_atras () {
  if (digitalRead(ESTADO_RELE4) == ON) {
    desacelerar (RELE4, VELOCIDAD_MAX);
  }
  invertir_sentido (ESTADO_RELE4, ESTADO_RELE3);
  acelerar (RELE3,VELOCIDAD_MAX);
}

void desacelerar (int rueda, int velocidad) {
  for (size_t i = velocidad; i > 0; i--){
    analogWrite (rueda, i);
    delay (2);
  }
}

void acelerar (int rueda, int velocidad) {
  for (size_t i = 0; i < velocidad; i++){
    analogWrite (rueda, i);
    delay (2);
  }
}

void invertir_sentido (int pin_apagar, int pin_prender) {
    digitalWrite (pin_apagar, OFF);
    delay (1000);
    digitalWrite (pin_prender, ON);
}

void detener () {
  if (digitalRead(ESTADO_RELE3) == ON) {
    desacelerar (RELE3, VELOCIDAD_MAX);
    digitalWrite (ESTADO_RELE3, OFF);
  }
  else if (digitalRead(ESTADO_RELE4) == ON) {
    desacelerar (RELE4, VELOCIDAD_MAX);
    digitalWrite (ESTADO_RELE4, OFF);
  }
  
}

