#include "Guirlande.h"

#ifndef _TOUTES_GUIRLANDE_H
#define _TOUTES_GUIRLANDE_H

class ToutesGuirlandes {
private:
    Adafruit_TLC59711* m_tlc;
    
    Guirlande m_g_r_0;
    Guirlande m_g_g_0;
    Guirlande m_g_b_0;
    Guirlande m_g_r_1;
    Guirlande m_g_g_1;
    Guirlande m_g_b_1;
    Guirlande m_g_r_2;
    Guirlande m_g_g_2;
    Guirlande m_g_b_2;
    Guirlande m_g_r_3;
    Guirlande m_g_g_3;
    Guirlande m_g_b_3;

public:
    ToutesGuirlandes(Adafruit_TLC59711*);

    // lux_debut et lux_fin doivent être compris entre 0 et 65535
    void setup_scintille(uint16_t lux_debut, uint16_t lux_fin);
   
    void update();

    void allume(uint16_t level=65535);

};

#endif
