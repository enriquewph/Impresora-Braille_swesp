#include <ESP32Encoder.h>
#include "header.h"

uint32_t lastMillis;

void setup()
{
    pinMode(2, OUTPUT);
    pinMode(MOTOR_A, OUTPUT);
    pinMode(MOTOR_B, OUTPUT);

    // Attache pins for use as encoder pins
    encoder.attachHalfQuad(ENCODER_A, ENCODER_B);
    Serial.begin(115200);

    EJEX_PONERACERO();

    lastMillis = millis();

    ledcAttachPin(MOTOR_A, MOTOR_A_PWM);
    ledcAttachPin(MOTOR_B, MOTOR_B_PWM);
    ledcSetup(MOTOR_A_PWM, MOTOR_PWM_FREQ, MOTOR_PWM_RESOLUCION);
    ledcSetup(MOTOR_B_PWM, MOTOR_PWM_FREQ, MOTOR_PWM_RESOLUCION);
    EJEX_POSICION_ENCODER_SETPOINT = 450;
}

void loop()
{

    if (millis() >= lastMillis + 500U)
    {
        lastMillis = millis();
        Serial.println("ACT: " + String(EJEX_POSICION_ENCODER_ACTUAL));
        Serial.println("SET: " + String(EJEX_POSICION_ENCODER_SETPOINT));
        Serial.println("RESTA: " + String(resta));
        MOVER(DISTANCIA_LETRA);
    }

    if (EJEX_POSICION_ENCODER_SETPOINT >= 3650)
        EJEX_POSICION_ENCODER_SETPOINT = 450;
    if (EJEX_POSICION_ENCODER_SETPOINT <= 450)
        EJEX_POSICION_ENCODER_SETPOINT = 450;

    if (Serial.available())
    {
        String input = Serial.readStringUntil('\n');
        
    }

    MOVIMIENTO_EJEX();
}
