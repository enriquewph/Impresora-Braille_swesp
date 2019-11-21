#include "headers/header.h"

void setup()
{
    initPins();
    Serial.begin(115200);
    SerialBT.begin("Impresora"); //Bluetooth device name
    EJEX_INIT();
    EJEY_INIT();
    BrailleComLib_Init();

    ejex_poner_a_cero();
}

void loop()
{
    BrailleComLib_Loop();

    if (BCLV_IMPRIMIENDO) //Se recibio la instrucción de imprimir una hoja. proceder a imprimir.
    {
        eventArgs_t eventFromResult = rutinaImpresion();

        BCL_SendEvent(eventFromResult.result, eventFromResult.code);

        BCLV_IMPRIMIENDO = 0;
    }
}

eventArgs_t rutinaImpresion()
{
    eventArgs_t retArgs;

    SerialBT.println("Comenzando Impresion");
    ejex_poner_a_cero(); //Correr el carrete asi no interfiere con el mecanismo de carga de hoja.

    if (!MOVIMIENTO_EJEY(MOV_Y_ENTRAR_HOJA))
    {
        //No se pudo cargar la hoja.
        retArgs.result = BCLE_EVENTO_IMPRESION_FAIL;
        retArgs.code = 0;
        return retArgs;
    }

    //Ubicar la hoja en X,Y 0,0
    MOVIMIENTO_EJEY(MOV_Y_MARGEN_SUPERIOR);
    for (int i = 0; i < 27; i++)
    {
        MOVIMIENTO_EJEY(MOV_Y_ESPACIO_LINEA);
    }



    uint16_t index_y = 0;

    imprimirLinea(0, 1);
    MOVIMIENTO_EJEY(MOV_Y_ESPACIO_LINEA);
    imprimirLinea(1, 1);
    MOVIMIENTO_EJEY(MOV_Y_ESPACIO_LINEA);
    imprimirLinea(2, 1);
    MOVIMIENTO_EJEY(MOV_Y_ESPACIO_RENGLON);

    MOVIMIENTO_EJEY(MOV_Y_SACAR_HOJA);

    retArgs.result = BCLE_EVENTO_IMPRESION_OK;
    retArgs.code = 0;
    return retArgs;
}

void imprimirLinea(uint16_t index_y, uint8_t direccion)
{
    SerialBT.println("Imprimiendo linea en direccion: " + String(direccion));
    if (direccion)
    {
        ejex_poner_a_cero();
        EJEX_MOVERSE_A_COORDENADA(DIST_X_BORDE_IZQUIERDO + DIST_X_MARGEN);

        for (uint16_t index_x = 0; index_x < BCL_SIZE_BITARRAY_X; index_x++)
        {
            SerialBT.println("X" + String(encoder.getCount()) + ":" + bitArray[index_x][index_y]);

            SOLENOIDE_PUNTO(bitArray[index_x][index_y]);

            if (index_x % 2) //Debe ir un espacio entre letras
                MOVIMIENTO_EJEX(MOV_X_ESPACIO_ENTRE_LETRAS, 1);
            else
                MOVIMIENTO_EJEX(MOV_X_ESPACIO_ENTRE_PUNTOS, 1);
            
            if (!segmentoDeLineaNoVacio(index_x + 1, BCL_SIZE_BITARRAY_X, index_y))
            {
                SerialBT.println(F("No hay mas puntos en lo que resta de esta linea."));
                return;
            }
        }
    }
    else
    {
        EJEX_MOVERSE_A_COORDENADA(DIST_X_MARGEN_IZQ_DESDE_BORDE_NL);

        for (uint16_t index_x = BCL_SIZE_BITARRAY_X; index_x > 0; index_x--)
        {
            uint16_t newIndex_x = index_x - 1;
            SerialBT.println("X" + String(encoder.getCount()) + ":" + bitArray[newIndex_x][index_y]);

            SOLENOIDE_PUNTO(bitArray[newIndex_x][index_y]);

            if (newIndex_x % 2)                                    //Debe ir un espacio entre letras
                MOVIMIENTO_EJEX(MOV_X_ESPACIO_ENTRE_PUNTOS, 0); //la expresion esta al reves..
            else
                MOVIMIENTO_EJEX(MOV_X_ESPACIO_ENTRE_LETRAS, 0);
            
            if (!segmentoDeLineaNoVacio(0, index_x - 1, index_y)) //probar.
            {
                SerialBT.println(F("No hay mas puntos en lo que resta de esta linea."));
                return;
            }
        }
    }
    return;
}