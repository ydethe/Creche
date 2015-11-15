/*
 * playWithName.ino
 * Example sketch for MusicShield 2.0
 *
 * Copyright (c) 2012 seeed technology inc.
 * Website    : www.seeed.cc
 * Author     : Jack Shao (jacky.shaoxg@gmail.com)
 * Create Time: Mar 2014
 * Change Log :
 *
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <SD.h>                // lecteur de carte SD
#include <arduino.h>           // 
#include <MusicPlayer.h>       // lecteur mp3
#include <Adafruit_TLC59711.h> // carte support LED
#include <SPI.h>               // bus entre carte mere et le support LED (circuit TLC 59711)
#include "Guirlande.h"               // bus entre carte mere et le support LED (circuit TLC 59711)

#define NUM_TLC59711 1         // nombre de support LED chainés en série 
#define data   2              // numéro du port de la carte mÃ¨re donnant la data
#define clock  9              // numéro du port de la carte mÃ¨re donnant le clock

long probaflamme;
int att;

// La variable tlc désigne le driver de LEDs :
// il fournit des fonctions toutes faites qui permettent de manipuler les lignes de LEDs
// Pour mémoire, le module acheté permet de gérer 12 lignes de LEDs
Adafruit_TLC59711 tlc = Adafruit_TLC59711(NUM_TLC59711, clock, data); // création de l'objet tlc permettant de faire des actions sur le support LED (définis dans le .h)
Guirlande g_R0 = Guirlande(&tlc, 0, RED);
Guirlande g_R3 = Guirlande(&tlc, 3, RED);
Guirlande g_G2 = Guirlande(&tlc, 2, GREEN); // 2 : numéro du bloc, 1 = G (0=R

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
  
  g_R0.setup_rampe(0, 65535, 500);
  g_G2.setup_rampe(65535, 0, 500);
  g_R3.setup_scintille(0, 25000);
  
}

// Cette fonction est appelée en boucle à la fréquence du processeur (16MHz)
// D'où la diffculté d'avoir une heure fiable
void loop(void)
{ 
  player.play();  //do some leisurely job
  
  att = g_R0.update();
  att = g_R3.update();
  att = g_G2.update();
  delay(att);

}

