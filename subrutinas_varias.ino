#include "headers/header.h"

bool segmentoDeLineaNoVacio(int16_t desde, int16_t hasta, uint16_t index_y)
{
    for (int16_t index_x = desde; index_x < hasta; index_x++)
    {
        if (bitArray[index_x][index_y])
            return true;
    }
    return false;
}

void SOLENOIDE_PUNTO(bool i)
{
    if (i)
    {
        delay(5);
        digitalWrite(pin_solenoide, HIGH);
        delay(80);
        digitalWrite(pin_solenoide, LOW);
        delay(10);
    }
    else
        return;
}

int32_t diferencia(int32_t a, int32_t b)
{
    if (a > b)
        return a - b;
    else if (a < b)
        return b - a;
    else
        return 0;
}

bool leerADC_DIG(uint8_t pin)
{
    uint16_t lectura = analogRead(pin);

    if (lectura <= 1800)
        return false;
    else if (lectura >= 2200)
        return true;
    else
        return false;
}

void moverHoja(float milimetros)
{
    long pasos = milimetros * PASOS_POR_MILIMETRO;
    stepper.move(pasos);
}

void debugMovimientos()
{
    if (Serial.available())
    {
        switch (Serial.readStringUntil('\n').toInt())
        {
        case 1:
            MOVIMIENTO_EJEY(MOV_Y_ENTRAR_HOJA);
            break;
        case 2:
            SOLENOIDE_PUNTO(1);
            break;
        case 3:
            EJEX_MOVERSE_A_COORDENADA(DIST_X_BORDE_IZQUIERDO);
            MOVIMIENTO_EJEX(MOV_X_MARGEN, 1);
            break;
        case 4:
            MOVIMIENTO_EJEX(MOV_X_ESPACIO_ENTRE_PUNTOS, 1);
            break;
        case 5:
            MOVIMIENTO_EJEX(MOV_X_ESPACIO_ENTRE_LETRAS, 1);
            break;
        case 6:
            MOVIMIENTO_EJEY(MOV_Y_ESPACIO_LINEA);
            break;
        case 7:
            MOVIMIENTO_EJEY(MOV_Y_ESPACIO_RENGLON);
            break;
        case 8:
            MOVIMIENTO_EJEY(MOV_Y_SACAR_HOJA);
            break;
        case 9:
            MOVIMIENTO_EJEY(MOV_Y_MARGEN_SUPERIOR);
            break;
        }
    }
}