#include <mbed.h>
#include "joint_config.h"
#include "protocol_config.h"


#include "driveMotor.h"
#include <AS5600.h>

AS5600 encoder(SDA_PIN,SCL_PIN,HZ_ENCODER);  // SDA SCL
DigitalIn slaveCmdPin(PA_4);      // pin check on SPI active communication
DigitalOut pinStatus(PB_4);

int absAngle = 0;

long getAngle(int angle){
  return ((angle + (2047 - SET_ZERO)) % 4096) - 2047;
}

Timer timeSpan;
#define DEBUG

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
  return (degree / 360.0) * 4095.0;
}

int indexCalculate = 0;
bool isReadyCalculate = false;

#define T_PERIOD 0.01

inline void compute(){
  absAngle = encoder.getAngleAbsolute();
  float computeAngle = (float)getAngle(absAngle)*INVERSE/4095.0 * 360.0 ;
  

  if(!encoder.isMagnetPresent()) {
    configFb.tau = 0.0;
    isReadyCalculate = false;
    #ifdef DEBUG
    pc.printf("***encoder error***\n");
    #endif
    return;
  }

  #ifdef DEBUG
  pc.printf("%f & %d error %f : setpoint %f\n",computeAngle , absAngle, configFb.error, toEncoder(config._coeff));
  #endif


  switch (instruct)
  {
  case CONFIGURATION:
    configFb.error = config._coeff - (computeAngle);
    configFb.tau = configFb.Kp * (configFb.error)
                    + configFb.Kd * ((configFb.error - configFb.lastError) / T_PERIOD);
    configFb.lastError = configFb.error;

    break;

  case TRAJECTORY:

    trajectFb.time += T_PERIOD;
    float t = trajectFb.time;
    float tp2 = pow(trajectFb.time,2.0);
    float tp3 = pow(trajectFb.time,3.0);

    float q_ref = slave_joint1[indexCalculate]._coeff +                           // c0
                  slave_joint1[indexCalculate + 1]._coeff * t +                   // c1 * t
                  slave_joint1[indexCalculate + 2]._coeff * tp2 +                 // c2 * t^2
                  slave_joint1[indexCalculate + 3]._coeff * tp3;                  // c3 * t^3

    float q_dot_ref = slave_joint1[indexCalculate + 1]._coeff +                   // c1
                    (2.0 * slave_joint1[indexCalculate + 2]._coeff * t)+          // 2 * c2 * t
                    (3.0 * slave_joint1[indexCalculate + 3]._coeff * tp2);        // 3 * c3 * t^2

    trajectFb.error = toEncoder(q_ref) - (getAngle(absAngle) * INVERSE);

    /*
    5 column
    [c0, c1, c2, c3, T],
    [c0, c1, c2, c3, T],
    [c0, c1, c2, c3, T],
    */
    if (trajectFb.time >= slave_joint1[indexCalculate + 4]._coeff){
      if ( indexCalculate < (20) ){  // size_coeff - 5
        trajectFb.time = 0.0f;  // reset time for calcute new index
        indexCalculate += 5;
      }
    } else {                                                                      // tau = Kp(q_ref-q) + Kd(q_dot_ref - q_dot)
      trajectFb.tau = trajectFb.Kp * (trajectFb.error)
                    + trajectFb.Kd * (q_dot_ref - (trajectFb.error - trajectFb.lastError) / T_PERIOD);
      trajectFb.lastError = trajectFb.error;
    }
    break;
  }
  
}


void state(){

  switch (instruct)
  {
  case CONFIGURATION:
      if (configFb.error > 0.3){
        driveMotor(DIR_JOINT, fabs(configFb.tau));
      }else if(configFb.error < -0.3){
        driveMotor((!DIR_JOINT), fabs(configFb.tau));
      }else{
        driveMotor(0, 0);
        isReadyCalculate = false;
        pinStatus = 0;
      }
      break;
  
  case TRAJECTORY:

      if (trajectFb.error > 0.3) {
        driveMotor(DIR_JOINT, fabs(trajectFb.tau));
      }else if(trajectFb.error < -0.3){
        driveMotor((!DIR_JOINT), fabs(trajectFb.tau));
      }else{
        driveMotor(0, 0);
        isReadyCalculate = false;
        pinStatus = 0;
      }
    break;
  default:
    driveMotor(0,0);
    isReadyCalculate = false;
    pinStatus = 0;
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
        configFb.tau = 0.0;
        
        #ifdef DEBUG
        pc.printf("con %f\n",config._coeff);
        #endif

        break;
      case TRAJECTORY:
        /* code */
        trajectFb.error = 0.0;
        trajectFb.lastError = 0.0;
        trajectFb.tau = 0.0;
        trajectFb.time = 0.0;

        indexCalculate = 0; // set index calculate trajectory to home

        #ifdef DEBUG
        pc.printf("tra %f\n",slave_joint1[3]._coeff);
        #endif

        break;

      default:
        break;
    }
    compute();
    isReadyCalculate = true;
    pinStatus = 1;
    timeSpan.reset();
    isReadDyProtocol = false;
  }
}


inline void setup(){
  led = 1;
  pinStatus = 0;
  timeSpan.start();
  setupMotor();
  device.format(8,1);
  // encoder.init();
  // pc.printf("system cock %d\n",SystemCoreClock);
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

    // add new feature if SPI is inactive the system is working
    // if (slaveCmdPin == 1) {
    //   state();
    // }

    if (isReadyCalculate){
      if ( timeSpan.read_ms() > 10) {
        compute();
        led = !led;
        timeSpan.reset();
      }
      state();
    }

    #else
    absAngle = encoder.getAngleAbsolute();
    pc.printf("%f & %d\n",(float)getAngle(absAngle)*INVERSE/4095.0 * 360.0 , absAngle);
    wait_ms(10);
    #endif

  }
}