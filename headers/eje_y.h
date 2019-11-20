#ifndef EJE_Y_HEADER
#define EJE_Y_HEADER

#define STEPPER_STEPS 32
#define STEPPER_RPM 500
#define STEPPER_MICROSTEPS 1
#define PASOS_POR_MILIMETRO 14.6
BasicStepperDriver stepper(STEPPER_STEPS, pin_stepper_dir, pin_stepper_step);

#define MOV_Y_ENTRAR_HOJA 0
#define MOV_Y_MARGEN_SUPERIOR 1
#define MOV_Y_ESPACIO_LINEA 2
#define MOV_Y_ESPACIO_RENGLON 3
#define MOV_Y_SACAR_HOJA 4

//Definicion de funciones
void EJEY_INIT();
uint8_t MOVIMIENTO_EJEY(uint8_t MOV_ID);

#endif