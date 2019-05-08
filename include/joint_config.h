#ifndef JOINT_CONFIG_H
#define JOINT_CONFIG


#define SIZE_DATA 75
#define SIZE_CONFIG_DATA 3
#define JOINT_NUM 4

union PackData{
  float _coeff;
  uint8_t _coeff_bytes[4];
};
PackData slave4[SIZE_DATA];
PackData config[SIZE_CONFIG_DATA];

typedef struct _feedback{
  float Kp;
  float Ki;
  float Kd;

  float error;
  float lastError;
  float tua;

  float time;
}FeedbackControl;

#if (JOINT_NUM == 1)
    #define JOINT_LIMIT 150
    #define SET_ZERO 485
    #define SDA_PIN B9
    #define SCL_PIN B8
    #define INVERSE -1
    #define DIR_JOINT 1
    #define LIMIT_MIN_TUA 2000.0f
    #define LIMIT_MAX_TUA 10000.0f
#elif (JOINT_NUM == 2)
    #define JOINT_LIMIT 90
    #define SET_ZERO 1642
    #define SDA_PIN B9
    #define SCL_PIN B8
    #define INVERSE 1
    #define DIR_JOINT 0
    #define LIMIT_MIN_TUA 10.0f
    #define LIMIT_MAX_TUA 500.0f
    #define KP 1.0
    #define KI 0.0
    #define KD 0.0
#elif (JOINT_NUM == 3)
    #define JOINT_LIMIT 90
    #define SET_ZERO 2509
    #define SDA_PIN B9
    #define SCL_PIN B8
    #define INVERSE -1
    #define DIR_JOINT 0
    #define LIMIT_MIN_TUA 2000.0f
    #define LIMIT_MAX_TUA 10000.0f
    #define KP 1.0
    #define KI 0.0
    #define KD 0.0
#elif (JOINT_NUM == 4)
    #define JOINT_LIMIT 90
    #define SET_ZERO 2509
    #define SDA_PIN B9
    #define SCL_PIN B8
    #define INVERSE -1
    #define DIR_JOINT 0
    #define LIMIT_MIN_TUA 2000.0f
    #define LIMIT_MAX_TUA 10000.0f
    #define KP 2.0
    #define KI 0.0
    #define KD 0.0
#endif
FeedbackControl configFb[3] = {
  KP,     // Kp
  KI,     // Ki
  KD,     // Kd

  0.0f,     // error
  0.0f,     // lastError
  0.0f,     // tua
  0.0f      // time
};
FeedbackControl trajectFb[3] = {
  KP,     // Kp
  KI,     // Ki
  KD,     // Kd

  0.0f,     // error
  0.0f,     // lastError
  0.0f,     // tua
  0.0f      // time
};

#endif