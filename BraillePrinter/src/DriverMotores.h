#ifndef drivermotores_h
#define drivermotores_h

#define MOTOR_STEPS 32

BasicStepperDriver stepper(MOTOR_STEPS, pin_stepper_dir, pin_stepper_step);

#endif