#include <Servo.h> //importar librería de Servomotor
#include <LiquidCrystal.h> //importar lcd library
#include <Keypad.h> //importar keypad library
Servo servomotor;
boolean encendidoCuarto=false;
boolean encendidoCocina=false;
boolean encendidoprincipal=false;

  int pin_cuarto=50;
  int pin_cocina=48;
  int pin_principal=46;
void setup() {
  Serial.begin(9600);
  servomotor.attach(2);
  servomotor.write(0);

  pinMode(pin_cuarto,OUTPUT);
  pinMode(pin_cocina,OUTPUT);
  pinMode(pin_principal,OUTPUT);
}

void loop() {
  if(Serial.available()){
   char dato= Serial.read(); 
    Serial.print("Dato Recibido: ");
    Serial.println(dato);
    if(dato=='B'){
        servomotor.write(90);
      }
    else if(dato=='D'){
        servomotor.write(0);
      }
    else if(dato=='c'){
        if(!encendidoCuarto)
        digitalWrite(pin_cuarto,HIGH);
        else
        digitalWrite(pin_cuarto,LOW);
      }
    else if(dato=='C'){
        if(!encendidoCocina)
        digitalWrite(pin_cocina,HIGH);
        else
        digitalWrite(pin_cocina,LOW);
      }
    else if(dato=='P'){
        if(!encendidoprincipal)
        digitalWrite(pin_principal,HIGH);
        else
        digitalWrite(pin_principal,LOW);
      }
  }
}
