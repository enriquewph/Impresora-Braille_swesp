#ifndef EJE_X_HEADER
#define EJE_X_HEADER

#define MOTOR_A_PWM 1
#define MOTOR_B_PWM 2
#define ESCALONES_PID 5
#define PWM_maximo 235
int32_t disVector[ESCALONES_PID] = {2, 25, 50, 100, 150}; //<= activa respectiva salida.
uint8_t pwmVector[ESCALONES_PID] = {0, 160, 175, 185, 195};
int32_t EJEX_SETPOINT = 0;
ESP32Encoder encoder;

#define MOV_X_ESPACIO_ENTRE_PUNTOS 0
#define MOV_X_ESPACIO_ENTRE_LETRAS 1
#define MOV_X_MARGEN 2

#define DIST_X_ESPACIO_ENTRE_PUNTOS 35
#define DIST_X_ESPACIO_ENTRE_LETRAS 49
#define DIST_X_MARGEN 355

#define DIST_X_MARGEN_IZQ_DESDE_BORDE 3457

#define DIST_X_MARGEN_IZQ_DESDE_BORDE_NL 3237

#define DIST_X_BORDE_IZQUIERDO 581

//Definicion de funciones
void EJEX_INIT();
void ejex_poner_a_cero();
void MOVIMIENTO_EJEX(uint8_t MOV_ID, bool direccion);
bool EJEX_AJUSTAR();
void EJEX_MOVERSE_A_COORDENADA(int32_t cord);
void EJEX_ESPERAR_A_MOVERSE();
void setPwmMotor_dir(uint8_t pwm, uint8_t direccion);
void setPwmMotor(uint8_t a, uint8_t b);


#endif