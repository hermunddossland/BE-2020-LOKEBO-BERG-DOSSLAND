#include <unistd.h>
#include "core_simulation.h"

// la fonction d'initialisation d'arduino
void Board::setup(){
  // on configure la vitesse de la liaison
  Serial.begin(9600);
// on fixe les pin en entree et en sorite en fonction des capteurs/actionneurs mis sur la carte
  pinMode(1,INPUT);
  pinMode(0,OUTPUT);
  //%%%%%%%%%%%%%%%%%
  pinMode(2,INPUT);
  pinMode(3,OUTPUT);
  //%%%%%%%%%%%%%%%%
}

// la boucle de controle arduino
void Board::loop(){
  char buf[100];
  int val;
  char buff[100];
  int l;
  static int cpt=0;
  static int bascule=0;
  int i=0;
  for(i=0;i<10;i++){
    // lecture sur la pin 1 : capteur de temperature
    val=analogRead(1);
    l = analogRead(2);
    sprintf(buff, "luminosite %d", l);
    Serial.println(buff);
    sprintf(buf,"temperature %d",val);
    Serial.println(buf);
    if(cpt%5==0){
        // tous les 5 fois on affiche sur l ecran la temperature
      sprintf(buf,"%d",val);
      sprintf(buff, "%d", l);
      bus.write(2,buff,100);
      bus.write(1,buf,100);
    }
    cpt++;
    sleep(1);
  }
// on eteint et on allume la LED
  if(bascule){
    digitalWrite(0,HIGH);
    digitalWrite(3,HIGH);
  }
  else {
    digitalWrite(0,LOW);
    digitalWrite(3,LOW);
  }
  bascule=1-bascule;

}
