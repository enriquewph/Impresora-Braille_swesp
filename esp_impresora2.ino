
#include <ESP32Encoder.h>

#include <PID_v1.h>

#include <math.h> // round, floor, ceil, trunc 

#define ENCODER_A 33
#define ENCODER_B 32
#define MOTOR_A 27
#define MOTOR_B 26
#define MOTOR_A_PWM 1
#define MOTOR_B_PWM 2

#define MOTOR_PWM_FREQ 250
#define MOTOR_PWM_RESOLUCION 8

#define solenoide 13

ESP32Encoder encoder;

double EJEX_POSICION_ENCODER_SETPOINT = 0;
double EJEX_POSICION_ENCODER_ACTUAL;
double EJEX_PID_OUTPUT; //pwm en una direccion u otra (-255 a 0 a +255)
/*
Parameters and what they do (sort of)
P_Param:  the bigger the number the harder the controller pushes.
I_Param:  the SMALLER the number (except for 0, which turns it off,)  the more quickly the controller reacts to load changes, but the greater the risk of oscillations.
D_Param: the bigger the number  the more the controllr dampens oscillations (to the point where performance can be hindered)
*/
double CONS_KP = 0.3;
double CONS_KI = 1;
double CONS_KD = 0;


uint16_t input_serial = 0;

#define MOTOR_PWM_TOPEBAJO 125
#define MOTOR_PWM_TOPEALTO 235

PID myPID(&EJEX_POSICION_ENCODER_ACTUAL, &EJEX_PID_OUTPUT, &EJEX_POSICION_ENCODER_SETPOINT, CONS_KP, CONS_KI, CONS_KD, REVERSE);

uint32_t lastMillis;

void setup()
{
    // put your setup code here, to run once:
    pinMode(2, OUTPUT);
    pinMode(MOTOR_A, OUTPUT);
    pinMode(MOTOR_B, OUTPUT);
    pinMode(solenoide, OUTPUT);

    // Attache pins for use as encoder pins
    encoder.attachHalfQuad(ENCODER_A, ENCODER_B);
    Serial.begin(115200);
    EJEX_POSICION_ENCODER_SETPOINT = 0;
    EJEX_PONERACERO();
    EJEX_PID_INICIAR();

    lastMillis = millis();
}

void loop()
{

      
    if (millis() >= lastMillis + 500u)
    {
        Serial.println("ACT: " + String(EJEX_POSICION_ENCODER_ACTUAL));
        Serial.println("SET: " + String(EJEX_POSICION_ENCODER_SETPOINT));
        Serial.println("OUT: " + String(EJEX_PID_OUTPUT));
        lastMillis = millis();
        if (EJEX_POSICION_ENCODER_ACTUAL<4000)
        {
            EJEX_POSICION_ENCODER_SETPOINT = EJEX_POSICION_ENCODER_SETPOINT+20;
        }
        else
        {
            EJEX_POSICION_ENCODER_SETPOINT = 0;
        }
        
       
    }
   
    digitalWrite(solenoide,LOW);

    if (Serial.available())
    {
        String input = Serial.readStringUntil('\n');
        EJEX_POSICION_ENCODER_SETPOINT = input.toInt();
    }
    
    
    EJEX_PID_COMPUTAR();


}

void EJEX_PID_INICIAR()
{
    ledcAttachPin(MOTOR_A, MOTOR_A_PWM);
    ledcAttachPin(MOTOR_B, MOTOR_B_PWM);
    ledcSetup(MOTOR_A_PWM, MOTOR_PWM_FREQ, MOTOR_PWM_RESOLUCION);
    ledcSetup(MOTOR_B_PWM, MOTOR_PWM_FREQ, MOTOR_PWM_RESOLUCION);

    myPID.SetMode(AUTOMATIC);
    myPID.SetOutputLimits(0, 100);
}

void EJEX_PID_COMPUTAR()
{
    myPID.Compute();
    EJEX_POSICION_ENCODER_ACTUAL = encoder.getCount();
    //hacer algo con la salida

    /*
    4300--------- 2000----------0
    Si la coordenada X actual es mayor al setpoint de 2000 (Está a la izquierda de este)
    Hay que mover el carrete hacia la derecha, con velocidad proporcional a la diferencia de distancia.

    La salida del PID se deberá mantener en 50, cuando el carrete este en su lugar (XACT = XSET)
    Si se pasa a la izquierda, la salida del pid, sobrepasa 50.
    Caso contrario, pasa or debajo de 50.

    */

    //ledcWrite(MOTOR_A_PWM, input.toInt());

    //Sacarle el decimal a la salida:

    int sindecimal = EJEX_PID_OUTPUT;
    EJEX_PID_OUTPUT = sindecimal;

    if (EJEX_PID_OUTPUT > 50) //Se paso para la izquierda
    {
        ledcWrite(MOTOR_B_PWM, myMap(EJEX_PID_OUTPUT, 50, 100, MOTOR_PWM_TOPEBAJO, MOTOR_PWM_TOPEALTO));
        ledcWrite(MOTOR_A_PWM, 0);
    }

    if (EJEX_PID_OUTPUT < 50) //Se paso para la derecha
    {
        ledcWrite(MOTOR_A_PWM, myMap(EJEX_PID_OUTPUT, 50, 0, MOTOR_PWM_TOPEBAJO, MOTOR_PWM_TOPEALTO));
        ledcWrite(MOTOR_B_PWM, 0);
    }

    if (EJEX_PID_OUTPUT == 50) //No hacer nada.
    {
        ledcWrite(MOTOR_B_PWM, 0);
        ledcWrite(MOTOR_B_PWM, 0);
    }
}

int myMap(double x, double in_min, double in_max, double out_min, double out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void EJEX_PONERACERO()
{
    //ir a 0.

    digitalWrite(MOTOR_A, LOW);
    digitalWrite(MOTOR_B, HIGH);
    delay(3500);
    digitalWrite(MOTOR_A, LOW);
    digitalWrite(MOTOR_B, LOW);
    encoder.setCount(0);
    EJEX_POSICION_ENCODER_ACTUAL = 0;
}
