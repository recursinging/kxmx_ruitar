#ifndef RuiMIDIToggle_h
#define RuiMIDIToggle_h

#include "RuiMIDIUtil.h"

class RuiMIDIToggle {
 public:
  RuiMIDIToggle(uint8_t t_idx);
  int idx;
  bool toggle;
  bool rose;
  bool state;
  int8_t ccValue;
  int8_t ccValueMomentary;
  void update();
};
#endif
