#include <mbed.h>
#include "joint_config.h"
#include "protocol_config.h"
#include <AS5600.h>

// #define DEBUG

long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

AS5600 encoder(B9,B8);//SDA SCL

int  getAngle(){
  return ((encoder.getAngleAbsolute() + (2047 - SET_ZERO)) % 4096) - 2047;
}

// ------------------- CONFIG --------------------------//
#ifdef DEBUG
Serial pc(A9,A10);
#endif
// ----------------- END CONFIG ------------------------//



void setup(){
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

        break;
      case TRAJECTORY:
        /* code */
        // memcpy(slave_joint1,buffer,sizeof(buffer) - 1);
        // device.reply(buffer[6]);
        // memcpy(slave_joint1,buffer,sizeof(buffer) - 1);
        // #ifdef DEBUG
        // pc.printf("data is %f\n",slave_joint1[2]._coeff);
        // #endif
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