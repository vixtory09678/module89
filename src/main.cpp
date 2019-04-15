#include <mbed.h>
#include <AS5600.h>
#include "joint_config.h"
#include "protocol_config.h"
#include <math.h>
#include "compute.h"

AS5600 encoder(B9,B8);//SDA SCL


Ticker computeFeedback;

int  getAngle(){
  return ((encoder.getAngleAbsolute() + (2047 - SET_ZERO)) % 4096) - 2047;
}
int toEncoder(float degree){
  return (config._coeff / 360.0) * 4095;
}

int indexCalculate = 0;

#define T_PERIOD 0.002f
void compute(){
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
      indexCalculate += 1;
    } else {

    }
    break;
  }
}


void setup(){
  computeFeedback.attach(compute,T_PERIOD);
  device.format(8,1);
  encoder.init();
}

void loop(){
  checkReceiveData();

  if (isReadDyProtocol){
    switch (instruct)
    {
      case CONFIGURATION:
        /* code */
        configFb.Kp = 0.0;
        configFb.Ki = 0.0;
        configFb.Kd = 0.0;
        configFb.error = 0.0;
        configFb.lastError = 0.0;
        configFb.tua = 0.0;
        break;
      case TRAJECTORY:
        /* code */
        trajectFb.Kp = 0.0;
        trajectFb.Ki = 0.0;
        trajectFb.Kd = 0.0;
        trajectFb.error = 0.0;
        trajectFb.lastError = 0.0;
        trajectFb.tua = 0.0;

        break;

      default:
        break;
    }
    isReadDyProtocol = false;
  }
}













int main() {

  setup();

  while(1) {
    // put your main code here, to run repeatedly:
    loop();
    // if (device.receive()){
    //   // out = 1;
    //   device.reply(device.read());
    //   // out = 0;
    // }
    // if(device.receive()) {
    //   for(int i = 0; i < 4 ; i++){
    //     data[i] = device.read();
    //   }
    //   device.reply(111);

    //   pc.printf("%d\n",sizeof(data)/sizeof(data[0]));
    // }
    // pc.printf("data is %d\n",encoder.getAngleAbsolute());
    
  }
}