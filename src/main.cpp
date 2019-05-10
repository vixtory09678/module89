#include <mbed.h>
#include "compute.h"
#include "joint_config.h"
#include "protocol_config.h"
#include "driveMotor.h"

PwmOut servo_joint[3] = {PwmOut(B0), PwmOut(A11), PwmOut(B4)};
bool flagComplete[3] = {false,false,false};

const int PERIOD_CONS_ARR[3] = {20, 3333, 20};
const int MIN_POSITION[3] = {2500, 2450, 1150};
const int MID_POSITION[3] = {2200, 1725, 1850};
const int MAX_POSITION[3] = {2200, 1000, 2550};



DigitalIn slaveCmdPin(PA_4);

DigitalOut pinStatus[3] = { DigitalOut(B12), DigitalOut(B13), DigitalOut(B14) };

Timer timeSpan;
Timer controlServo;
Timer print;
// ------------------- CONFIG --------------------------//
// #define DEBUG
#ifdef DEBUG
int position[3] = {MID_POSITION[0], MID_POSITION[1], MID_POSITION[2]};
Serial pc(A9,A10);
#else
int position[3] = {MID_POSITION[0], MID_POSITION[1], MIN_POSITION[2]};
#endif

// #define DEBUG_COMPUTE
#ifdef DEBUG_COMPUTE
// Serial pc(A9,A10);
#endif
// ----------------- END CONFIG ------------------------//

int indexCalculate = 0;
bool isReadyCalculate = false;

#define T_PERIOD 0.01

float getAngle(int joint_i){
  return map(position[joint_i], MIN_POSITION[joint_i], MAX_POSITION[joint_i], 0, 180);
}

float toPosition(float angle, int joint_i){
  if (joint_i == 0){
    return map(angle, -90.0f, 90.0f, MAX_POSITION[joint_i], MIN_POSITION[joint_i]);
  }else if(joint_i == 1){
    return map(angle, -90.0f, 90.0f, MIN_POSITION[joint_i], MAX_POSITION[joint_i]);
  }else{
    return map(angle, 0.0f, 180.0f, MIN_POSITION[joint_i], MAX_POSITION[joint_i]);
  }
}

inline void compute(){
  switch (instruct)
  {
  case CONFIGURATION:
    for(int i = 0; i < 3; i++){
      configFb[i].error = toPosition(config[i]._coeff, i) - position[i];
      if (i == 1){
        configFb[i].tua = fabs(50);
      }else{
        configFb[i].tua = fabs(50);
      }
      
    }
    break;

  case TRAJECTORY:
    for(int i = 0; i < 3; i++){
      trajectFb[i].time += T_PERIOD;

      float t = trajectFb[i].time;
      float tp2 = pow(trajectFb[i].time,2.0);
      float tp3 = pow(trajectFb[i].time,3.0);

      float q_ref = slave4[indexCalculate]._coeff +                          // c0
                    slave4[indexCalculate + 1]._coeff * t+                   // c1 * t
                    slave4[indexCalculate + 2]._coeff * tp2+                 // c2 * t^2
                    slave4[indexCalculate + 3]._coeff * tp3;                 // c3 * t^3

      // float q_dot_ref = slave4[indexCalculate + 1]._coeff +                   // c1
      //                 (2.0 * slave4[indexCalculate + 2]._coeff * t)+          // 2 * c2 * t
      //                 (3.0 * slave4[indexCalculate + 3]._coeff * tp2);        // 3 * c3 * t^2

      if (trajectFb[i].time >= slave4[indexCalculate + 4]._coeff){
        if (indexCalculate < 20){
          trajectFb[i].time = 0.0;
          indexCalculate += 5;
        }
      } else {
        trajectFb[i].tua = q_ref;
      }
    }
    break;
  }
}

