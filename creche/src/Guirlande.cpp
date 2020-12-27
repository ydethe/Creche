#include "Guirlande.h"


Guirlande::Guirlande() {

}

Guirlande::Guirlande(uint8_t num_led) {
   m_num_led = num_led;
}

void Guirlande::allume(Adafruit_TLC59711* tlc, uint16_t intensite) {
   tlc->setPWM(m_num_led, intensite);
}

void Guirlande::setup_scintille(uint16_t lux_debut, uint16_t lux_fin) {
   m_niv_min = lux_debut;
   m_niv_max = lux_fin;
}

void Guirlande::update(Adafruit_TLC59711* tlc) {
   uint16_t lux;
   
   lux = random(m_niv_min,m_niv_max);
   
   Guirlande::allume(tlc, lux);
   
}
