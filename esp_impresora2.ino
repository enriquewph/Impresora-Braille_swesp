#include <ESP32Encoder.h>
#include "header.h"
#include "BasicStepperDriver.h"

void setup()
{
    //Pines out
    pinMode(SOLENOIDE, OUTPUT);
    pinMode(MOTOR_A, OUTPUT);
    pinMode(MOTOR_B, OUTPUT);
    // Attache pins for use as encoder pins
    encoder.attachHalfQuad(ENCODER_A, ENCODER_B);
    // Serial
    Serial.begin(115200);
    EJEX_PONERACERO();

    // Motor
    ledcAttachPin(MOTOR_A, MOTOR_A_PWM);
    ledcAttachPin(MOTOR_B, MOTOR_B_PWM);
    ledcSetup(MOTOR_A_PWM, MOTOR_PWM_FREQ, MOTOR_PWM_RESOLUCION);
    ledcSetup(MOTOR_B_PWM, MOTOR_PWM_FREQ, MOTOR_PWM_RESOLUCION);

    //steper

    stepper.begin(RPM, MICROSTEPS);

    //funciones varias
}

void loop()
{

   
  
    if (Serial.available())
    {
        String input = Serial.readStringUntil('\n');
        int a = input.toInt();
        if (a == 1)
            MOVIMIENTO_EJEY(ENTRAR_HOJA);
        if (a == 2)
            punto();
        if (a == 3)
        {
            EJEX_POSICION_ENCODER_SETPOINT = DISTANCIA_MARGEN_DER;
            MOVER(DISTANCIA_MARGEN);
            MOVIMIENTO_EJEX();
        }
        if (a == 4)
        {
            MOVER(DISTANCIA_LETRA);
            MOVIMIENTO_EJEX();
        }
        if (a == 5)
        {
            MOVER(DISTANCIA_LyL);
            MOVIMIENTO_EJEX();
        }
        if (a == 6)
            MOVIMIENTO_EJEY(ESPA_LINEA);
        if (a == 7)
            MOVIMIENTO_EJEY(ESPA_RENGLON);
        if (input == "I")
            escritura();
    }

}
