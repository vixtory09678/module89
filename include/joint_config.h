#ifndef JOINT_CONFIG_H
#define JOINT_CONFIG


#define SIZE_DATA 20
#define JOINT_NUM 1

union PackData{
  float _coeff;
  uint8_t _coeff_bytes[4];
};
PackData slave_joint1[SIZE_DATA];

typedef struct _feedback{
  float Kp;
  float Ki;
  float Kd;

  float error;
  float lastError;
  float tua;
}FeedbackControl;

FeedbackControl configFb = {
  0.0f,     // Kp
  0.0f,     // Ki
  0.0f,     // Kd
  0.0f,     // error
  0.0f,     // lastError
  0.0f      // tua
};

FeedbackControl trajectFb = {
  0.0f,     // Kp
  0.0f,     // Ki
  0.0f,     // Kd
  0.0f,     // error
  0.0f,     // lastError
  0.0f      // tua
};

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