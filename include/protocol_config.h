#ifndef PROTOCOL_CONFIG_H
#define PROTOCOL_CONFIG_H

#include <mbed.h>

// #define DEBUG

#define CONFIGURATION      1
#define TRAJECTORY         2
#define WAITING            3


#define PACKET_SIZE         SIZE_DATA * 4
#define PACKET_CONFIG_SIZE  4

//
DigitalOut led(PC_13);
// ----------------- RECEIVE Data ----------------------//
uint8_t buffer[128];
uint8_t cnt_buff = 0;
uint8_t i = 0;

SPISlave device(A7,A6,A5,A4); // mosi, miso, sclk, ssel
int instruct = 0;
bool isReadDyProtocol = false;

inline void checkReceiveData(){

    if (device.receive()) {
        // config before data receive loop

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
                    if (i < PACKET_CONFIG_SIZE) {
                        buffer[i++] = tmp;
                        device.reply(buffer[i-1]);
                    } else {
                        int chkSm = ~(buffer[0] + buffer[1] + buffer[2] + buffer[3]) & 0xFF;
                        if (chkSm == tmp){
                            // complete
                            led = !led;
                            memcpy(&config,buffer,PACKET_CONFIG_SIZE);
                            isReadDyProtocol = true;
                        }else{
                            led = 0;
                        }
                        cnt_buff = 0;
                        i = 0;
                    }
                    break;
                case TRAJECTORY:
                    if (i < PACKET_SIZE) {
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
                            memcpy(slave_joint1,buffer,PACKET_SIZE);
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