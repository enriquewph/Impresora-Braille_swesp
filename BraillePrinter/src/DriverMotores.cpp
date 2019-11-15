#include "../../headers/header.h"


DriverMotores :: movimiento_x(float suma)
{
    EJEX_POSICION_ENCODER_SETPOINT = EJEX_POSICION_ENCODER_SETPOINT + suma;
}

DriverMotores :: movimiento_eje_x()
{

    POSICION_ESTABLECIDA = 0;

    while (POSICION_ESTABLECIDA == 0)
    {
        EJEX_POSICION_ENCODER_ACTUAL = encoder.getCount();
        resta = EJEX_POSICION_ENCODER_SETPOINT - EJEX_POSICION_ENCODER_ACTUAL; //aca esta el error.
        int b = 0;
        
        if (resta <= DISTANCIA_ERROR)
        {
            b = 1;
            POSICION_ESTABLECIDA = 1;
        }
        else if (resta < DISTANCIA_2)
            b = 2;
        else if (resta < DISTANCIA_3)
            b = 3;
        else if (resta < DISTANCIA_4)
            b = 4;
        else if (resta < DISTANCIA_5)
            b = 5;
        else
            b = 6;
        
        if (EJEX_POSICION_ENCODER_ACTUAL < EJEX_POSICION_ENCODER_SETPOINT)
        {
            switch (b)
            {
            case 1:
                setPwmMotor(0, 0);
                break;
            case 2:
                setPwmMotor(MOTOR_PWM_1, 0);
                break;
            case 3:
                setPwmMotor(MOTOR_PWM_2, 0);
                break;
            case 4:
                setPwmMotor(MOTOR_PWM_3, 0);
                break;
            case 5:
                setPwmMotor(MOTOR_PWM_4, 0);
                break;
            case 6:
                setPwmMotor(MOTOR_PWM_TOPEALTO, 0);
                break;
            }
        }
        else
        {
            switch (b)
            {
            case 1:
                setPwmMotor(0, 0);
                break;
            case 2:
                setPwmMotor(0, MOTOR_PWM_1);
                break;
            case 3:
                setPwmMotor(0, MOTOR_PWM_2);
                break;
            case 4:
                setPwmMotor(0, MOTOR_PWM_3);
                break;
            case 5:
                setPwmMotor(0, MOTOR_PWM_4);
                break;
            case 6:
                setPwmMotor(0, MOTOR_PWM_TOPEALTO);
                break;
            }
        }
    }
}

DriverMotores :: setPwmMotor(uint8_t a, uint8_t b)
{
    ledcWrite(MOTOR_A_PWM, a);
    ledcWrite(MOTOR_B_PWM, b);
}

DriverMotores :: ejex_poner_a_cero()
{
    //ir a 0.
    Serial.println("Poniendo a 0");
    digitalWrite(MOTOR_A, LOW);
    digitalWrite(MOTOR_B, HIGH);
    delay(3500);
    digitalWrite(MOTOR_A, LOW);
    digitalWrite(MOTOR_B, LOW);
    encoder.setCount(0);
    EJEX_POSICION_ENCODER_ACTUAL = 0;
}

DriverMotores :: movimiento_y(uint8_t movimiento);
{
    int c = 0;
    int d = 0;

    switch (movimiento)
    {
    case 1:
        moverHoja(-10);
        delay(100);
        moverHoja(10);
        delay(100);
        lastMillis = millis();

        while (leerADC_DIG(pin_sensor_hoja) + c == 0)
        {
            if (millis() >= lastMillis + 4500U) //timeout
            {
                stepper.enable();
                c = 1;
                return (1);
            }
            moverHoja(-1);
        }
        moverHoja(-19);
        return (0);
        break;
    case 2:
        moverHoja(-41);
        break;
    case 3:
        moverHoja(-2.5);
        break;
    case 4:
        moverHoja(-5);
        break;
    case 5:
        while (leerADC_DIG(pin_sensor_hoja))
        {
            moverHoja(-1);
        }
        moverHoja(-80);
        delay(100);
        break;
    }
    stepper.enable();
}


DriverMotores :: moverHoja(float milimetros)
{
    long pasos = milimetros * PASOS_POR_MILIMETRO;
    stepper.move(pasos);
}

DriverMotores :: leerADC_DIG(uint8_t pin)
{
    uint16_t lectura = analogRead(pin);
    
    if (lectura <= 1800)
        return false;
    else if (lectura >= 2200)
        return true;
    else
        return false;
}