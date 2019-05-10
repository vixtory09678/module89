#ifndef JOINT_CONFIG_H
#define JOINT_CONFIG


#define SIZE_DATA 25
#define JOINT_NUM 1

union PackData{
  float _coeff;
  uint8_t _coeff_bytes[4];
};

PackData slave_joint1[SIZE_DATA];
PackData config;

typedef struct _feedback{
  float Kp;
  float Ki;
  float Kd;

  float error;
  float lastError;
  float tau;

  float time;
}FeedbackControl;

#if (JOINT_NUM == 1)
    #define JOINT_LIMIT 150
    #define SET_ZERO 1545
    #define SDA_PIN B11
    #define SCL_PIN B10
    #define INVERSE -1
    #define DIR_JOINT 1
    #define KP_UP 8.0
    #define KI_UP 0.0
    #define KD_UP 1.5
    #define HZ_ENCODER 100000
#elif (JOINT_NUM == 2)
    #define JOINT_LIMIT 90
    #define SET_ZERO 1648
    #define SDA_PIN B11
    #define SCL_PIN B10
    #define INVERSE 1
    #define DIR_JOINT 0

    #define KP_UP 5.0
    #define KI_UP 0.0
    #define KD_UP 1.0

    #define KP_DOWN 5.0
    #define KI_DOWN 0.0
    #define KD_DOWN 0.0
    #define HZ_ENCODER 100000
#elif (JOINT_NUM == 3)
    #define JOINT_LIMIT 90
    #define SET_ZERO 857
    #define SDA_PIN B11
    #define SCL_PIN B10
    #define INVERSE -1
    #define DIR_JOINT 0
    
    #define KP_UP 8.0
    #define KI_UP 0.0
    #define KD_UP 2.0

    #define KP_DOWN 5.0
    #define KI_DOWN 0.0
    #define KD_DOWN 2.0
    #define HZ_ENCODER 100000
#endif

FeedbackControl configFb = {
  KP_UP,     // Kp
  KI_UP,     // Ki
  KD_UP,     // Kd

  0.0f,     // error
  0.0f,     // lastError
  0.0f,     // tua
  0.0f      // time
};

FeedbackControl trajectFb = {
  KP_UP,     // Kp
  KI_UP,     // Ki
  KD_UP,     // Kd

  0.0f,     // error
  0.0f,     // lastError
  0.0f,     // tua
  0.0f      // time
};

#endif