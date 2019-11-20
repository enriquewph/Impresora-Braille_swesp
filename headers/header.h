#ifndef HEADER_H
#define HEADER_H
#include <Arduino.h>
#include <stdint.h>

#include <ESP32Encoder.h>       //V0.2.1
#include <BasicStepperDriver.h> //V1.1.4

#include "pines.h"
#include "comandos_uart.h"
#include "BrailleCom.h"
#include "eje_x.h"
#include "eje_y.h"
#include "subrutinas_varias.h"


#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;


//Estructura para retorno de eventos de fallo/ok por parte de la rutina de impresion:

typedef struct eventArgs
{
    uint8_t result;
    uint8_t code;
} eventArgs_t;

eventArgs_t rutinaImpresion();

String eventMessage[] = 
{
    "No hay hoja en la impresora", //codigo 0
    "Error random 1" //codigo 1
};

#endif