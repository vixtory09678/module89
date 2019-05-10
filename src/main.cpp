#include <mbed.h>
#include "joint_config.h"
#include "protocol_config.h"
#include "driveMotor.h"
#include <AS5600.h>

AS5600 encoder(SDA_PIN,SCL_PIN,HZ_ENCODER);  // SDA SCL
DigitalIn slaveCmdPin(PA_4);      // pin check on SPI active communication
DigitalOut pinStatus(PB_4);

int absAngle = 0;
Timer timeSpan;

// ------------------- CONFIG --------------------------//
// #define DEBUG
#ifdef DEBUG
Serial pc(A9,A10); // tx rx
#endif

// #define DEBUG_ENCODER
#ifdef DEBUG_ENCODER
Serial pc(A9,A10); // tx rx
#endif

#define T_PERIOD 0.0001

int indexCalculate = 0;
bool isReadyCalculate = false;
// ----------------- END CONFIG ------------------------//

float toEncoder(float degree){
  return (degree / 360.0) * 4095.0;
}

long getAngle(int angle){
  return ((angle + (2047 - SET_ZERO)) % 4096) - 2047;
}

inline void compute(){
  absAngle = encoder.getAngleAbsolute();
  float computeAngle = (float)getAngle(absAngle)*INVERSE / 4095.0 * 360.0 ;
  
  if(!encoder.isMagnetPresent()) {
    configFb.tau = 0.0;
    isReadyCalculate = false;
    #ifdef DEBUG
    pc.printf("***encoder error***\n");
    #endif
    // system_reset();
    
    return;
  }

  

  // #ifdef DEBUG
  // pc.printf("%f & %d error %f tau %f\n",computeAngle ,absAngle, configFb.error, configFb.tau);
  // #endif


  switch (instruct)
  {
  case CONFIGURATION:
    configFb.error = config._coeff - (computeAngle);

    #if JOINT_NUM != 1
    if (configFb.error > 0){
      configFb.Kp = KP_UP;
      configFb.Kd = KD_UP;
    }else if(configFb.error < 0){
      configFb.Kp = KP_DOWN;
      configFb.Kd = KD_DOWN;
    }
    #else
      configFb.Kp = KP_UP;
      configFb.Kp = KD_UP;
    #endif

    configFb.tau = configFb.Kp * (configFb.error)
                    + configFb.Kd * ((configFb.error - configFb.lastError) / T_PERIOD);
    configFb.lastError = configFb.error;

    break;

  case TRAJECTORY:

    trajectFb.time += T_PERIOD;
    float t = trajectFb.time;
    float tp2 = pow(trajectFb.time, 2.0);
    float tp3 = pow(trajectFb.time, 3.0);

    float q_ref = slave_joint1[indexCalculate]._coeff +                           // c0
                  slave_joint1[indexCalculate + 1]._coeff * t +                   // c1 * t
                  slave_joint1[indexCalculate + 2]._coeff * tp2 +                 // c2 * t^2
                  slave_joint1[indexCalculate + 3]._coeff * tp3;                  // c3 * t^3

    float q_dot_ref = slave_joint1[indexCalculate + 1]._coeff +                   // c1
                    (2.0 * slave_joint1[indexCalculate + 2]._coeff * t)+          // 2 * c2 * t
                    (3.0 * slave_joint1[indexCalculate + 3]._coeff * tp2);        // 3 * c3 * t^2

    trajectFb.error = q_ref - computeAngle;

    /*
    5 column
    [c0, c1, c2, c3, T],
    [c0, c1, c2, c3, T],
    [c0, c1, c2, c3, T],
    */
    if (trajectFb.time >= slave_joint1[indexCalculate + 4]._coeff){
      if ( indexCalculate < 20 ){  // size_coeff - 5
        trajectFb.time = 0.0f;  // reset time for calcute new index
        indexCalculate += 5;
      } else {
        driveMotor(0, 0);
        isReadyCalculate = false;
        pinStatus = 0;
      }
    } else {                                                                      // tau = Kp(q_ref-q) + Kd(q_dot_ref - q_dot)
      trajectFb.tau = trajectFb.Kp * (trajectFb.error)
                    + trajectFb.Kd * (q_dot_ref - (trajectFb.error - trajectFb.lastError) / T_PERIOD);
      trajectFb.lastError = trajectFb.error;
    }
    break;
  }
  
}


void control(){
  switch (instruct)
  {
  case CONFIGURATION:
      if (configFb.error > 0.18){
        driveMotor(DIR_JOINT, fabs(configFb.tau));
      }else if(configFb.error < -0.18){
        driveMotor((!DIR_JOINT), fabs(configFb.tau));
      }else{
        pinStatus = 0;
        driveMotor(0, 0);
        isReadyCalculate = false;
      }
      break;
  
  case TRAJECTORY:

      if (trajectFb.error > 0.0) {
        driveMotor(DIR_JOINT, fabs(trajectFb.tau));
      } else {
        driveMotor((!DIR_JOINT), fabs(trajectFb.tau));
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
    isReadDyProtocol = false;
    timeSpan.reset();
    pinStatus = 1;
    wait_ms(50);
  }
}


inline void setup(){
  led = 1;
  pinStatus = 0;
  timeSpan.start();
  setupMotor();
  device.format(8,1);
  wait(0.1);
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
    //   control();
    // }

    if (isReadyCalculate){
      if ( timeSpan.read_us() > 100) {
        compute();
        led = !led;
        timeSpan.reset();
      }
      control();
    }

    #else
    absAngle = encoder.getAngleAbsolute();
    pc.printf("%f & %d mag %d\n",(float)getAngle(absAngle)*INVERSE/4095.0 * 360.0 , absAngle, encoder.isMagnetPresent());
    wait_ms(10);
    #endif

  }
}