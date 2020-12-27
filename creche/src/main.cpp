#include <arduino.h>
#include "Adafruit_TLC59711.h"
#include <SPI.h>
#include <SD.h>          // lecteur de carte SD
#include <MusicPlayer.h> // lecteur mp3

#include "ToutesGuirlandes.h"

// Voir tuto driver LED :
// https://learn.adafruit.com/tlc5947-tlc59711-pwm-led-driver-breakout/python-circuitpython
// Music Shield V2.0 Doc mise à jour : https://wiki.seeedstudio.com/Music_Shield_V2.2/

#define NUM_TLC59711 1 // nombre de support LED chainés en série 
#define clock 2 // Broche Arduino connectée à la broche CI du driver
#define data  9 // Broche Arduino connectée à la broche DI du driver

#define inc_tps 100 // attente en fin de boucle principale en millisecondes

#define SCINT_MIN 40000
#define SCINT_MAX 65535

Adafruit_TLC59711 tlc = Adafruit_TLC59711(NUM_TLC59711, clock, data);
ToutesGuirlandes gui = ToutesGuirlandes(&tlc);

// Cette fonction n'est appelée qu'une seule fois
// à la mise sous tension de l'Arduino
void setup(void)
{
  Serial.begin(9600);
  pinMode(10, OUTPUT);

  player.begin();
  player.setPlayMode(PM_REPEAT_LIST);   //set mode to play shuffle
  player.scanAndPlayAll();

  tlc.begin();
  tlc.write();
    
  gui.setup_scintille(SCINT_MIN,SCINT_MAX);
  
}

// Cette fonction est appelée en boucle à la fréquence du processeur (16MHz)
void loop(void)
{
  player.play();
  
  gui.update();
  tlc.write();

  delay(inc_tps);

}

