#ifndef RuiMIDISoftPot_h
#define RuiMIDISoftPot_h

#include "RuiMIDIUtil.h"

class RuiMIDISoftPot {
 public:
  RuiMIDISoftPot(uint8_t t_idx);
  uint8_t idx;
  int16_t rawValue;
  int16_t constrainedValue;
  int8_t ccValue;
  int8_t noteValue;
  int16_t pitchBendValue;
  int8_t stickiness;
  int16_t upperBound;
  int16_t lowerBound;
  int16_t pitchBendMiddle;

  void update();
};
#endif
