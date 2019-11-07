#include <ESP32Encoder.h>
//movimientos para entrar la hoja 20,-83

#define SENSOR_HOJA 35
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

#define DISTANCIA_ERROR 2
#define DISTANCIA_2 25
#define DISTANCIA_3 50
#define DISTANCIA_4 100
#define DISTANCIA_5 150
#define MOTOR_PWM_1 160
#define MOTOR_PWM_2 175
#define MOTOR_PWM_3 185
#define MOTOR_PWM_4 195

#define MARGEN_IZQ 1
#define MARGEN_DER 2
#define ESPA_LETRA 3
#define ESPA_LyL 4

#define ENTRAR_HOJA 1
#define MARGEN_TOP_DOWN 2
#define ESPA_LINEA 3
#define ESPA_RENGLON 4
#define SACAR_HOJA 5

#define DISTANCIA_MARGEN_IZQ 3550
#define DISTANCIA_MARGEN_DER 407
#define DISTANCIA_MARGEN_ARRIB 25
#define DISTANCIA_MARGEN_ABAJO 25
#define DISTANCIA_LETRA 100
#define DISTANCIA_LyL 200

#define MOTOR_STEPS 32
#define RPM 500
#define MICROSTEPS 1
#define DIR 14
#define STEP 25
#define PASOS_POR_MM 9

#define NUMERO_POSICIONES_Y 6
#define NUMERO_POSICIONES_X 21