void state(){

  switch (instruct)
  {
  case CONFIGURATION:
    for(int i = 0; i < 3; i++){
      
      if(flagComplete[i]){
        continue;
      }

      #ifdef DEBUG_COMPUTE
      pc.printf("[%d] angle %d , setpoint %f , error %f , setpoint_angle %f\n",i,position[i],toPosition(config[i]._coeff,i),configFb[i].error,config[i]._coeff);
      #endif

      if (i != 0){
        if (configFb[i].error > 30.0){
          position[i] = position[i] + configFb[i].tua;
        }else if(configFb[i].error < -30.0){
          position[i] = position[i] - configFb[i].tua;
        }else{
          position[i] = toPosition(config[i]._coeff, i);
          flagComplete[i] = true;
          pinStatus[i] = 0;
        }
      } else {
        if (configFb[i].error > 26.0){
          position[i] = position[i] + configFb[i].tua;
        }else if(configFb[i].error < -26.0){
          position[i] = position[i] - configFb[i].tua;
        }else{
          position[i] = toPosition(config[i]._coeff, i);
          flagComplete[i] = true;
          pinStatus[i] = 0;
        }
      }
      
    }

    if (flagComplete[0]&&flagComplete[1]&&flagComplete[2]){
      isReadyCalculate = false;
    }

    break;

  case TRAJECTORY:
      for(int i = 0; i < 3; i++){
        if (trajectFb[i].error > 2.0){
          // servo_joint[i].write(trajectFb[i].tua / 180.0);
        } else if(trajectFb[i].error < -2.0) {
        
        } else {
          // servo_joint[i].write(slave4[i]._coeff / 180.0);
          isReadyCalculate = false;
        }
      }
  }
}

inline void onDataReceive(){
  if (isReadDyProtocol){

    switch (instruct)
    {
      case CONFIGURATION:
        /* code */
        for(int i = 0; i < 3; i++){
          configFb[i].error = 0.0;
          configFb[i].tua = 0.0;

          #ifdef DEBUG_COMPUTE
          pc.printf("con %f\n",config[i]._coeff);
          #endif
        }

        break;
      case TRAJECTORY:
        /* code */
        for (int i = 0; i < 3; i++){
          trajectFb[i].error = 0.0;
          trajectFb[i].tua = 0.0;
          trajectFb[i].time = 0.0;
        }

        break;

      default:
        break;
    }
    compute();
    isReadyCalculate = true;
    timeSpan.reset();
    isReadDyProtocol = false;

    for (int i = 0; i < 3; i++){
      pinStatus[i] = 1;
      flagComplete[i] = false;
    }
    
  }
}

inline void setup(){
  timeSpan.start();
  controlServo.start();
  print.start();
  led = 1;
  device.format(8,1);

  config[0]._coeff = 0.0f;
  config[1]._coeff = 0.0f;
  config[2]._coeff = 0.0f;
  
  servo_joint[0].period_ms(PERIOD_CONS_ARR[0]);
  servo_joint[1].period_us(PERIOD_CONS_ARR[1]);
  servo_joint[2].period_ms(PERIOD_CONS_ARR[2]);

  for (int i = 0; i < 3; i++){
    pinStatus[i] = 0;
    servo_joint[i].pulsewidth_us(position[i]);
  }

  wait(2);
  led = 0;
}

#ifdef DEBUG
void readAble(){
  if(pc.readable()){
    switch(pc.getc()) {
        case '1': position[0] += 50; break;
        case '2': position[0] -= 50; break;

        case '3': position[1] += 50; break;
        case '4': position[1] -= 50; break;

        case '5': position[2] += 50; break;
        case '6': position[2] -= 50; break;
    }
  }
}
#endif

int num = 0;

int main() {
  setup();
  #ifdef DEBUG
  pc.attach(readAble);
  #endif

  while(1) {
    // put your main code here, to run repeatedly:
    
    #ifndef DEBUG
    checkReceiveData();
    onDataReceive();

    if(slaveCmdPin == 1){
      if (controlServo.read_ms() > 50){
        state();
        for (int i = 0; i < 3 ; i++){
          if (slaveCmdPin == 0) break;
          servo_joint[i].pulsewidth_us(position[i]);
        }
        controlServo.reset();
      }
    }

    // if (slaveCmdPin == 1) {
    //   if (print.read_ms() > 100){
    //     pc.printf("[%d] p %d\n",num,position[num]);
    //     num = (num < 2) ? num + 1 : 0;
    //     print.reset();
    //   }
    // }

    if (isReadyCalculate){
      if ( timeSpan.read_ms() > 50){
        compute();
        led = !led;
        timeSpan.reset();
      }
    }
    #else
    if( timeSpan.read_ms() > 100){
      for(int i = 0; i < 3; i++){
        servo_joint[i].pulsewidth_us(position[i]);
        pc.printf("position[%d] : %d ",i,position[i]);
      }
      pc.printf("\n");
      timeSpan.reset();
    }
    #endif
  }
}