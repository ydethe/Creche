#include <SD.h>                // lecteur de carte SD
#include <arduino.h>           // 
#include <MusicPlayer.h>       // lecteur mp3
#include "ToutesGuirlandes.h"

#define NUM_TLC59711 1        // nombre de support LED chainés en série 
#define data   2              // numéro du port de la carte mère donnant la data
#define clock  9              // numéro du port de la carte mère donnant le clock

#define inc_tps 100           // attente en fin de boucle principale en millisecondes

#define SCINT_PERIOD 1
#define SCINT_MIN 50000
#define SCINT_MAX 65535

Adafruit_TLC59711 tlc = Adafruit_TLC59711(NUM_TLC59711, clock, data); // création de l'objet tlc permettant de faire des actions sur le support LED (définis dans le .h)
ToutesGuirlandes gui = ToutesGuirlandes(&tlc);

// Cette fonction n'est appelée qu'une seule fois
// à la mise sous tension de l'Arduino
void setup(void)
{
  Serial.begin(9600);
  
  player.begin();    //will initialize the hardware and set default mode to be normal.
  player.setPlayMode(PM_REPEAT_LIST);   //set mode to play shuffle
  player.scanAndPlayAll();
  tlc.begin();
  tlc.write();
  
  randomSeed(1442562427); // Initialisation du générateur de nombres aléatoires
  
  gui.setup_scintille(SCINT_PERIOD,SCINT_MIN,SCINT_MAX);
  
}

// Cette fonction est appelée en boucle à la fréquence du processeur (16MHz)
void loop(void)
{
  player.play();  //do some leisurely job
  
  gui.update();
  
  delay(inc_tps);

}


