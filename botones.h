#ifndef _BOTONES_H_
#define _BOTONES_H_

#define PULSADORAZUL 12
#define PULSADORROJO 8

int ESTADOAZUL;
int ESTADOROJO;

void setupBotones() {
  pinMode(PULSADORAZUL, INPUT);
  pinMode(PULSADORROJO, INPUT);
}


//##############################################################################/
//###################COMPROBACION PULSACION BOTONES#############################/
//##############################################################################/


bool PresionarAzul() {
  
         if(digitalRead(PULSADORAZUL) == HIGH){                
         ESTADOAZUL=1;                                          
         }
         if(ESTADOAZUL==HIGH && digitalRead(PULSADORAZUL)==LOW){ 
         ESTADOAZUL=0;                                          
         return true;
         }else return false;
}
bool PresionarRojo() {
  
         if(digitalRead(PULSADORROJO) == HIGH){                 
         ESTADOROJO=1;                                          
         }
         if(ESTADOROJO==HIGH && digitalRead(PULSADORROJO)==LOW){                                               
         ESTADOROJO=0;                                         
         return true;
         }else return false;
}


#endif
