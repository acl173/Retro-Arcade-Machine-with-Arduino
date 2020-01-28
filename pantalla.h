#ifndef PANTALLA_H
#define PANTALLA_H
//2325
int PIN_BUZZER =A2;

#include <LCD5110_Graph.h>

// Software SPI (slower updates, more flexible pin options):
// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (DC)
// pin 4 - LCD chip select (CE)
// pin 3 - LCD reset (RST)

LCD5110 LCD(7,6,5,3,4);

bool gameover=false;

extern uint8_t SmallFont[];
extern uint8_t PantallaInicio[];
extern uint8_t PantallaInicio2[];

void menuInit(){
    
    LCD.clrScr();
    LCD.setFont(SmallFont);
    LCD.print("MENU DE JUEGOS",CENTER,0);
    LCD.drawLine(0, 9, 83, 9);
    LCD.print(">STACK",0,15);
    LCD.print(">SPACE",0,25);
    LCD.print(">COCO",0,35);
    LCD.update();
   
}
void musicaIntro(){
  
  LCD.clrScr();
  LCD.drawBitmap(0, 0, PantallaInicio, 84, 48);
  LCD.update();
  tone(PIN_BUZZER,988);
  delay(250);
  tone(PIN_BUZZER,1319);
  delay(500); 
  tone(PIN_BUZZER,1568);
  delay(125);
  tone(PIN_BUZZER,1480);
  delay(125);
  LCD.clrScr();
  LCD.drawBitmap(0, 0, PantallaInicio2, 84, 48);
  LCD.update();
  tone(PIN_BUZZER,1319);
  delay(500);
  tone(PIN_BUZZER,1976);
  delay(250);
  tone(PIN_BUZZER,1760);
  delay(625);
  noTone(PIN_BUZZER);

}

void setupPANTALLA() {
  
  LCD.InitLCD();      
  LCD.setContrast(75); 
  LCD.clrScr(); 
  musicaIntro();
  menuInit(); 
  
}

void game_over(){
  
     LCD.clrScr();
     LCD.print("GAME", CENTER, 15);
     LCD.print("OVER", CENTER, 30);
     LCD.update();
     tone(PIN_BUZZER, 660,200);
     delay(200);
     tone(PIN_BUZZER, 185, 800);
     delay(400);
     noTone(PIN_BUZZER);
     delay(400);
     gameover=true;
}

#endif
