#include "headers/header.h"

void EJEX_INIT()
{
    encoder.attachHalfQuad(pin_encoder_a, pin_encoder_b);
    ledcAttachPin(pin_motor_a, MOTOR_A_PWM);
    ledcAttachPin(pin_motor_b, MOTOR_B_PWM);
    ledcSetup(MOTOR_A_PWM, 250, 8);
    ledcSetup(MOTOR_B_PWM, 250, 8);
}

void ejex_poner_a_cero()
{
    setPwmMotor(0, 255);
    delay(50); //prevenir deteccion de la corriente de arranque del motor
    while (analogRead(pin_motor_current) < 2150)
        delay(50); //asegurarse que llegó a 0.
    setPwmMotor(0, 0);
    encoder.setCount(0);
}

void MOVIMIENTO_EJEX(uint8_t MOV_ID, bool direccion)
{
    int32_t setPointNuevo = EJEX_SETPOINT;
    int32_t distanciaAMover = 0;

    switch (MOV_ID)
    {
    case MOV_X_ESPACIO_ENTRE_PUNTOS:
        distanciaAMover = DIST_X_ESPACIO_ENTRE_PUNTOS;
        break;
    case MOV_X_ESPACIO_ENTRE_LETRAS:
        distanciaAMover = DIST_X_ESPACIO_ENTRE_LETRAS;
        break;
    case MOV_X_MARGEN:
        distanciaAMover = DIST_X_MARGEN;
        break;
    }

    setPointNuevo += (distanciaAMover * direccion) - (distanciaAMover * (1 - direccion));
    EJEX_MOVERSE_A_COORDENADA(setPointNuevo);
}

bool EJEX_AJUSTAR() //retorna 1 si esta en el setpoint.
{
    bool retorno = false;
    int32_t posAct = encoder.getCount();     //actualizar posicion actual...
    bool direccion = posAct < EJEX_SETPOINT; //1 si se debe mover hacia la izquierda.
    int32_t diff = diferencia(EJEX_SETPOINT, posAct);
    uint8_t pwm = 0;
    uint8_t index = ESCALONES_PID;
    uint8_t lastIndex = ESCALONES_PID;

    while (index--)
        if (diff <= disVector[index])
            lastIndex = index;

    if (lastIndex == 0)
        retorno = true; //ya está en el setpoint...

    if (lastIndex != ESCALONES_PID)
        pwm = pwmVector[lastIndex];
    else //sino aplicar maximo pwm.
        pwm = PWM_maximo;

    setPwmMotor_dir(pwm, posAct < EJEX_SETPOINT); //actualizar salida del motor dir =1 si se debe mover hacia la izquierda.

    return retorno;
}

void EJEX_MOVERSE_A_COORDENADA(int32_t cord)
{
    EJEX_SETPOINT = cord;
    EJEX_ESPERAR_A_MOVERSE();
}

void EJEX_ESPERAR_A_MOVERSE()
{
    while (!EJEX_AJUSTAR())
        ;
    return;
}

void setPwmMotor_dir(uint8_t pwm, uint8_t direccion) //Direccion = 1, mueve izquierda.
{
    if (direccion)
        setPwmMotor(pwm, 0);
    else
        setPwmMotor(0, pwm);
}

void setPwmMotor(uint8_t a, uint8_t b)
{
    ledcWrite(MOTOR_A_PWM, a);
    ledcWrite(MOTOR_B_PWM, b);
}