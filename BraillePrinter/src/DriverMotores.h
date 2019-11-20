#ifndef drivermotores_h
#define drivermotores_h

#define MOTOR_STEPS 32

#define PASOS_POR_MILIMETRO 14.6

BasicStepperDriver stepper(MOTOR_STEPS, pin_stepper_dir, pin_stepper_step);

class DriverMotores
{
public:
    uint8_t movimiento_y(uint8_t movimiento);
    void ejex_poner_a_cero();
    void movimiento_eje_x();
    void movimiento_x(float suma);

    double EJEX_POSICION_ENCODER_SETPOINT = 0;
    float EJEX_POSICION_ENCODER_ACTUAL;
    int POSICION_ESTABLECIDA = 0;
    uint16_t resta;

private:
    void moverHoja(float milimetros);
    bool leerADC_DIG(uint8_t pin);
    uint32_t lastMillis;
    void setPwmMotor_dir(uint8_t pwm, uint8_t direccion); //Direccion = 1, mueve izquierda.
    void setPwmMotor(uint8_t a, uint8_t b);
};

void solenoide_punto();
int32_t diferencia(int32_t a, int32_t b);

#endif