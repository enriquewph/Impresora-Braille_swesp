#include "headers/header.h"

ESP32Encoder encoder;

void setup()
{
    initPins();

    Serial.begin(115200);

    encoder.attachHalfQuad(pin_encoder_a, pin_encoder_b);

    ledcAttachPin(pin_motor_a, MOTOR_A_PWM);
    ledcAttachPin(pin_motor_b, MOTOR_B_PWM);
    ledcSetup(MOTOR_A_PWM, 250, 8);
    ledcSetup(MOTOR_B_PWM, 250, 8);

    ejex_poner_a_cero();
    EJEX_MOVERSE_A_COORDENADA(1000);
    delay(500);
    EJEX_MOVERSE_A_COORDENADA(500);
    delay(500);
    EJEX_MOVERSE_A_COORDENADA(1500);
    delay(500);
    EJEX_MOVERSE_A_COORDENADA(2000);
    delay(500);
    EJEX_MOVERSE_A_COORDENADA(200);
    delay(500);
    EJEX_MOVERSE_A_COORDENADA(3500);
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
