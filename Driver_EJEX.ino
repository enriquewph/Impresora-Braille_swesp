#include <ESP32Encoder.h>
#include "header.h"

double EJEX_POSICION_ENCODER_SETPOINT = 0;
double EJEX_POSICION_ENCODER_ACTUAL;
int POSICION_ESTABLECIDA = 0;
uint16_t resta;

ESP32Encoder encoder;

void MOVER(int suma)
{
    EJEX_POSICION_ENCODER_SETPOINT = EJEX_POSICION_ENCODER_SETPOINT + suma;
}
void MOVIMIENTO_EJEX()
{

    POSICION_ESTABLECIDA = 0;

    while (POSICION_ESTABLECIDA == 0)
    {
        EJEX_POSICION_ENCODER_ACTUAL = encoder.getCount();
        resta = EJEX_POSICION_ENCODER_SETPOINT - EJEX_POSICION_ENCODER_ACTUAL;
        int b = 0;
       

        if (resta < DISTANCIA_5)
        {
            b = 5;
        }
        else
        {
            b = 6;
        }
        if (resta < DISTANCIA_4)
        {
            b = 4;
        }
        if (resta < DISTANCIA_3)
        {
            b = 3;
        }
        if (resta < DISTANCIA_2)
        {
            b = 2;
        }
        if (resta <= DISTANCIA_ERROR)
        {
            b = 1;
            POSICION_ESTABLECIDA = 1;
        }

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