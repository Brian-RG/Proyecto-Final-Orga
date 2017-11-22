#include <Servo.h> //importar librería de Servomotor
//#include <LiquidCrystal.h> //importar lcd library
#include <Keypad.h> //importar keypad library
#include <SoftwareSerial.h>
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
SoftwareSerial BT(0,1); //10 RX, 11 TX.
int ledred=3; //Pin LED Red
int ledgreen=4;//Pin LED Green
int ledblue=5; //Pin LED Blue



const byte ROWS = 4; // four rows
const byte COLS = 4; // four columns

//define the keymap
char keys [ROWS] [COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '=', 'E'}
};

byte rowPins[ROWS] = {
  39 ,41 ,43 ,45}; //connect keypad ROW1, ROW2, ROW3, ROW4 to these arduino pins
byte colPins[COLS] = {
  37, 35, 33, 31}; //connect keypad COL1, COL2, COL3, COL4 to these arduino pins


Keypad myKeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );



Servo servomotor;
String clave="1234";
String intento;
boolean encendidoCuarto=false;
boolean encendidoCocina=false;
boolean encendidoprincipal=false;
boolean encendidocomedor=false;
boolean peligro=false;
  int pin_comedor=52;
  int pin_cuarto=50;
  int pin_cocina=48;
  int pin_principal=46;
  int lectura,luz;
  int Sensor=A0;
  int movim=10;
  boolean activo=false;
  boolean s_activo=false;
long tiempo;
int disparador = 7;
int entrada = 8;
float distancia;
int buzzer=9;
int blanc=31;
int blanco=29;
boolean desactivado=false;
LiquidCrystal_I2C  lcd(0x27,2,1,0,4,5,6,7); // 0x27 is the I2C bus address for an unmodified module
  
void setup() {
    
  servomotor.attach(2);
  servomotor.write(0);
  pinMode(movim, INPUT);  //Configuramos el pin analogico A5 como entrada
  pinMode(ledred,OUTPUT);   //Pueto Digital utilizando la función PWM
  pinMode(ledgreen,OUTPUT);//Pueto Digital utilizando la función PWM
  pinMode(ledblue,OUTPUT);//Pueto Digital utilizando la función PWM
  pinMode(pin_cuarto,OUTPUT);
  pinMode(pin_cocina,OUTPUT);
  pinMode(pin_principal,OUTPUT);
  pinMode(disparador,OUTPUT);
  pinMode(entrada,INPUT);
  pinMode(buzzer,OUTPUT);
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH); // NOTE: You can turn the backlight off by setting it to LOW instead of HIGH
  lcd.begin(16, 2);
  lcd.clear();
    intento="";
  Serial.begin(9600);
  
}

void loop() {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Ingresa tu clave:");
    lcd.setCursor(0,1);
    lcd.print(intento);
    char key=myKeypad.getKey();
    if(key!= NO_KEY && (key=='1' || key=='2' || key=='3' || key=='4' || key=='5' || key=='6' || key=='7' || key=='8' || key=='9' || key=='0')){
      intento= intento +key;
    }
    else if(key=='A'){
        if(intento=="1234"){
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Clave aceptada");
            if(s_activo==true){
                s_activo=false;
              }
            else{
                s_activo=true;
              }
              intento="";
              delay(1000);
          }
          else{
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("Clave incorrecta");
              if(s_activo){
                  peligro=true;
                }
                delay(1000);
            }
      }
    if(peligro){
         analogWrite(buzzer,180);
        delay(1000);
        analogWrite(buzzer,0); 
      }
  if(activo){
        lectura=analogRead(Sensor);
        luz = map (lectura,450 ,910 ,0 ,100);
        if(luz<=-90){
            digitalWrite(pin_cuarto,HIGH);
            digitalWrite(pin_cocina,HIGH);
            digitalWrite(pin_principal,HIGH);
            digitalWrite(pin_comedor,HIGH);
            delay(300);
        }
        else{
          digitalWrite(pin_cuarto,LOW);
          digitalWrite(pin_cocina,LOW);
          digitalWrite(pin_principal,LOW);
          digitalWrite(pin_comedor,LOW);
        }
        //Serial.println(luz);
        delay(100);
    }
  /*else {
      digitalWrite(pin_cuarto,LOW);
      digitalWrite(pin_cocina,LOW);
      digitalWrite(pin_principal,LOW);
      digitalWrite(pin_comedor,LOW);
    }*/
  if(s_activo){
      analogWrite(ledred,0);
      analogWrite(ledgreen,255);
      analogWrite(ledblue,0);
      digitalWrite(disparador, HIGH);
      delay (30);
      digitalWrite(disparador, LOW);

      tiempo = (pulseIn(entrada, HIGH)/2);

      distancia = float(tiempo * 0.0343);
      //Serial.println(distancia);
      if(distancia<10){
       peligro=true;
      }
      double val=digitalRead(movim);
    //  Serial.println(val);
      if(val>100){
          peligro=true;
        }
    }
  else{
      analogWrite(ledred,255);
      analogWrite(ledgreen,0);
      analogWrite(ledblue,0);
      analogWrite(buzzer,0);
    }
  if(Serial.available()){
    
   char dato= Serial.read(); 
   // Serial.print("Dato Recibido: ");
   //Serial.println(dato);
    if(dato=='B'){
        servomotor.write(90);
      }
    else if(dato=='D'){
        servomotor.write(0);
      }
    else if(dato=='c'){
        if(encendidoCuarto==false){
          digitalWrite(pin_cuarto,HIGH);
          encendidoCuarto=true;
        }
        else{
          digitalWrite(pin_cuarto,LOW);
          encendidoCuarto=false;
        }
      }
    else if(dato=='n'){
        if(encendidoCocina==false){
          digitalWrite(pin_cocina,HIGH);
          encendidoCocina=true;
        }
        else{
          digitalWrite(pin_cocina,LOW);
          encendidoCocina=false;
        }
      }
    else if(dato=='P'){
        if(encendidoprincipal==false){
          digitalWrite(pin_principal,HIGH);
          encendidoprincipal=true;
        }
        else{
          digitalWrite(pin_principal,LOW);
          encendidoprincipal=false;
        }
      }
    else if(dato=='m'){
        if(encendidocomedor==false){
          digitalWrite(pin_comedor,HIGH);
          encendidocomedor=true;
        }
        else{
          digitalWrite(pin_comedor,LOW);
          encendidocomedor=false;
        }
      }
   else if(dato=='f'){
        activo= !activo;
      //  Serial.println(activo);
    }

    else if(dato=='s'){
        s_activo=true;
        
      analogWrite(buzzer,20);
      delay(10);
      analogWrite(buzzer,0);
      
      analogWrite(buzzer,20);
      delay(10);
      analogWrite(buzzer,0);
      
      analogWrite(buzzer,20);
      delay(10);
      analogWrite(buzzer,0);
      
      analogWrite(buzzer,20);
      delay(10);
      analogWrite(buzzer,0);
      }
    else if(dato=='a'){
        s_activo=false;
        peligro=false;
      }
   
  }
}
