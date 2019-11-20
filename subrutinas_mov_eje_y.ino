#include "headers/header.h"

void EJEY_INIT()
{
    stepper.begin(STEPPER_RPM, STEPPER_MICROSTEPS);
}

uint8_t MOVIMIENTO_EJEY(uint8_t MOV_ID) //retornara 1 cuando se llame con parametro 1 y se haya cargado la hoja.
{
    uint32_t lM_y = millis();
    switch (MOV_ID)
    {
    case MOV_Y_ENTRAR_HOJA:
        moverHoja(-10); //hacer movimiento en reversa para cargar el resorte
        delay(100);
        moverHoja(10); //empezar a bajar...
        delay(100);

        lM_y = millis();
        while (!leerADC_DIG(pin_sensor_hoja))
        {
            if (millis() >= lM_y + 4500U) //probar por 4.5 segundos si entra o no la hoja...
                return (0);               //no tiene hoja...
            moverHoja(-1);
        }

        moverHoja(-19);
        return (1);
        break;

    case MOV_Y_MARGEN_SUPERIOR:
        moverHoja(-41);
        break;

    case MOV_Y_ESPACIO_LINEA:
        moverHoja(-2.5);
        break;

    case MOV_Y_ESPACIO_RENGLON:
        moverHoja(-5);
        break;

    case MOV_Y_SACAR_HOJA:
        while (leerADC_DIG(pin_sensor_hoja))
        {
            moverHoja(-1);
        }
        moverHoja(-80);
        delay(100);
        break;
    }
    while (stepper.getCurrentState() != stepper.STOPPED); //esperar a que se detenga.
}