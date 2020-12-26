#include "Guirlande.h"


Guirlande::Guirlande() {

}


Guirlande::Guirlande(int num_block, Couleur coul) {
   m_num_block = num_block;
   m_coul = coul;
   m_chrono = 0;
}


Guirlande::~Guirlande() {
   
}

void Guirlande::allume(Adafruit_TLC59711* tlc, uint16_t intensite) {
   if (m_coul==RED)
      tlc->setLED(m_num_block, intensite, 0, 0);
   else if (m_coul==GREEN)
      tlc->setLED(m_num_block, 0, intensite, 0);
   else if (m_coul==BLUE)
      tlc->setLED(m_num_block, 0, 0, intensite);
      
}

void Guirlande::setup_scintille(uint16_t nb_incr, uint16_t lux_debut, uint16_t lux_fin) {
   m_niv_min = lux_debut;
   m_niv_max = lux_fin;
   m_nb_incr = nb_incr;
   m_chrono  = m_nb_incr;
}

void Guirlande::update(Adafruit_TLC59711* tlc) {
   uint16_t lux;
   
   m_chrono += 1;
   if (m_chrono >= m_nb_incr) {
      lux = random(m_niv_min,m_niv_max);
      m_chrono = 0;
   }
   
   Guirlande::allume(tlc, lux);
   
}
