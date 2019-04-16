#ifndef PROTOCOL_CONFIG_H
#define PROTOCOL_CONFIG_H

#include <mbed.h>

#define CONFIGURATION   1
#define TRAJECTORY      2

#define PACKET_SIZE     SIZE_DATA * 4

SPISlave device(A7,A6,A5,A4); // mosi, miso, sclk, ssel
DigitalOut led(PC_13);
// ----------------- RECEIVE Data ----------------------//
uint8_t buffer[128];
uint8_t cnt_buff = 0;
uint8_t i = 0;
uint8_t instruct = 0;

bool isReadDyProtocol = false;

inline void checkReceiveData(){
    if (device.receive()) {
        while(device.receive()) {

            int tmp = device.read();

            if (cnt_buff < 2) {
                // device.reply(255);
                if ((tmp & 0xff) == 0xff)
                    cnt_buff += 1;
                else
                    cnt_buff = 0;
            } else if (cnt_buff < 3){
                // device.reply(200);
                instruct = tmp;
                cnt_buff += 1;
            } else {
                switch (instruct)
                {
                case CONFIGURATION:
                    if (i < 5) {
                        // reply to master
                        device.reply(buffer[i]);
                        buffer[i++] = tmp;
                    } else {
                        int chkSm = ~(buffer[0] + buffer[1]) & 0xFF;
                        if (chkSm == buffer[2]){
                            // complete
                            isReadDyProtocol = true;
                        }else{
                            device.reply(11);
                        }
                        cnt_buff = 0;
                        i = 0;
                    }
                    break;
                case TRAJECTORY:
                    if (i < PACKET_SIZE) {
                        // device.reply(55);
                        buffer[i++] = tmp;
                    }else{
                        int chkSm = 0;
                        for (int n = 0; n < PACKET_SIZE; n++) {
                            chkSm += buffer[n];
                        }
                        chkSm = (~chkSm) & 0xFF;

                        if (chkSm == tmp){
                            // complete
                            led = !led;
                            memcpy(slave_joint1,buffer,PACKET_SIZE-1);
                            device.reply(slave_joint1[2]._coeff*10);
                            isReadDyProtocol = true;
                        } else {
                            led = 0;
                        }

                        cnt_buff = 0;
                        i = 0;
                    }
                    break;
                default:
                    cnt_buff = 0;
                    break;
                }
            }
        }
    }
}
// --------------- END RECEIVE Data --------------------//
#endif