#ifndef PROTOCOL_CONFIG_H
#define PROTOCOL_CONFIG_H

#include <mbed.h>

#define CONFIGURATION   1
#define TRAJECTORY      2
#define PACKET_SIZE     SIZE_DATA * 4

SPISlave device(A7,A6,A5,A4); // mosi, miso, sclk, ssel
// ----------------- RECEIVE Data ----------------------//
uint8_t buffer[128];
uint8_t cnt_buff = 0;
uint8_t i = 0;
uint8_t instruct = 0;

bool isReadDyProtocol = false;

void checkReceiveData(){
    if (device.receive()) {
        while(device.receive()) {

            int tmp = device.read();

            if (cnt_buff < 2) {
                if ((tmp & 0xff) == 0xff)
                    cnt_buff += 1;
                else
                    cnt_buff = 0;
            } else if (cnt_buff < 3){
                instruct = tmp;
                cnt_buff += 1;
            } else {
                switch (instruct)
                {
                case CONFIGURATION:
                    if (i < 3) {
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
                    if (i < 101) {

                        buffer[i++] = tmp;
                    } else {
                        int chkSm = 0;
                        for (int n = 0; n < PACKET_SIZE; n++) {
                            chkSm += buffer[n];
                        }
                        chkSm = (~chkSm) & 0xFF;

                        if (chkSm == buffer[PACKET_SIZE]){
                            // complete
                            memcpy(slave_joint1,buffer,sizeof(buffer) - 1);
                            device.reply(slave_joint1[4]._coeff*10);
                            // device.reply(slave_joint1[2]._coeff*10);
                            isReadDyProtocol = true;
                        } else {

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