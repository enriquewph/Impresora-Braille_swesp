void ejex_poner_a_cero()
{
    setPwmMotor(0, 255);
    delay(50); //prevenir deteccion de la corriente de arranque del motor
    while (analogRead(pin_motor_current) < 2150)
    delay(50); //asegurarse que llegó a 0.
    setPwmMotor(0, 0);
    encoder.setCount(0);
}

bool EJEX_AJUSTAR() //retorna 1 si esta en el setpoint.
{
    bool retorno = false;
    int32_t posAct = encoder.getCount(); //actualizar posicion actual...
    bool direccion = posAct < posSet;    //1 si se debe mover hacia la izquierda.
    int32_t diff = diferencia(posSet, posAct);
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

    setPwmMotor_dir(pwm, posAct < posSet); //actualizar salida del motor dir =1 si se debe mover hacia la izquierda.

    return retorno;
}

void EJEX_MOVERSE_A_COORDENADA(int32_t cord)
{
    posSet = cord;
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