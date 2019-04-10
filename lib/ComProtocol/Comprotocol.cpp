#include "ComProtocol.h"

ComProtocol::ComProtocol(PinName _mosi, PinName _miso, PinName _clk, PinName _cs)
    : device(_mosi,_miso,_clk,_cs){
        _cntBuff = 0;
        index = 0;
        mSerial = NULL;
}

ComProtocol::ComProtocol(PinName _mosi, PinName _miso, PinName _clk, PinName _cs, CALLBACK_DATA)
    : device(_mosi,_miso,_clk,_cs), _callback(_cb){
        _cntBuff = 0;
        index = 0;
        mSerial = NULL;
}

void ComProtocol::setCallback(CALLBACK_DATA){
    _callback = _cb;
}

void ComProtocol::begin(){
    device.format(8,3); // SPI 8bit tranfer and setup in MODE 0
    // device.frequency()1
}

void ComProtocol::setDebugOutput(Serial *_serial){
    mSerial = _serial;
}

void ComProtocol::handle(){
    
    if (device.receive()){
        while (device.receive()){
            if (_callback == NULL) return;
            int buff = device.read();
            device.reply(buff);
            
            // buffer[_cntBuff++] = buff;

            // switch (buffer[0])
            // {
            //     case CONFIGURATION:
            //             if (_cntBuff > (CONFIGURATION_SIZE)) {
            //                 int data = (int)(buffer[1] << 8) | (buffer[2] & 0xFF);
            //                 _callback(data);
            //                 _cntBuff = 0;
            //             }
            //         break;
                    
            //     case TRAJECTORY:
            //     break;
            
            //     default:
            //         break;
            // }

        }
    }
    
}