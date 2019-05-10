#ifndef AS5600_H
#define AS5600_H

#include "mbed.h"

class AS5600 {
    public:
    AS5600(PinName sda, PinName scl,int hz);
    // float getAngleDegrees();
    int getAngleAbsolute();
    // int getAngleRelative();
    // float getAngleMinMax(float angleMax);

    int isMagnetPresent();
    
    // void init();
    // void setZero();

    private:
    char read(char address);
    I2C i2c;
    unsigned char addresse;
    // int relative_zero  ;
};
#endif


