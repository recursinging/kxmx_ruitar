#ifndef RuiMIDIJoystick_h
#define RuiMIDIJoystick_h

#include "RuiMIDIUtil.h"

class RuiMIDIJoystick {

 public:
  RuiMIDIJoystick();
  uint8_t xPitchBendValue;
  uint8_t yPitchBendValue;
  int8_t ccXValue;
  int8_t ccYValue;
  int8_t ccXPlusValue;
  int8_t ccXMinusValue;
  int8_t ccYPlusValue;
  int8_t ccYMinusValue;
  uint16_t xRaw;
  uint16_t yRaw;
  uint16_t xConstrained;
  uint16_t yConstrained;
  void update();
};
#endif
