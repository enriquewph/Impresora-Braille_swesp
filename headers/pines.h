#ifndef pines_h
#define pines_h

#define pin_sd_DI 23
#define pin_sd_DO 19
#define pin_sd_SCLK 18
#define pin_sd_CS 5

#define pin_i2c_SDA 21
#define pin_i2c_SCL 22

#define pin_uart_RX 3
#define pin_uart_TX 1

#define pin_button_a 0
#define pin_button_b 4
#define pin_led_a 2
#define pin_led_b 15

#define pin_solenoide 13
#define pin_cooler 12
#define pin_sensor_hoja 35
#define pin_motor_current 34

#define pin_stepper_dir 14
#define pin_stepper_step 25

#define pin_motor_a 27
#define pin_motor_b 26

#define pin_encoder_a 32
#define pin_encoder_b 33

void initPins()
{
    pinMode(pin_button_a, INPUT);
    pinMode(pin_button_b, INPUT);
    pinMode(pin_led_a, OUTPUT);
    pinMode(pin_led_b, OUTPUT);

    pinMode(pin_solenoide, OUTPUT);
    pinMode(pin_cooler, OUTPUT);
    pinMode(pin_sensor_hoja, INPUT);
    pinMode(pin_motor_current, INPUT);

    pinMode(pin_stepper_dir, OUTPUT);
    pinMode(pin_stepper_step, OUTPUT);

    pinMode(pin_motor_a, OUTPUT);
    pinMode(pin_motor_b, OUTPUT);

    pinMode(pin_encoder_a, INPUT);
    pinMode(pin_encoder_b, INPUT);
}

#endif