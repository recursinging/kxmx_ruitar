#ifndef RuiBody_h
#define RuiBody_h

#include <Arduino.h>

#define NN 4

enum SensorMode { PHY, OSC };

struct SensorCalibration {
  int16_t stringsInputMin[NN] = {0, 0, 0, 0};
  int16_t stringsInputMax[NN] = {800, 800, 800, 800};
  int16_t stringsInputThresh[NN] = {5, 5, 5, 5};
  int16_t stringsChangeThresh[NN] = {3, 3, 3, 3};
  int16_t padsInputMin[NN] = {0, 0, 0, 0};
  int16_t padsInputMax[NN] = {1000, 1000, 1000, 1000};
  int16_t padsInputThresh[NN] = {50, 50, 50, 50};
  int16_t padsChangeThresh[NN] = {5, 5, 5, 5};
  int16_t fadersInputMin[NN] = {0, 0, 0, 0};
  int16_t fadersInputMax[NN] = {1024, 1024, 1024, 1024};
  int16_t fadersChangeThresh[NN] = {15, 15, 15, 15};
  int16_t joystickInputMin = 0;
  int16_t joystickInputMax = 1024;
  int16_t joystickXMiddle = 512;
  int16_t joystickYMiddle = 512;
  int16_t joystickChangeThresh = 5;
  int16_t accelChangeThresh = 2;
  uint16_t calMsgRate = 10000;
  uint16_t senMsgRate = 50;
  uint16_t preMsgRate = 5000;
  uint16_t fbkMsgRate = 50;
  uint16_t prfMsgRate = 1000;
  uint16_t dbgMsgRate = 100;
  uint16_t midMsgRate = 50;
};

struct SensorState {
  int16_t stringsV[NN] = {0, 0, 0, 0};
  int16_t padsV[NN] = {0, 0, 0, 0};
  int16_t fadersV[NN] = {0, 0, 0, 0};
  bool togglesV[NN] = {false, false, false, false};
  int16_t knobsV[NN] = {0, 0, 0, 0};
  bool buttonsV[NN] = {false, false, false, false};
  int16_t jsXv = 0;
  int16_t jsYv = 0;
  int16_t accXv = 0;
  int16_t accYv = 0;
  int16_t accZv = 0;
};

struct FeedbackState {
  uint16_t headLedsR[NN] = {0, 0, 0, 0};
  uint16_t headLedsG[NN] = {0, 0, 0, 0};
  uint16_t headLedsB[NN] = {0, 0, 0, 0};
  uint16_t toggleLeds[NN] = {0, 0, 0, 0};
};

struct PerformanceState {
  int refreshRate = 0;
  float audioCpuUsage = 0;
  float audioCpuUsageMax = 0;
  float audioMemUsage = 0;
  float audioMemUsageMax = 0;
};

class RuiBodyClass {
 public:
  SensorMode sensorMode = PHY;
  SensorCalibration calibration;
  SensorState sensors;
  SensorState sensorsLast;
  FeedbackState feedback;
  FeedbackState feedbackLast;
  PerformanceState performance;
  RuiBodyClass();
};

extern RuiBodyClass RuiBody;

#endif
