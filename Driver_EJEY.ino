#include "BasicStepperDriver.h"
uint32_t lastMillis;

BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP);

int MOVIMIENTO_EJEY(int a)
{
    int b = 0;
    int c = 0;
    int d = 0;
    b = analogRead(SENSOR_HOJA);

    if (a == 1)
    {
        stepper.moverHoja(-10, 14.6);
        delay(100);
        stepper.moverHoja(10, 14.6);
        delay(100);
        lastMillis = millis();
        while (b <= 2000 && c == 0)
        {
            if (millis() >= lastMillis + 4500U)
            {
                //lastMillis = millis();
                Serial.println("NO HAY HOJA");
                stepper.enable();
                c = 1;
                return(1);
            }
            b = analogRead(SENSOR_HOJA);
            stepper.moverHoja(-1, 14.6);
        }
        stepper.moverHoja(-19, 14.6);
        return(0);
        
    }
    if (a == 2)
    {
        stepper.moverHoja(-41, 14.6);
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
            stepper.moverHoja(-1, 14.6);
        }
        stepper.moverHoja(-80, 14.6);
        delay(100);
    }
    stepper.enable();
}