#include "Guirlande.h"


Guirlande::Guirlande(Adafruit_TLC59711* tlc, int num_block, Couleur coul) {
   m_tlc = tlc;
   m_num_block = num_block;
   m_coul = coul;
   m_chrono = 0;
}


Guirlande::~Guirlande() {
   
}

void Guirlande::allume(uint16_t intensite) {
   if (m_coul==RED)
      m_tlc->setLED(m_num_block, intensite, 0, 0);
   else if (m_coul==GREEN)
      m_tlc->setLED(m_num_block, 0, intensite, 0);
   else if (m_coul==BLUE)
      m_tlc->setLED(m_num_block, 0, 0, intensite);
      
   m_tlc->write();
   
}

void Guirlande::eteind() {
   Guirlande::allume(0);
   
}

void Guirlande::setup_scintille(uint16_t nb_incr, uint16_t lux_debut, uint16_t lux_fin) {
   m_niv_min = lux_debut;
   m_niv_max = lux_fin;
   m_nb_incr = nb_incr;
   m_chrono  = m_nb_incr;
}

void Guirlande::update() {
   int lux;
   
   m_chrono += 1;
   if (m_chrono >= m_nb_incr) {
      m_lux = random(m_niv_min,m_niv_max);
      m_chrono = 0;
   }
   
   Guirlande::allume(m_lux);
   
}



