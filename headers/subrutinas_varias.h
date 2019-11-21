#ifndef SUBRUTINAS_VARIAS_H
#define SUBRUTINAS_VARIAS_H


//Definicion de funciones
bool segmentoDeLineaNoVacio(int16_t desde, int16_t hasta, uint16_t index_y);
void SOLENOIDE_PUNTO(bool i);
int32_t diferencia(int32_t a, int32_t b);
bool leerADC_DIG(uint8_t pin);
void moverHoja(float milimetros);
void debugMovimientos();

#endif