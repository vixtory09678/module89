#ifndef DRIVE_MOTOR_H
#define DRIVE_MOTOR_H
#include <mbed.h>

#define TO_PERIOD(hz) (float)(1.0/hz)
#define CONSTAIN(x,min,max) (x > max) ? max : (x < min) ? min : x

DigitalOut dirPin(A15);
PwmOut tuaPin(B3);

inline void driveMotor(int direction, float tua){
    dirPin.write(direction);
    tua = CONSTAIN(tua, 0, 100);
    tuaPin.write(tua/100.0);
}
inline void setupMotor(){
    dirPin = 0;
    tuaPin.period(TO_PERIOD(1000));
    tuaPin.write(0.0);
}

#endif