//Stack Game CopyRights from Antonio Carmona Lozano
//Property of Group C
//Creative electronics
#ifndef _STACK_H_
#define _STACK_H_

#include "pantalla.h"
#include "botones.h"

  //VARIABLES STACK
extern uint8_t stack_logo[];

uint8_t nivel;
uint8_t coor_x,coor_x2, coor_y;
uint8_t coor_x_ant,coor_x2_ant;
uint8_t anchura;
bool derecha, izquierda;
bool dentro;
  
void inicio(){
  
  LCD.clrScr();
  LCD.print("STARTING", CENTER, 15);
  LCD.print("STACK GAME...",CENTER, 30);
  LCD.update();
  delay(1500);
  LCD.clrScr();
  LCD.drawBitmap(0, 0, stack_logo, 84, 48);
  LCD.update();
  delay(1500);
  LCD.clrScr();
  //INICIALIZACION DE VARIBLES
    nivel=1;
    coor_x=0;
    anchura=44;
    derecha=true;
    izquierda=false;
    dentro=false;
    gameover=false;
    coor_y=45;
    coor_x_ant=19;
    coor_x2_ant=63;
    anchura=coor_x2_ant-coor_x_ant;
}


void hasGanado(){
    
     LCD.clrScr();
     LCD.print("YOU", CENTER, 15);
     LCD.print("WIN", CENTER, 30);
     LCD.update();   
     tone(PIN_BUZZER, 250,200);
     delay(200);
     tone(PIN_BUZZER, 350, 200);
     delay(200);
     tone(PIN_BUZZER, 1185, 350);
     delay(600);
     noTone(PIN_BUZZER);
     gameover=true;
     //Volver al menu  
} 
void borrarPiso(){
      
      LCD.clrLine(0,coor_y,84, coor_y);
      LCD.clrLine(0,coor_y-1,84, coor_y-1);
}
void dibujarPiso(){
      
      if(derecha==true){
        coor_x+=2;
        coor_x2+=2;
      }else if(izquierda==true){
        coor_x-=2;
        coor_x2-=2;
      }
      LCD.drawLine(coor_x,coor_y,coor_x2, coor_y);
      LCD.drawLine(coor_x,coor_y-1,coor_x2, coor_y-1);
      LCD.update();
      unsigned long tiempo =69-(nivel*3);
      delay(tiempo);

}
void comprobarPiso(){
  
  if((coor_x >= coor_x_ant)&&(coor_x <= coor_x2_ant)){
        coor_x_ant= coor_x;
        dentro=true;
      }
      if((coor_x2 <=coor_x2_ant)&&(coor_x2>=coor_x_ant)){
        coor_x2_ant=coor_x2;
        dentro=true;  
      }
      anchura=coor_x2_ant-coor_x_ant;
      if(dentro==true){
        LCD.drawLine(coor_x_ant,coor_y,coor_x2_ant, coor_y);
        LCD.drawLine(coor_x_ant,coor_y-1,coor_x2_ant, coor_y-1);
        dentro=false;
      }else{
        game_over();  
      }
}
void moverPiso()
{ 
    if(coor_x2 > 82){
      derecha=false;
      izquierda=true;
    }
    if(coor_x < 2){
      izquierda=false;
      derecha=true;
    }
      borrarPiso();
      dibujarPiso();
}

void subirPiso()
{
     borrarPiso();
     comprobarPiso();

}


void JugarStack(){
    inicio();
    while(gameover==false){
      LCD.print("Piso", RIGHT, 0);
      char cadena[16];
      sprintf(cadena, "%d", nivel);
      LCD.print(cadena,RIGHT, 8); 
      LCD.drawLine(19,47,63,47);
      LCD.drawLine(19,46,63,46);
  
      coor_x2 = coor_x+(anchura);
      moverPiso();
      if(nivel==23){
           hasGanado();  
      }
      if(PresionarAzul()){
           subirPiso();
           nivel++;
           coor_y-=2;
           coor_x=coor_x_ant;
        }
     if(PresionarRojo()){
        gameover=true;
      }
    }
}//JugarStack()

#endif
