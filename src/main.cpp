#include "mbed.h"
#include "spi_slave.h"
#include "VL53L0X.h"
#include "MbedJSONValue.h"
#include <string>


#define VL53L0_I2C_SDA   PB_9
#define VL53L0_I2C_SCL   PB_8

MbedJSONValue dataJson;
Serial pc(USBTX, USBRX);
int cnt_buff = 0;
bool flagReadSerial = false;

char buff[2048];
static DevI2C devI2c(VL53L0_I2C_SDA,VL53L0_I2C_SCL);

Ticker loopSender;
SPI spi(PC_12, PC_11, PC_10); //MOSI MISO SCLK
DigitalOut ss1(PC_5);
DigitalOut ss2(PC_6);
DigitalOut ss3(PC_8);
DigitalOut ss4(PC_9);
DigitalOut led(LED2);

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
// put your setup code here, to run once:
  ss1 = 1;
  spi.format(8,1);
  spi.frequency(20000000);
  pc.baud(115200);
  pc.attach(&onSerialEvent);

  // for (int i = 0; i < SIZE_DATA ; i++){
  //   slave_joint1[i]._coeff = 1.55;
  // }
}

void sendDataSlave(DigitalOut *cs, PackData coefficient[], int size){
  int length = size + 4;
  unsigned char data[length];
  
  addHeader(data);
  data[2] = (size == 4) ? 1 : 2;
  data[length-1] = (unsigned char)(getCalChksm(coefficient) & 0xFF);
  memcpy(&data[3],coefficient,size);

  cs->write(1);
  cs->write(0);
  wait_us(50);
  for (int num_coeff = 0 ; num_coeff < sizeof(data); num_coeff++){
    buff[num_coeff] = spi.write(data[num_coeff]);
  }
  wait_us(50);
  cs->write(1);

//  printf("receive -> ");
//   for (int num_coeff = 1 ; num_coeff < sizeof(data) ; num_coeff++){
//     if (num_coeff == sizeof(data) - 1){
//       printf("%d ",buff[0]);
//       num_coeff += 1;
//     } else {
//       printf("%d ",buff[num_coeff]);
//     }
//   }
//   printf("\n");
}

void loop(){
  
  if (flagReadSerial) {

    parse(dataJson,buff);
    string cmd = dataJson["cmd"].get<string>();

    if (cmd.compare("move") == 0){
      for (int i = 0, cnt = 0 ; i < 4 ; i++){
        for (int j = 0; j < 5 ; j++) slave_joint1[cnt++]._coeff = dataJson["data"][0][i][j].get<double>();
      }
      for (int i = 0, cnt = 0 ; i < 4 ; i++){
        for (int j = 0; j < 5 ; j++) slave_joint2[cnt++]._coeff = dataJson["data"][1][i][j].get<double>();
      }
      for (int i = 0, cnt = 0 ; i < 4 ; i++){
        for (int j = 0; j < 5 ; j++) slave_joint3[cnt++]._coeff = dataJson["data"][2][i][j].get<double>();
      }
      for (int i = 0, cnt = 0 ; i < 4 ; i++){
        for (int j = 0; j < 5 ; j++) slave_joint4[cnt++]._coeff = dataJson["data"][3][i][j].get<double>();
      }

      sendDataSlave(&ss1,slave_joint1,sizeof(slave_joint1));
      sendDataSlave(&ss2,slave_joint2,sizeof(slave_joint2));
      sendDataSlave(&ss3,slave_joint3,sizeof(slave_joint3));
      sendDataSlave(&ss4,slave_joint4,sizeof(slave_joint4));

    }else if(cmd.compare("point") == 0){

      slave_joint1[0]._coeff = dataJson["data"][0].get<double>();
      slave_joint2[0]._coeff = dataJson["data"][1].get<double>();
      slave_joint3[0]._coeff = dataJson["data"][2].get<double>();
      slave_joint4[0]._coeff = dataJson["data"][3].get<double>();

      sendDataSlave(&ss1, slave_joint1, 4);
      sendDataSlave(&ss2, slave_joint2, 4);
      sendDataSlave(&ss3, slave_joint3, 4);
      sendDataSlave(&ss4, slave_joint4, 4);
    }
    flagReadSerial = false;
  }
  // led = 1;
  // wait(0.5);
  // led = 0;
  // wait(0.5);
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