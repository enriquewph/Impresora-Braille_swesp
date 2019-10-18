

#include <ESP32Encoder.h>

#define ENCODER_A 32
#define ENCODER_B 33
#define MOTOR_A 27
#define MOTOR_B 26
#define MOTOR_A_PWM 1
#define MOTOR_B_PWM 2

#define MOTOR_PWM_FREQ 250
#define MOTOR_PWM_RESOLUCION 8

#define SOLENOIDE 13
#define MOTOR_PWM_TOPEBAJO 125
#define MOTOR_PWM_TOPEALTO 235

#define NUMERO_POSICIONES_X 70
#define NUMERO_POSICIONES_Y 70

#define DISTANCIA_ERROR 2
#define DISTANCIA_2 25
#define DISTANCIA_3 50
#define DISTANCIA_4 100
#define DISTANCIA_5 150
#define MOTOR_PWM_1 165
#define MOTOR_PWM_2 180
#define MOTOR_PWM_3 195
#define MOTOR_PWM_4 225

double EJEX_POSICION_ENCODER_SETPOINT = 0;
double EJEX_POSICION_ENCODER_ACTUAL;
uint16_t resta;