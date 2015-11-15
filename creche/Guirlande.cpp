#include "Guirlande.h"


Guirlande::Guirlande(Adafruit_TLC59711* tlc, int num_block, Couleur coul) {
   m_tlc = tlc;
   m_num_block = num_block;
   m_coul = coul;
   m_pos_tableau = 0;
   for (int i=0; i<NB_CASES; i++) {
      m_sequentiel[i] = 0;
   }
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

void Guirlande::setup_rampe(uint16_t lux_debut, uint16_t lux_fin, int duree_ms) {
   float nb_lux;
   int attente;
   float f_deb,f_fin;
   float quantum;
   uint16_t lux_cmd;
   
   f_deb = float(lux_debut);
   f_fin = float(lux_fin);
   nb_lux = min(float(duree_ms)/1000./PERIODE_MAX*NB_CASES, NB_CASES-1); // On empeche que la rampe prenne plus que NB_CASES-1 cases
   quantum = (f_fin - f_deb)/nb_lux;
   
   for (int i=0; i<int(nb_lux); i++)
   {
      lux_cmd = lux_debut + uint16_t(quantum*i);
      
      // On borne le lux entre 1 et 65534
      m_sequentiel[i] = min(max(1, lux_cmd),65534);
      Serial.println(m_sequentiel[i]);
   }
   
   for (int i=int(nb_lux); i<NB_CASES; i++)
   {
      // Les lux nuls signifient : "retour au d�but du tableau"
      m_sequentiel[i] = 0;
   }
   
}

int Guirlande::update() {
   int attente;
   
   uint16_t lux = m_sequentiel[m_pos_tableau];
   attente = int(PERIODE_MAX*1000./NB_CASES);
   
   if (lux == 0) {
      Guirlande::reset();
   } else {
      Guirlande::allume(lux);
      m_pos_tableau++;
   }
   
   return attente;
   
}

void Guirlande::reset() {
   m_pos_tableau=0;
}



