#ifndef COM_PROTOCOL_H
#define COM_PROTOCOL_H

#include "mbed.h"

#define CONFIGURATION 1
#define TRAJECTORY 2

#define BUFFER_SIZE 64
#define CONFIGURATION_SIZE  2
#define TRAJECTORY_SIZE     16

#ifdef PRODUCT
#define CALLBACK_DATA void (*_cb)(double data[], uint8_t modes)
#else
#define CALLBACK_DATA void (*_cb)(int data)
#endif

class ComProtocol
{
private:
    /* data */
    SPISlave device;
    uint8_t buffer[BUFFER_SIZE];
    
    int _cntBuff;
    uint8_t index;

    #ifdef PRODUCT
    void (*_callback)(double data[], uint8_t modes);
    #else
    void (*_callback)(int data);
    #endif
    Serial *mSerial;

public:
    ComProtocol(PinName,PinName,PinName,PinName);
    ComProtocol(PinName,PinName,PinName,PinName,CALLBACK_DATA);

    void setDebugOutput(Serial*);
    void setCallback(CALLBACK_DATA);
    void begin();

    void handle();
};


#endif