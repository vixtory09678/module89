#define SIZE_DATA 25
#define BUFF_SIZE_BYTE 512
#define CONFIGURATION   1
#define TRAJECTORY      2


union PackData{
  float _coeff;
  uint8_t _coeff_bytes[4];
};
PackData slave_joint1[SIZE_DATA];
PackData slave_joint2[SIZE_DATA];
PackData slave_joint3[SIZE_DATA];
PackData slave4[SIZE_DATA * 3];

void addHeader(uint8_t *data){
    data[0] = 0xFF;
    data[1] = 0xFF;
}

int getCalChksm(PackData *data,int size){
    int chksm = 0;
    for (int i = 0 ; i < (size / 4) ; i++){
        for (int j = 0; j < 4 ; j++){
            chksm += (int)data[i]._coeff_bytes[j];
        }
    }
    printf("B chk %d ",chksm);
    chksm = (~chksm);
    printf("A chk %d\n",chksm);
    return chksm;
}