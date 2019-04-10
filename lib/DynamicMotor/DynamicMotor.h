#ifndef DYNAMIC_MOTOR_H
#define DYNAMIC_MOTOR_H

#include "mbed.h"
#include "AS5600.h"

#define PI 3.141592653589793

#define TO_PERIOD(hz) 1.0/(hz)
#define TO_HZ(period) 1.0/(period)

#define KP 0.0
#define KI 0.0
#define KD 0.0


class DynamicMotor
{
private:
    /* data */
    AS5600 _encoder;
    DigitalOut _dirMotor;
    PwmOut _pwm;
    Ticker _ticker;
    long _qr;
    long _dqr;

    Serial *_ser;

    float tua;
    float T_duration;
    double lastError;
    void calPID();
    int _fq;
    double convertEncoderToRadiant(int encoder);
public:
    // Constructor for initialize class
    DynamicMotor(PinName _pDMotor, PinName _pPWM, PinName _pI2C_SCL, PinName _pI2C_SDA);
    DynamicMotor(PinName _pDMotor, PinName _pPWM);

    void setDebug(Serial *ser);

    void handle();

    // driveMotor is a function for control motor
    // @param1 _direction : control direction in value 1 or 0
    // @param2 _duty : percentage of duty cycle
    void driveMotor(uint8_t direction, float _duty);

    // ************************************************
    // ******************* CONFIG *********************
    // ************************************************
    // setMotorPin is a function for set up pin of motor driver
    // @param1 _pDMotor : direction pin to control motor driver
    // @param2 _pPWM : PWM pin to control motor driver
    void setMotorPin(PinName _pDMotor, PinName _pPWM);

    // setConfiguration is a function for set configuration of joint for calculate in calPID() func
    // @param1 _q : q is configuration of joint
    void setConfiguration(float _coeff[4][5]);

    // setI2CEncoderPin is a function for set up pin of AS5600 encoder sensor
    // @param1 _pI2C_SCL : SCL pin used for AS5600 encoder sensor
    // @param2 _pI2C_SDA : SDA pin used for AS5600 encoder sensor
    void setI2CEncoderPin(PinName _pI2C_SCL, PinName _pI2C_SDA);

    // setCalculateFreq is a function for setup Frequency of calculate PID
    // @param1 hz : set frequency ticker for calculate PID by period parameter input
    void setCalculateFreq(float hz);

    // setDriveMotorFreq is a function for setup Frequency for drive motor
    // @param1 hz : set frequency for control motor
    void setDriveMotorFreq(float _hz);
};
#endif