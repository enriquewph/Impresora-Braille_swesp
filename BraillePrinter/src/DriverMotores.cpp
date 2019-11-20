#include "../../headers/header.h"

DriverMotores ::movimiento_x(float suma)
{
    EJEX_POSICION_ENCODER_SETPOINT = EJEX_POSICION_ENCODER_SETPOINT + suma;
}

#define DISTANCIA_ERROR 2
#define DISTANCIA_2 25
#define DISTANCIA_3 50
#define DISTANCIA_4 100
#define DISTANCIA_5 150

int32_t posSet = 0;
uint8_t pwmVector[] = {0, 160, 175, 185, 195, 235}; //escalas del pwm...

DriverMotores ::movimiento_eje_x()
{
    POSICION_ESTABLECIDA = 0;

    while (POSICION_ESTABLECIDA == 0)
    {
        int32_t posAct = encoder.getCount(); //actualizar posicion actual...
        int32_t resta = diferencia(posSet, posAct); //obtener diferencia para calculo de "pid"
        bool direccion = posAct < posSet; //1 si se debe mover hacia la izquierda.
        uint8_t pwm = 0;

        if (resta <= DISTANCIA_ERROR)
        {
            pwm = pwmVector[0];
            POSICION_ESTABLECIDA = 1;
        }
        else if (resta < DISTANCIA_2)
            pwm = pwmVector[1];
        else if (resta < DISTANCIA_3)
            pwm = pwmVector[2];
        else if (resta < DISTANCIA_4)
            pwm = pwmVector[3];
        else if (resta < DISTANCIA_5)
            pwm = pwmVector[4];
        else
            pwm = pwmVector[5];
        
        setPwmMotor_dir(pwm, direccion); //actualizar salida del motor
    }
}

int32_t diferencia(int32_t a, int32_t b)
{
    if (a > b)
        return a - b;
    else if (a < b)
        return b - a;
    else
        return 0;
}

void solenoide_punto()
{
    digitalWrite(pin_solenoide, HIGH);
    delay(50);
    digitalWrite(pin_solenoide, LOW);
};

DriverMotores ::setPwmMotor_dir(uint8_t pwm, uint8_t direccion) //Direccion = 1, mueve izquierda.
{
    if (direccion)
        setPwmMotor(pwm, 0);
    else
        setPwmMotor(0, pwm);
}

DriverMotores ::setPwmMotor(uint8_t a, uint8_t b)
{
    ledcWrite(MOTOR_A_PWM, a);
    ledcWrite(MOTOR_B_PWM, b);
}

DriverMotores ::ejex_poner_a_cero()
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

DriverMotores ::movimiento_y(uint8_t movimiento);
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

DriverMotores ::moverHoja(float milimetros)
{
    long pasos = milimetros * PASOS_POR_MILIMETRO;
    stepper.move(pasos);
}

DriverMotores ::leerADC_DIG(uint8_t pin)
{
    uint16_t lectura = analogRead(pin);

    if (lectura <= 1800)
        return false;
    else if (lectura >= 2200)
        return true;
    else
        return false;
}