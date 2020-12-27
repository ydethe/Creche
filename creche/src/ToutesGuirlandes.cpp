#include "ToutesGuirlandes.h"


ToutesGuirlandes::ToutesGuirlandes(Adafruit_TLC59711* tlc) {
    m_tlc = tlc;

    m_g_r_0 = Guirlande(0);
    m_g_g_0 = Guirlande(1);
    m_g_b_0 = Guirlande(2);

    m_g_r_1 = Guirlande(3);
    m_g_g_1 = Guirlande(4);
    m_g_b_1 = Guirlande(5);

    m_g_r_2 = Guirlande(6);
    m_g_g_2 = Guirlande(7);
    m_g_b_2 = Guirlande(8);

    m_g_r_3 = Guirlande(9);
    m_g_g_3 = Guirlande(10);
    m_g_b_3 = Guirlande(11);

}

// lux_debut et lux_fin doivent être compris entre 0 et 65535
void ToutesGuirlandes::setup_scintille(uint16_t lux_debut, uint16_t lux_fin) {
    m_g_r_0.setup_scintille(lux_debut, lux_fin);
    m_g_g_0.setup_scintille(lux_debut, lux_fin);
    m_g_b_0.setup_scintille(lux_debut, lux_fin);

    m_g_r_1.setup_scintille(lux_debut, lux_fin);
    m_g_g_1.setup_scintille(lux_debut, lux_fin);
    m_g_b_1.setup_scintille(lux_debut, lux_fin);

    m_g_r_2.setup_scintille(lux_debut, lux_fin);
    m_g_g_2.setup_scintille(lux_debut, lux_fin);
    m_g_b_2.setup_scintille(lux_debut, lux_fin);

    m_g_r_3.setup_scintille(lux_debut, lux_fin);
    m_g_g_3.setup_scintille(lux_debut, lux_fin);
    m_g_b_3.setup_scintille(lux_debut, lux_fin);

}

void ToutesGuirlandes::update() {
    m_g_r_0.update(m_tlc);
    m_g_g_0.update(m_tlc);
    m_g_b_0.update(m_tlc);

    m_g_r_1.update(m_tlc);
    m_g_g_1.update(m_tlc);
    m_g_b_1.update(m_tlc);

    m_g_r_2.update(m_tlc);
    m_g_g_2.update(m_tlc);
    m_g_b_2.update(m_tlc);

    m_g_r_3.update(m_tlc);
    m_g_g_3.update(m_tlc);
    m_g_b_3.update(m_tlc);

    // m_tlc->write();

}

void ToutesGuirlandes::allume(uint16_t level) {
    m_g_r_0.allume(m_tlc, level);
    m_g_g_0.allume(m_tlc, level);
    m_g_b_0.allume(m_tlc, level);

    m_g_r_1.allume(m_tlc, level);
    m_g_g_1.allume(m_tlc, level);
    m_g_b_1.allume(m_tlc, level);

    m_g_r_2.allume(m_tlc, level);
    m_g_g_2.allume(m_tlc, level);
    m_g_b_2.allume(m_tlc, level);

    m_g_r_3.allume(m_tlc, level);
    m_g_g_3.allume(m_tlc, level);
    m_g_b_3.allume(m_tlc, level);

    // m_tlc->write();

}