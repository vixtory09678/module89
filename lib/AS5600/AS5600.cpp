// AS5600 Verson 1.3
// 20/03/2015  GR : fonction limitant la dynamique autour de zero à -max , +max
#include "AS5600.h"
//#include "mbed.h"



AS5600::AS5600(PinName sda, PinName scl,int hz) : i2c(sda,scl) {
    addresse=0x36;
    i2c.frequency(hz);
}

int AS5600::isMagnetPresent() {
    char cmd=0x0B,data=0,value=0;
    data=this->read(cmd);
    value=(char) (data & 0x20) >> 5 ;

    return value;
}


int AS5600::getAngleAbsolute() {
    char cmd1=0x0E,cmd2=0x0F;
    int data=0;

    data=this->read(cmd1) << 8;
    data=data+this->read(cmd2);

    return data;
}

// int AS5600::getAngleRelative() {
//     return ((this->getAngleAbsolute() + (2047 - relative_zero)) % 4096) - 2047;
// }


// float AS5600::getAngleDegrees() {
//     return ((float)this->getAngleRelative() * 180) / 2048 ;
// }

// void AS5600::setZero() {
//     relative_zero = 0;
//     relative_zero = this->getAngleAbsolute();
// }


char AS5600::read(char address) {
    char retval;
    i2c.write(addresse * 2, &address, 1);
    i2c.read(addresse * 2, &retval, 1);
    return retval;
}

// void AS5600::init() {
//     for (int i = 0; i < 10; i++)
//         this->setZero();
// }

// float AS5600::getAngleMinMax(float angleMax) {
//     static unsigned char etat=0;           // etat de l'automate
//     static int anglePrec=0;                // angle precedent
//     float angle=0;                         // angle courant
//     float angleX=0;                        //angle en sortie borne
//     //
//     angle=this->getAngleDegrees();         // lecture de l'angle courant
//     switch(etat) {
//         case 0 :    // angle compris entre min et max
//             angleX = angle;
//             if(angle > angleMax)  etat = 2;
//             if(angle < -angleMax) etat = 1;
//             break;
//         case 1 :    // angle inferieur a -max
//             angleX = -angleMax;
//             if((anglePrec <= -angleMax) && (angle >= -angleMax) && (angle < 0)) etat = 0;
//             break;
//         case 2 :
//             angleX = angleMax;
//             if((anglePrec >=  angleMax) && (angle <= angleMax) && (angle > 0))etat = 0;
//             break;
//         default :
//             break;
//     }
//     anglePrec=angle;
//     return angleX;
// }