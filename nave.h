#include "pantalla.h"
#include "botones.h"

extern uint8_t spaceini[];
extern uint8_t ship[];
extern uint8_t enemy[];
extern uint8_t SmallFont[];


int enemy_0_pos, enemy_1_pos, enemy_phase;
int Joy_X;
int game_speed = 0;
int score = 0;
char POS=2;
boolean enemy_dead = true;
boolean control = true;

void inicio_nave(){
  LCD.clrScr();
  LCD.print("STARTING", CENTER, 15);
  LCD.print("SPACE GAME...",CENTER, 30);
  LCD.update();
  delay(1500);
  LCD.clrScr();
  LCD.drawBitmap(0,0,spaceini,84,48);
  LCD.update();
  delay(1500);
  LCD.clrScr();   
  gameover=false;
  game_speed = 0;
  score = 0;
  POS=2;
  enemy_dead = true;
  control = true;
}

void Level_Controller(){ 
 
  if (score>=0 && score<=3){
    game_speed = 0; 
    LCD.update();
    delay(100); 
  }
  
  if (score>3 && score<=6){
    game_speed = 1; 
    LCD.update();
    delay(90); 
  }
 
  if (score>6 && score<=9){
    game_speed = 2;
    LCD.update();
    delay(80); 
  }
  
  if (score>9 && score<=12){
    game_speed = 3; 
    LCD.update();
    delay(70);
  }
  
  if (score>12 && score<=15){
    game_speed = 4; 
    LCD.update();
    delay(60); 
  }
  
  if (score>15 && score<=18){
    game_speed = 5;
    LCD.update();
    delay(50); 
  }
  
  if (score>18 && score<=21){
    game_speed = 6;
    LCD.update();
    delay(40); 
  }
  
  if (score>21 && score<=24){
    game_speed = 7; 
    LCD.update();
    delay(30); 
  }
}

void enemy_ship(int place, int phase){
  
  if (place==1){
  LCD.drawBitmap(2, phase, enemy, 15, 15);
  LCD.update();
  }
  
  if (place==2){
  LCD.drawBitmap(18, phase, enemy, 15, 15);
  LCD.update();
  }
  if (place==3){
  LCD.drawBitmap(34, phase, enemy, 15, 15);
  LCD.update();
  }

}

void gameLCD(){
  
  LCD.drawLine(0, 0, 0, 47);
  LCD.drawLine(50, 0, 50, 47);
  LCD.drawLine(0, 47, 50, 47);
  LCD.update();
  LCD.print("Speed",52,2);
  char cadena[2];
  sprintf(cadena,"%d",game_speed);
  LCD.print(cadena,56,12);
  LCD.print("Score",52,25);
  char cadena2[6];
  sprintf(cadena2,"%d",score);
  LCD.print(cadena2,56,37);
  LCD.update();

}

void player_car(char pos){
  
  if (pos==1){
    LCD.drawBitmap(2, 32, ship, 15, 15);
    LCD.update();
  }
  
  if (pos==2){
    LCD.drawBitmap(18, 32, ship, 15, 15);
    LCD.update();
  }
  
  if (pos==3){
    LCD.drawBitmap(34, 32, ship, 15, 15);
    LCD.update();
  }

}

void Jugar_Nave(){
 
  inicio_nave();
  
  while(gameover==false){
 
    LCD.clrScr();   
    gameLCD(); 
    LCD.update();  
    Joy_X = analogRead(A0); 
    
    if (Joy_X < 312 && POS!=1 && control==true){ 
      POS--; control = false;
    }else if(Joy_X > 712 && POS!=3 && control==true){ 
      POS++; control = false;
     }else if (Joy_X >502 && Joy_X<522)control = true;  

    player_car(POS); 

    if (enemy_dead){ 
      enemy_0_pos = POS;
      enemy_1_pos = random(0,4);
      enemy_phase = 0;
      enemy_dead = false; 
      LCD.update();
    }

    enemy_ship (enemy_0_pos,enemy_phase); enemy_phase++; 
    enemy_ship (enemy_1_pos,enemy_phase); enemy_phase++; 

    if (enemy_phase>22 && ((enemy_0_pos == POS) || (enemy_1_pos == POS))) game_over(); 
  
    if (enemy_phase>40){
      enemy_dead = true; 
      score++;
    } 
    
    Level_Controller();
    LCD.update();
    
    if(PresionarRojo()){
      gameover=true;
    }
  }
}
