#include <Adafruit_TLC59711.h>

#ifndef _GUIRLANDE_H
#define _GUIRLANDE_H

#define PERIODE_MAX 0.5

typedef enum {RED, GREEN, BLUE} Couleur;

class Guirlande {
private:
   // int m_compteur;
   int m_num_block;
   Couleur m_coul;
   uint16_t m_niv_min, m_niv_max,m_nb_incr;
   uint16_t m_chrono;
   
public:
   Guirlande();
   Guirlande(int num_block, Couleur coul);
   ~Guirlande();
   
   void allume(Adafruit_TLC59711* tlc, uint16_t intensite);
   
   // lux_debut et lux_fin doivent être compris entre 0 et 65535
   void setup_scintille(uint16_t nb_incr, uint16_t lux_debut, uint16_t lux_fin);
   
   void update(Adafruit_TLC59711* tlc);
   
};

#endif

