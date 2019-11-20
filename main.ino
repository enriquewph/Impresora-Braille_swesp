

#include "headers/header.h"

DriverMotores driverMotores;

void setup()
{    
    initPins();
    
    Serial.begin(115200);

    driverMotores.ejex_poner_a_cero();
    driverMotores.EJEX_POSICION_ENCODER_SETPOINT = 2000;
    driverMotores.movimiento_eje_x();

    //BrailleComLib_Init();
}

void loop()
{
    //BrailleComLib_Loop();
    if (BCLV_IMPRIMIENDO) //Se recibio la instrucción de imprimir una hoja. proceder a imprimir.
    {

        BCLV_IMPRIMIENDO = 0;
    }
}
