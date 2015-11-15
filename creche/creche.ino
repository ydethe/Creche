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
#include "Adafruit_TLC59711.h" // carte support LED
#include <SPI.h>               // bus entre carte mere et le support LED (circuit TLC 59711)

#define NUM_TLC59711 1         // nombre de support LED chainÃ©s en sÃ©rie 
#define BUFSZE 128

#define data   2              // numÃ©ro du port de la carte mÃ¨re donnant la data
#define clock  9              // numÃ©ro du port de la carte mÃ¨re donnant le clock

// On the Ethernet Shield, CS is pin 4. Note that even if it's not
// used as the CS pin, the hardware CS pin (10 on most Arduino boards,
// 53 on the Mega) must be left as an output or the SD library
// functions will not work.
const int chipSelect = 4;

Adafruit_TLC59711 tlc = Adafruit_TLC59711(NUM_TLC59711, clock, data); // crÃ©ation de l'objet tlc permettant de faire des actions sur le support LED (dÃ©finis dans le .h)

void setup(void)
{
  Serial.begin(9600);
  
  player.begin();    //will initialize the hardware and set default mode to be normal.
  player.setPlayMode(PM_REPEAT_ONE);   //set mode to repeat playing a song
//  charge_sequence();
  player.playOne("boeuf.mp3");         //play a song with its name
  tlc.begin();
  tlc.write();
  
}

void loop(void)
{
  player.play();  //do some leisurely job
  
  colorWipe(65535, 0, 0, 100); // "Red" (depending on your LED wiring)
  delay(200);
  colorWipe(0, 65535, 0, 100); // "Green" (depending on your LED wiring)
  delay(200);
  colorWipe(0, 0, 65535, 100); // "Blue" (depending on your LED wiring)
  delay(200);
  
}

// Lecture d'une ligne d'un fichier ASCII
int saute_commentaires(SdFile file, char* buf, int* sze) {
  char b; // Le caractere lu
  char tmp[BUFSZE]; // La ligne reconstituee
  char *dbg; // Ligne de debug
  
  // Tant qu'on lit des commentaires
  while (true) {
    *sze = 0;
    file.read(&b, 1);
    if ((int)b == -1) return 3;
    
    // Tant qu'on n'a pas detecte la fin de ligne ('\n')
    while (b != '\n' || true) {
      Serial.print("Debug\n");
      Serial.print(b);
      
      tmp[*sze] = b;
      sze++;
      if (*sze > BUFSZE) return 1;
      
      file.read(&b, 1);
      if (b == -1) return 3;
      
    }
    *sze++;
    Serial.print("*sze\n");
    Serial.print(*sze);
    
    // On arrete la boucle principale des qu'on a une ligne qui ne commence pas par #
    Serial.print("tmp[0]\n");
    Serial.print(tmp[0]);
    if (tmp[0] != '#') {
      Serial.print("Pas un commentaire!\n");
      break;
    }
    
  }
  
  // On alloue buf pour communiquer le resultat a l'appelant
  buf = (char*)malloc(*sze);
  if (buf == NULL) return 2;
  
  memcpy(buf, tmp, *sze);
  buf[*sze] = '\0';
  
  return 0;
  
}

void charge_sequence() {
  SdFile seq;
  
  char* line;
  int istat;
  int sze;
  
  if (!seq.open(&root, "sequence.txt", O_READ))
    {
      Serial.print("Erreur");
      return;
    }
  
  istat = saute_commentaires(seq, line, &sze);
  Serial.print("saute_commentaires\n");
  Serial.print(istat);
  Serial.print(line);
  
}

// Fill the dots one after the other with a color
void colorWipe(uint16_t r, uint16_t g, uint16_t b, uint8_t wait) {
  for(uint16_t i=0; i<8*NUM_TLC59711; i++) {
      tlc.setLED(i, r, g, b);
      tlc.write();
      delay(wait);
  }
}



