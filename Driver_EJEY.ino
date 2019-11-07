#include "BasicStepperDriver.h"

BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP);

void MOVIMIENTO_EJEY(int a)
{
    int b = 0;
    b = analogRead(SENSOR_HOJA);
    Serial.println(b);

    if (a == 1)
    {
        stepper.moverHoja(-10, 14.6);
        delay(100);
        stepper.moverHoja(10, 14.6);
        delay(100);
        while (b <= 2000)
        {
            b = analogRead(SENSOR_HOJA);
            Serial.println(b);
            stepper.moverHoja(-1, 14.6);
        }
        stepper.moverHoja(-19, 14.6);
    }
    if (a == 2)
    {
        stepper.moverHoja(-25, 14.6);
    }
    if (a == 3)
    {
        stepper.moverHoja(-2.5, 14.6);
    }
    if (a == 4)
    {
        stepper.moverHoja(-5, 14.6);
    }
    if (a == 5)
    {
        while (b >= 2000)
        {
            b = analogRead(SENSOR_HOJA);
            Serial.println(b);
            stepper.moverHoja(-1, 14.6);
        }
        stepper.moverHoja(-80, 14.6);
        delay(100);
    }
    stepper.enable();
}