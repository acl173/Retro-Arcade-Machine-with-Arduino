
#include <LCD5110_Graph.h>
#include "pantalla.h"

extern uint8_t SmallFont[];
extern uint8_t pacman1[];
extern uint8_t pacman2[];
extern uint8_t pacman3[];
extern uint8_t pill[];
extern uint8_t cocointro[];

int puntos;
long int tiempoahora;

#define Width  84
#define Hight  48
#define Range  12

int FirstShotX , FirstShotY;
int PointX, PointY;
int delaytime;

void setupCoco(){
  
  LCD.InitLCD();
  LCD.setFont(SmallFont);
  LCD.clrScr();
  LCD.print("STARTING", CENTER, 15);
  LCD.print("COCO GAME...",CENTER, 30);
  LCD.update();
  delay(1500);
  LCD.clrScr();
  LCD.drawBitmap(0, 0, cocointro, 84, 48);
  LCD.update();
  delay(1500);
  LCD.clrScr();
  gameover=false;
  puntos=0;
  /* Record Joystick corrected coordinates */
  FirstShotX = analogRead(A0);
  FirstShotY = analogRead(A1);
  
  /* Black specks the initial coordinates */
  PointX = 75;
  PointY = 20;
  
  /* Refresh time */
  delaytime = 50;
 
}

void JugarCoco(){
  
   setupCoco();
   tiempoahora=millis();
 
  while((millis()<tiempoahora+5000)&&(gameover==false)){
    
    uint8_t* bm;
    
    for (int i=-20; i<84; i++){
      LCD.clrScr();     
    
      /* Refresh Greedy Freak Bitmap */
      switch(((i+20)/3) % 4){
        case 0: bm=pacman1;
                break;
        case 1: bm=pacman2;
                break;
        case 2: bm=pacman3;
                break;
        case 3: bm=pacman2;
                break;
     }
      int sensorValueX = (analogRead(A0) - FirstShotX)*0.1 + 32;        //You can change the coefficient such as 0.08, which decide X-axis Range
      int sensorValueY = (FirstShotY - analogRead(A1))*0.06 + 14;        //You can change the coefficient such as 0.04, which decide Y-axis Range 
    
      LCD.drawBitmap(sensorValueX, sensorValueY, bm, 20, 20);
   
    /* Once the Greedy Freak be close to black specks, random another X and Y */
      TX:                                                                
      if( (sensorValueX-5 <= PointX && PointX <= sensorValueX+15) && (sensorValueY-3<= PointY && PointY <= sensorValueY + 20 )){
         PointX = random(0, 80);
         PointY = random(0, 43); 
         puntos=puntos+5; 
         goto TX;
      }else LCD.drawBitmap(PointX, PointY, pill, 5, 5);
      
      if(PresionarRojo()){
        gameover=true;
      }
    
      LCD.update();        //update and display the Bitmap
    
      delay(delaytime);
  }
 } 
}

void FinalCoco(){
     
     LCD.clrScr();
     LCD.print("TIEMPO EXPIRADO", CENTER, 10);
     LCD.print("PUNTUACION:", CENTER, 20);
     char cadena[16];
     sprintf(cadena,"%d",puntos);
     LCD.print(cadena,CENTER,30);
     LCD.update();
     tone(PIN_BUZZER, 660,200);
     delay(200);
     tone(PIN_BUZZER, 185, 800);
     delay(400);
     noTone(PIN_BUZZER);
     delay(400);
     delay(1000);
      
}
