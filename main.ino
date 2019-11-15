

#include "headers/header.h"

void setup()
{    
    initPins();
    
    Serial.begin(115200);
    BrailleComLib_Init();
}

void loop()
{
    BrailleComLib_Loop();
    if (BCLV_IMPRIMIENDO) //Se recibio la instrucción de imprimir una hoja. proceder a imprimir.
    {

        BCLV_IMPRIMIENDO = 0;
    }
}
