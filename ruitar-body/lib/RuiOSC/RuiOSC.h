#ifndef RuiOSC_h
#define RuiOSC_h

#include <Arduino.h>
#include <OSCMessage.h>
#include "RuiPreset.h"

#include <SLIPEncodedUSBSerial.h>

enum MsgClass {
  ALL_MSG,
  CAL_MSG,
  SEN_MSG,
  PRE_MSG,
  FBK_MSG,
  PRF_MSG,
  DBG_MSG,
  MID_MSG
};

class RuiOSCClass {
  static void dispatchOSC(OSCMessage &t_msg);

  static unsigned int lastCalMsg;
  static unsigned int lastSenMsg;
  static unsigned int lastPreMsg;
  static unsigned int lastFbkMsg;
  static unsigned int lastPrfMsg;
  static unsigned int lastDbgMsg;
  static unsigned int lastMidMsg;

  static void dispatchCal();
  static void dispatchSen();
  static void dispatchPre();
  static void dispatchFbk();
  static void dispatchPrf();
  static void dispatchDbg();
  static void dispatchMid();

  static SLIPEncodedUSBSerial SLIPSerial;

  static void handlePreset(OSCMessage &msg, int offset);
  static void handleSensors(OSCMessage &msg, int offset);
  static void handleFeedback(OSCMessage &msg, int offset);
  static void handleCalibration(OSCMessage &msg, int offset);

  static char debugMsg[512];
  static int debugIdx;

 public:
  static void update();
  static void dispatch();
  static void dispatch(MsgClass t_msgClass);
  static void debug(const char *msg);
  RuiOSCClass();
};

extern RuiOSCClass RuiOSC;

#endif