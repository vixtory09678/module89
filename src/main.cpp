#include <mbed.h>
#include "joint_config.h"
#include <AS5600.h>

long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

AS5600 encoder(B9,B8);//SDA SCL
SPISlave device(A7,A6,A5,A4); // mosi, miso, sclk, ssel

int  getAngle(){
  return ((encoder.getAngleAbsolute() + (2047 - SET_ZERO)) % 4096) - 2047;
}

// ------------------- CONFIG --------------------------//
#ifdef DEBUG
Serial pc(A9,A10);
#endif
// ----------------- END CONFIG ------------------------//

// ----------------- RECEIVE Data ----------------------//
uint8_t cnt_buff = 0;
uint8_t path_num = 0;
// void readSerialData()
// {
//     // receive data
//     uint8_t d = getc();
//     // putc(d);
//     if (countHeader < 2)
//     {
//         if ((d & 0xff) == 0xFF)
//             countHeader += 1;
//         else
//             countHeader = 0;
//     }
//     else
//     {
//         data[i++] = d;
//         if (i > (BUFFER_SIZE - 1))
//         {
//             i = 0;
//             countHeader = 0;
//             isReady = true;
//         }
//     }
// }
// --------------- END RECEIVE Data --------------------//

void setup(){
  device.format(8,1);
  encoder.init();
}

void loop(){
  if (device.receive()){
    int tmp = device.read();
    if (cnt_buff < 2) {
      if ((tmp & 0xff) == 0xff)
        cnt_buff += 1;
      else
        cnt_buff = 0;
    } else {
      int first = cnt_buff - 2;
      

    }
    device.reply(device.read());
  }
}













int main() {

  setup();

  while(1) {
    // put your main code here, to run repeatedly:
    // loop();
    if (device.receive()){
      // out = 1;
      device.reply(device.read());
      // out = 0;
    }
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