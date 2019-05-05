#include "mbed.h"
#include "spi_slave.h"
#include "MbedJSONValue.h"
#include <string>

using namespace std;

MbedJSONValue dataJson;
Serial pc(USBTX, USBRX);
int cnt_buff = 0;
bool flagReadSerial = false;
char buff[2048];

SPI spi(PC_12, PC_11, PC_10); //MOSI MISO SCLK
DigitalOut ss1(PC_5);
DigitalOut ss2(PC_6);
DigitalOut ss3(PC_8);
DigitalOut ss4(PC_9);
DigitalOut led(LED2);

DigitalOut valve(PB_0);

// pin status of each joint
DigitalIn status_joint1(PA_12);
DigitalIn status_joint2(PA_11);
DigitalIn status_joint3(PB_12);
DigitalIn status_joint4(PB_2);
DigitalIn status_joint5(PB_1);
DigitalIn status_joint6(PB_15);

// pin status of limit switch box
// DigitalIn status_switch(PA_4);
AnalogIn status_switch(PA_4);

void onSerialEvent() {
  if (pc.readable()) {
    while (pc.readable()) {
      uint8_t data = pc.getc();
      buff[cnt_buff++] = (char)data;

      if(data == '\n') {
        buff[cnt_buff] = '\0';
        flagReadSerial = true;
        cnt_buff = 0;
      }
    }
  }
}


void setup(){
// spi setup
  ss1 = 1;
  spi.format(8,1);
  spi.frequency(2250000);
  
  pc.baud(115200);
  pc.attach(&onSerialEvent);
}

void sendDataSlave(DigitalOut *cs, PackData coefficient[], int size, int mode){
  int length = size + 4;
  unsigned char data[length];
  
  addHeader(data);
  data[2] = mode;
  data[length-1] = (unsigned char)(getCalChksm(coefficient,size) & 0xFF);
  memcpy(&data[3],coefficient,size);

  printf("size is %d\n",length);
  for (int i = 0; i < length; i++){
    printf("%d +",data[i]);
  }
  printf("\n");

  cs->write(1);
  cs->write(0);
  wait_us(50);
  for (int num_coeff = 0 ; num_coeff < length; num_coeff++){
    buff[num_coeff] = spi.write(data[num_coeff]);
  }
  wait_us(50);
  cs->write(1);
  memset(buff,0,sizeof(buff));
}

bool flagSend = false;
bool flagReadBoxSwitch = false;
void loop(){

  // printf("data is %d \n",status_switch.read_u16());
  
  // wait(0.2);

  if (flagReadSerial) {
    // set for ready send back to pc
    flagSend = false;

    parse(dataJson,buff);
    string cmd = dataJson["cmd"].get<string>();

    // MbedJSONValue status;
    // status["cmd"] = "status";
    // status["data"] = "working";
    // string str = status.serialize();
    // printf("%s\r\n",str.c_str());

    if (cmd.compare("move") == 0){

      MbedJSONValue out;
      out["cmd"] = "status";
      out["data"] = "working";
      string strOut = out.serialize();
      printf("%s\r\n",strOut.c_str());


      for (int i = 0, cnt = 0 ; i < 5 ; i++){
        for (int j = 0; j < 5 ; j++) slave_joint1[cnt++]._coeff = dataJson["data"][0][i][j].get<double>();
      }
      for (int i = 0, cnt = 0 ; i < 5 ; i++){
        for (int j = 0; j < 5 ; j++) slave_joint2[cnt++]._coeff = dataJson["data"][1][i][j].get<double>();
      }
      for (int i = 0, cnt = 0 ; i < 5 ; i++){
        for (int j = 0; j < 5 ; j++) slave_joint3[cnt++]._coeff = dataJson["data"][2][i][j].get<double>();
      }
      for (int i = 3, cnt = 0; i < 6 ; i++){
        for (int j = 0; j < 5 ; j++){
          for (int k = 0; k < 5 ; k++) slave4[cnt++]._coeff = dataJson["data"][i][j][k].get<double>();
        }
      }   

      sendDataSlave(&ss1, slave_joint1, sizeof(slave_joint1), TRAJECTORY);
      sendDataSlave(&ss2, slave_joint2, sizeof(slave_joint2), TRAJECTORY);
      sendDataSlave(&ss3, slave_joint3, sizeof(slave_joint3), TRAJECTORY);
      sendDataSlave(&ss4, slave4, sizeof(slave4), TRAJECTORY);
      printf("send ok\n");

      

    }else if(cmd.compare("point") == 0){

      MbedJSONValue out;
      out["cmd"] = "status";
      out["data"] = "working";
      string strOut = out.serialize();
      printf("%s\r\n",strOut.c_str());

      slave_joint1[0]._coeff = dataJson["data"][0].get<double>();
      slave_joint2[0]._coeff = dataJson["data"][1].get<double>();
      slave_joint3[0]._coeff = dataJson["data"][2].get<double>();

      for (int i = 0; i < 3 ; i++){
        slave4[i]._coeff = dataJson["data"][i+3].get<double>();
      }

      sendDataSlave(&ss1, slave_joint1, 4, CONFIGURATION);
      sendDataSlave(&ss2, slave_joint2, 4, CONFIGURATION);
      sendDataSlave(&ss3, slave_joint3, 4, CONFIGURATION);
      sendDataSlave(&ss4, slave4, 12, CONFIGURATION);
      
    }else if(cmd.compare("switch_box") == 0){
      // Do something
    }else if(cmd.compare("relay") == 0){
      valve = dataJson["data"].get<int>();

      MbedJSONValue out;
      out["cmd"] = "relay";
      out["data"] = "ok";
      string strOut = out.serialize();
      printf("%s\r\n",strOut.c_str());
    }
    flagReadSerial = false;

    // clear array
    memset(buff,0,sizeof(buff));
  }

  if (status_switch.read_u16() > 40000){
    if (!flagReadBoxSwitch){

      MbedJSONValue out;
      out["cmd"] = "switch_box";
      out["data"] = 1;
      string strOut = out.serialize();
      printf("%s\r\n",strOut.c_str());

      flagReadBoxSwitch = true;
    }
  }else{
    if (flagReadBoxSwitch) {

      MbedJSONValue out;
      out["cmd"] = "switch_box";
      out["data"] = 0;
      string strOut = out.serialize();
      printf("%s\r\n",strOut.c_str());

      flagReadBoxSwitch = false;
    }
  }

  if (status_joint1 &&
        status_joint2 &&
        status_joint3 &&
        status_joint4 &&
        status_joint5 &&
        status_joint6){
    if (!flagSend) {
      flagSend = true;

      MbedJSONValue out;
      out["cmd"] = "status";
      out["data"] = "not_working";
      string strOut = out.serialize();
      printf("%s\r\n",strOut.c_str());

    }
  }
}




























int main() {
  // put your setup code here, to run once:
  setup();
  while(1) {
    // put your main code here, to run repeatedly:
    loop();
  }

return 0;
}