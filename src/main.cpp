#include <mbed.h>
#include "joint_config.h"
#include "protocol_config.h"
#include "driveMotor.h"
#include <AS5600.h>

AS5600 encoder(SDA_PIN,SCL_PIN);//SDA SCL
Timer timeSpan;
// ------------------- CONFIG --------------------------//
// #define DEBUG
#ifdef DEBUG
Serial pc(A9,A10);
#endif
// ----------------- END CONFIG ------------------------//

int  getAngle(){
  return ((encoder.getAngleAbsolute() + (2047 - SET_ZERO)) % 4096) - 2047;
}

float toEncoder(float degree){
  if (degree < 0.0) degree = CONSTAIN(degree,-180,0);
  else degree = CONSTAIN(degree,0,180);
  return (degree / 360.0) * 4095.0;
}

int indexCalculate = 0;

#define T_PERIOD 0.01
bool isReadyCalculate = false;
inline void compute(){
  switch (instruct)
  {
  case CONFIGURATION:
    configFb.error = toEncoder(config._coeff) - getAngle();
    configFb.tua = configFb.Kp * (configFb.error)
                    + configFb.Kd * ((configFb.error - configFb.lastError) / T_PERIOD);
    configFb.lastError = configFb.error;
    break;
  case TRAJECTORY:
    trajectFb.time += T_PERIOD;

    float t = trajectFb.time;
    float tp2 = pow(trajectFb.time,2.0);
    float tp3 = pow(trajectFb.time,3.0);

    float q_ref = slave_joint1[indexCalculate]._coeff +                          // c0
                  slave_joint1[indexCalculate + 1]._coeff * t+                   // c1 * t
                  slave_joint1[indexCalculate + 2]._coeff * tp2+                 // c2 * t^2
                  slave_joint1[indexCalculate + 3]._coeff * tp3;                 // c3 * t^3

    float q_dot_ref = slave_joint1[indexCalculate + 1]._coeff +                   // c1
                    (2.0 * slave_joint1[indexCalculate + 2]._coeff * t)+          // 2 * c2 * t
                    (3.0 * slave_joint1[indexCalculate + 3]._coeff * tp2);        // 3 * c3 * t^2

    if (trajectFb.time >= slave_joint1[indexCalculate + 4]._coeff){
      if (indexCalculate < 6)
        indexCalculate += 1;
      else
        indexCalculate = 5;
    } else {
      configFb.tua = configFb.Kp * (configFb.error)
                    + configFb.Kd * ((q_dot_ref - configFb.error - configFb.lastError) / T_PERIOD);
    }
    break;
  }
}

void state(){
  switch (instruct)
  {
  case CONFIGURATION:

      if (configFb.error > 2.0){
        driveMotor(1, fabs(configFb.tua));
      }else if(configFb.error < -1.0){
        driveMotor(0, fabs(configFb.tua));
      }else{
        driveMotor(1, 0);
        isReadyCalculate = false;
      }
      break;
    
  case TRAJECTORY:
    break;
  }
}

inline void onDataReceive(){
  if (isReadDyProtocol){
    switch (instruct)
    {
      case CONFIGURATION:
        /* code */
        configFb.Kp = 2.0;
        configFb.Ki = 0.0;
        configFb.Kd = 0.0;
        configFb.error = 0.0;
        configFb.lastError = 0.0;
        configFb.tua = 0.0;

        #ifdef DEBUG
        pc.printf("con %f\n",slave_joint1[0]._coeff);
        #endif

        break;
      case TRAJECTORY:
        /* code */
        trajectFb.Kp = 0.0;
        trajectFb.Ki = 0.0;
        trajectFb.Kd = 0.0;
        trajectFb.error = 0.0;
        trajectFb.lastError = 0.0;
        trajectFb.tua = 0.0;

        #ifdef DEBUG
        pc.printf("tra %f\n",slave_joint1[3]._coeff);
        #endif

        break;

      default:
        break;
    }
    isReadyCalculate = true;
    timeSpan.reset();
    isReadDyProtocol = false;
  }
}


inline void setup(){
  timeSpan.start();
  setupMotor();
  led = 0;
  device.format(8,1);
  encoder.init();
}

int main() {
  setup();
  while(1) {
    // put your main code here, to run repeatedly:
    checkReceiveData();
    onDataReceive();

    if (isReadyCalculate){
      if ( timeSpan.read_ms() > 100){
        // compute();
        timeSpan.reset();
      }
      // state();
    }

    // pc.printf("%f & %d\n",(float)getAngle()/4095.0 * 360.0 , encoder.getAngleAbsolute());
  }
}