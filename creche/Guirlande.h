#include <Adafruit_TLC59711.h>


#ifndef _GUIRLANDE_H
#define _GUIRLANDE_H

const uint16_t NB_CASES=50;
#define PERIODE_MAX 0.5

typedef enum {RED, GREEN, BLUE} Couleur;

class Guirlande {
private:
   int m_compteur;
   int m_num_block;
   Couleur m_coul;
   Adafruit_TLC59711* m_tlc;
   uint16_t m_sequentiel[NB_CASES];
   int m_pos_tableau;
   
public:
   Guirlande(Adafruit_TLC59711* tlc, int num_block, Couleur coul);
   ~Guirlande();
   
   void allume(uint16_t intensite);
   void eteind();
   
   void setup_rampe(uint16_t lux_debut, uint16_t lux_fin, int duree_ms);
   
   int update();
   void reset();
   
};

#endif

