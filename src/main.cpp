#include "mbed.h"
#include "spi_slave.h"
#include "VL53L0X.h"
#include "MbedJSONValue.h"
#include <string>


#define VL53L0_I2C_SDA   PB_9
#define VL53L0_I2C_SCL   PB_8

MbedJSONValue dataJson;

Serial pc(USBTX, USBRX);

char buff[2048];
static DevI2C devI2c(VL53L0_I2C_SDA,VL53L0_I2C_SCL);

Ticker loopSender;
SPI spi(PC_12, PC_11, PC_10); //MOSI MISO SCLK
DigitalOut ss1(PC_5);
DigitalOut led(LED2);


void setup(){
// put your setup code here, to run once:
  ss1 = 1;
  spi.format(8,1);
  spi.frequency(20000000);
  pc.baud(115200);

  for (int i = 0; i < SIZE_DATA ; i++){
    slave_joint1[i]._coeff = 20.234;
  }
}

void sendDataSlave(DigitalOut *cs, PackData coefficient[], int size){
  int length = size + 4;
  unsigned char data[length];
  pc.printf("length is %d\n",length);
  
  addHeader(data);
  data[2] = size;
  data[length-1] = (unsigned char)(getCalChksm(coefficient) & 0xFF);
  memcpy(&data[3],coefficient,size);

  for (int num_coeff = 0 ; num_coeff < length ; num_coeff++){
    printf("%d ",data[num_coeff]);
  }
  printf("\n");
  printf("\n");

  printf("receive -> ");
  cs->write(1);
  cs->write(0);
  // wait_us(50);
  for (int num_coeff = 0 ; num_coeff < sizeof(data); num_coeff++){
    buff[num_coeff] = spi.write(data[num_coeff]);
  }
  // wait_us(50);
  cs->write(1);

  for (int num_coeff = 1 ; num_coeff < sizeof(data) ; num_coeff++){
    if (num_coeff == sizeof(data) - 1){
      printf("%d ",buff[0]);
      num_coeff += 1;
    } else {
      printf("%d ",buff[num_coeff]);
    }
    // printf("%d ",buf[num_coeff]);
  }
  printf("\n");
}

void loop(){
  // printf("distance is %d\n", dSensor);
  sendDataSlave(&ss1,slave_joint1,sizeof(slave_joint1));
  led = 1;
  wait(0.5);
  led = 0;
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