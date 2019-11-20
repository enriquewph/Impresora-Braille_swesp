#ifndef HEADER_H
#define HEADER_H
#include <Arduino.h>
#include <stdint.h>

#include <ESP32Encoder.h> //V0.2.1
#include <BasicStepperDriver.h> //V1.1.4

#include "pines.h"
#include "comandos_uart.h"
#include "BrailleCom.h"

#define MOTOR_A_PWM 1
#define MOTOR_B_PWM 2

#define MOTOR_STEPS 32

#define PASOS_POR_MILIMETRO 14.6

BasicStepperDriver stepper(MOTOR_STEPS, pin_stepper_dir, pin_stepper_step);

#define ESCALONES_PID 5
#define PWM_maximo 235

int32_t disVector[ESCALONES_PID] = {2, 25, 50, 100, 150}; //<= activa respectiva salida.
uint8_t pwmVector[ESCALONES_PID] = {0, 160, 175, 185, 195};

int32_t posSet = 0;

#endif