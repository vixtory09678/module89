#ifndef JOINT_CONFIG_H
#define JOINT_CONFIG

#define JOINT_NUM 3

#define SIZE_DATA 25
union PackData{
  float _coeff;
  uint8_t _coeff_bytes[4];
};
PackData slave_joint1[SIZE_DATA];

#if (JOINT_NUM == 1)

    #define JOINT_LIMIT 150
    #define SET_ZERO 523

#elif (JOINT_NUM == 2)

    #define JOINT_LIMIT 90
    #define SET_ZERO 1630


#elif (JOINT_NUM == 3)

    #define JOINT_LIMIT 90
    #define SET_ZERO 2715


#endif


#endif