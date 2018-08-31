#ifndef RuiMIDIFader_h
#define RuiMIDIFader_h

#include "RuiMIDIUtil.h"

class RuiMIDIFader {
 public:
  RuiMIDIFader(uint8_t t_idx);
  uint8_t idx;
  int16_t rawValue;
  int16_t constrainedValue;
  int8_t ccValue;
  int8_t noteValue;
  int16_t pitchBendValue;
  int8_t stickiness;
  int16_t upperBound;
  int16_t lowerBound;

  void update();
};
#endif
