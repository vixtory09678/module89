#define SIZE_DATA 25

union PackData{
  float _coeff;
  uint8_t _coeff_bytes[4];
};
PackData slave_joint1[SIZE_DATA];
PackData slave_joint2[SIZE_DATA];
PackData slave_joint3[SIZE_DATA];
PackData slave_joint4[SIZE_DATA];
PackData slave_joint5[SIZE_DATA];
PackData slave_joint6[SIZE_DATA];

void addHeader(uint8_t *data){
    data[0] = 0xFF;
    data[1] = 0xFF;
}

int getCalChksm(PackData *data){
    int chksm = 0;
    for (int i = 0 ; i < SIZE_DATA ; i++){
        for (int j = 0; j < 4 ; j++){
            chksm += (int)data[i]._coeff_bytes[j];
        }
    }
    chksm = (~chksm);
    return chksm;
}