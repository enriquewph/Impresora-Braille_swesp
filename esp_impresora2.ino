

#include <ESP32Encoder.h>

#include <PID_v1.h>

#include <math.h> // round, floor, ceil, trunc

#include "header.h"

ESP32Encoder encoder;

double EJEX_POSICION_ENCODER_SETPOINT = 0;
double EJEX_POSICION_ENCODER_ACTUAL;
uint16_t resta;

uint32_t lastMillis;

void setup()
{
    // put your setup code here, to run once:
    pinMode(2, OUTPUT);
    pinMode(MOTOR_A, OUTPUT);
    pinMode(MOTOR_B, OUTPUT);

    // Attache pins for use as encoder pins
    encoder.attachHalfQuad(ENCODER_A, ENCODER_B);
    Serial.begin(115200);
    EJEX_POSICION_ENCODER_SETPOINT = 0;
    EJEX_PONERACERO();

    lastMillis = millis();

    ledcAttachPin(MOTOR_A, MOTOR_A_PWM);
    ledcAttachPin(MOTOR_B, MOTOR_B_PWM);
    ledcSetup(MOTOR_A_PWM, MOTOR_PWM_FREQ, MOTOR_PWM_RESOLUCION);
    ledcSetup(MOTOR_B_PWM, MOTOR_PWM_FREQ, MOTOR_PWM_RESOLUCION);
    EJEX_POSICION_ENCODER_SETPOINT=450;
}

void loop()
{

    if (millis() >= lastMillis + 500U)
    {
        lastMillis = millis();
        Serial.println("ACT: " + String(EJEX_POSICION_ENCODER_ACTUAL));
        Serial.println("SET: " + String(EJEX_POSICION_ENCODER_SETPOINT));
        Serial.println("RESTA: " + String(resta));
        //EJEX_POSICION_ENCODER_SETPOINT=EJEX_POSICION_ENCODER_SETPOINT+50;
        
    }
    if(EJEX_POSICION_ENCODER_SETPOINT>=3650)
    {
        EJEX_POSICION_ENCODER_SETPOINT=450;
    }

    if (Serial.available())
    {
        String input = Serial.readStringUntil('\n');
        EJEX_POSICION_ENCODER_SETPOINT = input.toInt();
    }
    go_to();
}
void go_to()
{
    EJEX_POSICION_ENCODER_ACTUAL = encoder.getCount();
    resta = EJEX_POSICION_ENCODER_SETPOINT - EJEX_POSICION_ENCODER_ACTUAL;
    //Serial.println("RESTA: " + String(resta));

    int b = 0;
    if (resta < DISTANCIA_5)
        b = 5;
    else
        b = 6;
    if (resta < DISTANCIA_4)
        b = 4;
    if (resta < DISTANCIA_3)
        b = 3;
    if (resta < DISTANCIA_2)
        b = 2;
    if (resta <= DISTANCIA_ERROR)
        b = 1;

    if (EJEX_POSICION_ENCODER_ACTUAL < EJEX_POSICION_ENCODER_SETPOINT)
    {
        switch (b)
        {
        case 1:
            ledcWrite(MOTOR_A_PWM, 0);
            ledcWrite(MOTOR_B_PWM, 0);
            break;
        case 2:
            ledcWrite(MOTOR_A_PWM, MOTOR_PWM_1);
            ledcWrite(MOTOR_B_PWM, 0);
            break;
        case 3:
            ledcWrite(MOTOR_A_PWM, MOTOR_PWM_2);
            ledcWrite(MOTOR_B_PWM, 0);
            break;
        case 4:
            ledcWrite(MOTOR_A_PWM, MOTOR_PWM_3);
            ledcWrite(MOTOR_B_PWM, 0);
            break;
        case 5:
            ledcWrite(MOTOR_A_PWM, MOTOR_PWM_4);
            ledcWrite(MOTOR_B_PWM, 0);
            break;
        case 6:
            ledcWrite(MOTOR_A_PWM, MOTOR_PWM_TOPEALTO);
            ledcWrite(MOTOR_B_PWM, 0);
            break;
        }
    }
    if (EJEX_POSICION_ENCODER_ACTUAL > EJEX_POSICION_ENCODER_SETPOINT)
    {
        switch (b)
        {
        case 1:
            ledcWrite(MOTOR_B_PWM, 0);
            ledcWrite(MOTOR_A_PWM, 0);
            break;
        case 2:
            ledcWrite(MOTOR_B_PWM, MOTOR_PWM_1);
            ledcWrite(MOTOR_A_PWM, 0);
            break;
        case 3:
            ledcWrite(MOTOR_B_PWM, MOTOR_PWM_2);
            ledcWrite(MOTOR_A_PWM, 0);
            break;
        case 4:
            ledcWrite(MOTOR_B_PWM, MOTOR_PWM_3);
            ledcWrite(MOTOR_A_PWM, 0);
            break;
        case 5:
            ledcWrite(MOTOR_B_PWM, MOTOR_PWM_4);
            ledcWrite(MOTOR_A_PWM, 0);
            break;
        case 6:
            ledcWrite(MOTOR_B_PWM, MOTOR_PWM_TOPEALTO);
            ledcWrite(MOTOR_A_PWM, 0);
            break;
        }
    }
}

void EJEX_PONERACERO()
{
    //ir a 0.
    digitalWrite(MOTOR_A, LOW);
    digitalWrite(MOTOR_B, HIGH);
    delay(3500);
    digitalWrite(MOTOR_A, LOW);
    digitalWrite(MOTOR_B, LOW);
    encoder.setCount(0);
    EJEX_POSICION_ENCODER_ACTUAL = 0;
}
