#ifndef DRIVE_MOTOR_H
#define DRIVE_MOTOR_H
#include <mbed.h>
// #include "joint_config.h"

#define TO_PERIOD(hz) (float)(1.0/hz)
#define CONSTAIN(x,min,max) (x > max) ? max : (x < min) ? min : x

DigitalOut dirPin(A15);
PwmOut tauPin(B3);

inline void driveMotor(int direction, float tau){
    dirPin.write(direction);
    if(tau != 0)
        tau = CONSTAIN(tau, 5, 60);
    else
        tau = 0.0;
    tauPin.write(tau/100.0);
}
inline void setupMotor(){
    dirPin = 0;
    tauPin.period(TO_PERIOD(500));
    tauPin.write(0.0);
}

#endif