#include "DynamicMotor.h"

DynamicMotor::DynamicMotor(PinName _pDMotor, PinName _pPWM, PinName _pI2C_SCL, PinName _pI2C_SDA)
    : _dirMotor(_pDMotor), _pwm(_pPWM), _encoder(_pI2C_SDA,_pI2C_SCL) {
        _encoder.init();
        lastError = 0;
        tua = 0;
        // _ser = NULL;
        // setCalculateFreq(1000);
        // setDriveMotorFreq(1000);
}

DynamicMotor::DynamicMotor(PinName _pDMotor, PinName _pPWM):_dirMotor(_pDMotor),_pwm(_pPWM),_encoder(I2C_SDA,I2C_SCL){
    _encoder.init();
    lastError = 0;
    tua = 0;
    // _ser = NULL;
    // setCalculateFreq(1000);
    // setDriveMotorFreq(1000);
}

void DynamicMotor::setDebug(Serial *ser){
    _ser = ser;
}

void DynamicMotor::handle(){
    if(_ser!=NULL){
        _ser->printf("encoder is %d\n",_encoder.getAngleAbsolute());
    }
}

void DynamicMotor::driveMotor(uint8_t direction, float _duty){
    _dirMotor.write(direction);
    _pwm.write(_duty/100.0);
}

double DynamicMotor::convertEncoderToRadiant(int encoder){
    return ((float)encoder / 4093.0) * (PI*2);
}

void DynamicMotor::calPID(){
    double error = _qr - convertEncoderToRadiant(_encoder.getAngleAbsolute());
    double d_error = (error - lastError) / TO_PERIOD(_fq);
    tua = KP * (error) + KD * (_dqr - d_error);
    lastError = error;
}


// setup function
void DynamicMotor::setMotorPin(PinName _pDMotor, PinName _pPWM){
    _dirMotor = DigitalOut(_pDMotor);
    _pwm = PwmOut(_pPWM);
}

void DynamicMotor::setI2CEncoderPin(PinName _pI2C_SCL, PinName _pI2C_SDA){
    _encoder = AS5600(_pI2C_SCL,_pI2C_SDA);
}

void DynamicMotor::setConfiguration(float _coeff[4][5]){
}

void DynamicMotor::setCalculateFreq(float hz){
    _fq = hz;
    _ticker.detach();
    _ticker.attach(callback(this,&DynamicMotor::calPID),TO_PERIOD(hz));
}

void DynamicMotor::setDriveMotorFreq(float hz){
    _pwm.period_ms(TO_PERIOD(hz) * 1000);
}