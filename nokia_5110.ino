
#include <avr/pgmspace.h>
#include "Stack.h"
#include "botones.h"
#include "nave.h"
#include "pantalla.h"
#include "Coco.h"

int X,Y;//j1->X;j2->Y;
int JX=A0;
int JY=A1;

int menuitem=1,azul=9,verde=10,rojo=11;
uint8_t irojo=255,iverde=255,iazul=255;

void setup() {

  setupBotones();
  setupPANTALLA();
  pinMode(JX,INPUT);
  pinMode(JY,INPUT);
  pinMode(rojo,OUTPUT);
  pinMode(verde,OUTPUT);
  pinMode(azul,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  
  X=analogRead(JX);
  Y=analogRead(JY);
  actualizaMenu();
  seleccionarJuego();
  RGB();
  
  
  }

//#################################################################################/
//###################COMPROBACION DIRECCIONES JOYSTICK#############################/
//#################################################################################/

bool ComprobarBajar(){
  
  if (Y >= 0 && Y < 480){         // si Y esta en la zona de abajo
    return true;
  }else return false;

}
bool ComprobarSubir(){
  
  if (Y > 520 && Y <= 1023){          // si Y esta en la zona de arriba
    return true;
  }else return false;
}

//##############################################################/
//###################MENU PRINCIPAL#############################/
//##############################################################/

  void actualizaMenu(){
     
   // while(botonAzul==false){ //mientras no se hace ninguna seleccion , la pantalla se quedará pillada en el menu de seleccion
   
    if (menuitem==1){ 
      
    LCD.invertText(true);    
    LCD.print(">STACK",0,15); 
    LCD.update();
    
    }else {
         LCD.invertText(false); 
         LCD.print(">STACK",0,15); 
         LCD.update();
    }
   
  
    if (menuitem==2){
      
    LCD.invertText(true);    
    LCD.print(">SPACE",0,25); 
    LCD.update();
  
    }else{
         LCD.invertText(false); 
         LCD.print(">SPACE",0,25);
         LCD.update();
    }
    
    if (menuitem==3){ 
   
    LCD.invertText(true);    
    LCD.print(">COCO",0,35); 
    LCD.update();
    
    }else{
         LCD.invertText(false); 
         LCD.print(">COCO",0,35);
         LCD.update();
    }

    if(ComprobarBajar()){
      menuitem++;
      delay(300);
      if(menuitem>3){
        menuitem=1;
      }
    }
    if(ComprobarSubir()){
      menuitem--;
      delay(300);
      if(menuitem<1){
        menuitem=3;
      }
    }

  }//Actualiza MENU

//###################################################################/
//###################SELECCION DE JUEGOS#############################/
//###################################################################/

void seleccionarJuego(){
  
    if ((PresionarAzul())) {
      if(menuitem == 1)  {
   ///////////////////////////////////// 
    JugarStack();
    menuInit();
    menuitem=1;
   //////////////////////////////////     
   }

   if (menuitem == 2)  {
   /////////////////////////////////////
    Jugar_Nave();
    menuInit();
    menuitem=1;
 
   //////////////////////////////////     
  }
    if(menuitem == 3){
   ///////////////////////////////////// 
    JugarCoco();
    FinalCoco();
    menuInit();
    menuitem=1;
   //////////////////////////////////     
  }
    }
}

void RGB(){
  
  irojo=irojo-3;
  iverde=iverde-5;
  iazul=iazul-7;
  
  if(irojo<=0) irojo=255;
  if(iverde<=0) iverde=255;
  if(iazul<=0) iazul=255;
  
  analogWrite(rojo,irojo);
  analogWrite(verde,iverde);
  analogWrite(azul,iazul);
  
}
