#ifndef DRIVE_MOTOR_H
#define DRIVE_MOTOR_H
#include <mbed.h>
// #include "joint_config.h"

#define TO_PERIOD(hz) (float)(1.0/hz)
#define CONSTAIN(x,min,max) (x > max) ? max : (x < min) ? min : x

DigitalOut dirPin(A15);
PwmOut tuaPin(B3);

inline void driveMotor(int direction, float tua){
    dirPin.write(direction);
    if(tua != 0)
        tua = CONSTAIN(tua, 5, 60);
    else
        tua = 0.0;
    tuaPin.write(tua/100.0);
}
inline void setupMotor(){
    dirPin = 0;
    tuaPin.period(TO_PERIOD(500));
    tuaPin.write(0.0);
}

#endif