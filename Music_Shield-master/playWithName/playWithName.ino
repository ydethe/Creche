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


#include <SD.h>
#include <arduino.h>
#include <MusicPlayer.h>
#include "Adafruit_TLC59711.h" // carte support LED
#include <SPI.h>               // bus entre carte mere et le support LED (circuit TLC 59711)

#define NUM_TLC59711 1         // nombre de support LED chainés en série 

#define data   2              // numéro du port de la carte mère donnant la data
#define clock  9              // numéro du port de la carte mère donnant le clock

Adafruit_TLC59711 tlc = Adafruit_TLC59711(NUM_TLC59711, clock, data); // création de l'objet tlc permettant de faire des actions sur le support LED (définis dans le .h)

void setup(void)
{
  Serial.begin(9600);
  player.begin();                      //will initialize the hardware and set default mode to be normal.
  player.setPlayMode(PM_REPEAT_ONE);   //set mode to repeat playing a song
  player.playOne("boeuf.mp3");        //play a song with its name
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

// Fill the dots one after the other with a color
void colorWipe(uint16_t r, uint16_t g, uint16_t b, uint8_t wait) {
  for(uint16_t i=0; i<8*NUM_TLC59711; i++) {
      tlc.setLED(i, r, g, b);
      tlc.write();
      delay(wait);
  }
}


