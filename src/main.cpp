#include <mbed.h>
#include "joint_config.h"
#include "protocol_config.h"

#include "driveMotor.h"
#include <AS5600.h>
AS5600 encoder(SDA_PIN,SCL_PIN);//SDA SCL

int sensor = 0;
int  getAngle(){
  return ((encoder.getAngleAbsolute() + (2047 - SET_ZERO)) % 4096) - 2047;
}

Timer timeSpan;
// #define DEBUG

#ifdef DEBUG
Serial pc(A9,A10);
#endif
// #define DEBUG_ENCODER
// ------------------- CONFIG --------------------------//
#ifdef DEBUG_ENCODER
Serial pc(A9,A10);
#endif
// ----------------- END CONFIG ------------------------//
float toEncoder(float degree){
  if (degree < 0.0) degree = CONSTAIN(degree,-180,0);
  else degree = CONSTAIN(degree,0,180);
  return (degree / 360.0) * 4095.0;
}

int indexCalculate = 0;
bool isReadyCalculate = false;

#define T_PERIOD 0.01

inline void compute(){

  // if(!encoder.isMagnetPresent()) {
  //   while(true);
  // }

  switch (instruct)
  {
  case CONFIGURATION:
    sensor = getAngle() * INVERSE;
    configFb.error = toEncoder(config._coeff) - sensor;
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

    trajectFb.error = toEncoder(q_ref) - (getAngle() * INVERSE);

    if (trajectFb.time >= slave_joint1[indexCalculate + 4]._coeff){
      if (indexCalculate < 20){
        trajectFb.time = 0.0;
        indexCalculate += 5;
      }
    } else {
      trajectFb.tua = trajectFb.Kp * (trajectFb.error)
                    + trajectFb.Kd * ((q_dot_ref - trajectFb.error - trajectFb.lastError) / T_PERIOD);
      trajectFb.lastError = trajectFb.error;
    }
    break;
  }
}


void state(){

  switch (instruct)
  {
  case CONFIGURATION:
      if (configFb.error > 2.0){
        driveMotor(DIR_JOINT, fabs(configFb.tua));
      }else if(configFb.error < -2.0){
        driveMotor((!DIR_JOINT), fabs(configFb.tua));
      }else{
        driveMotor(0, 0);
        isReadyCalculate = false;
      }
      break;
  
  case TRAJECTORY:

      if (trajectFb.error > 2.0) {
        driveMotor(DIR_JOINT, fabs(trajectFb.tua));
      }else if(trajectFb.error < -2.0){
        driveMotor((!DIR_JOINT), fabs(trajectFb.tua));
      }else{
        driveMotor(1,0);
        isReadyCalculate = false;
      }
    break;
  default:
    driveMotor(0,0);
    isReadyCalculate = false;
  }
}

inline void onDataReceive(){
  if (isReadDyProtocol){
    switch (instruct)
    {
      case CONFIGURATION:
        /* code */
        configFb.error = 0.0;
        configFb.lastError = 0.0;
        configFb.tua = 0.0;

        #ifdef DEBUG
        pc.printf("con %f\n",config._coeff);
        #endif

        break;
      case TRAJECTORY:
        /* code */
        trajectFb.error = 0.0;
        trajectFb.lastError = 0.0;
        trajectFb.tua = 0.0;
        trajectFb.time = 0.0;

        #ifdef DEBUG
        pc.printf("tra %f\n",slave_joint1[3]._coeff);
        #endif

        break;

      default:
        break;
    }
    compute();
    isReadyCalculate = true;
    timeSpan.reset();
    isReadDyProtocol = false;
  }
}


inline void setup(){
  led = 1;
  timeSpan.start();
  setupMotor();
  device.format(8,1);
  encoder.init();
  wait(1);
  led = 0;
}

int main() {
  setup();

  while(1) {
    // put your main code here, to run repeatedly:

    #ifndef DEBUG_ENCODER
    checkReceiveData();
    onDataReceive();

    if (isReadyCalculate){
      if ( timeSpan.read_ms() > 10) {
        compute();
        led = !led;
    //     #ifdef DEBUG
    //     pc.printf("%f & %f\n",(float)getAngle()*INVERSE/4095.0 * 360.0 , encoder.getAngleAbsolute());
    //     #endif
        timeSpan.reset();
      }
      state();
    }
    #else
    pc.printf("%f & %d\n",(float)getAngle()*INVERSE/4095.0 * 360.0 , encoder.getAngleAbsolute());
    wait_ms(10);
    #endif

  }
}