#include <LiquidCrystal.h>
#include <TimerOne.h>
 LiquidCrystal lcd(13,12,11,10,9,8);
 int on=0;
 int seg=0;
 int horas=0;
 int minutos=0;
 int ha=0;
 int ma=0;
 String horas_alarma;
 String minutos_alarma;
 char texto [ 10 ];
 char texto1 [ 10 ];
 int modo = 0 ;
 volatile int segundos=0;
 volatile boolean actualizar=true;
 int a;
 int b;
 int dato;
 int dato1;
 
void setup() {
   lcd.begin(16,4);
   lcd.setCursor(0,0);
   lcd.print("Hora");
   lcd.setCursor(0,2);
   lcd.print("Alarma");
   Serial.begin(9600);
   Timer1.initialize(1000000);
   Timer1.attachInterrupt(manejadoraTimer);
}

void manejadoraTimer(){
    segundos++;
    actualizar=true;
}

void actualizarReloj(){
  minutos += segundos / 60;
  segundos = segundos % 60;

  horas += minutos / 60;
  minutos = minutos % 60;

  horas = horas % 24;
}

void loop(){
  if(actualizar == true){
    actualizarReloj();
    //lcd.clear();
    lcd.noBlink();
    lcd.setCursor(0,1);
    sprintf(texto, "%02d:%02d:%02d",horas,minutos,segundos); 
    lcd.print(texto);

    //Serial.println("Presione una tecla para comenzar");
    delay(500);
    if(Serial.available()>0){
      Serial.println("Ingrese la hora: ");
      horas_alarma=Serial.readString();
      ha=horas_alarma.toInt();
      delay(4000);
      Serial.println("Ingrese los minutos: ");
      minutos_alarma=Serial.readString();
      ma=minutos_alarma.toInt();
      delay(4000);
      lcd.setCursor(0,3);
      sprintf(texto1, "%02d:%02d:%02d",ha,ma,0); 
      lcd.print(texto1);
    }
    if(horas == ha && minutos == ma && segundos == 0){
        Serial.println("Alarma Encendida");
        delay(1000);
    }
  }
}
