#include "BasicStepperDriver.h"


BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP);

void MOVIMIENTO_EJEY()
{
    stepper.moverHoja(-20,9);
    delay(100);
    stepper.moverHoja(10,9);   
    delay(100);
    stepper.enable(); 
}