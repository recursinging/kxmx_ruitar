#ifndef RuiMIDIButton_h
#define RuiMIDIButton_h

#include "RuiMIDIUtil.h"

class RuiMIDIButton {
 public:
  RuiMIDIButton(uint8_t t_idx);
  int idx;
  bool toggle;
  bool rose;
  bool state;
  int8_t ccValue;
  int8_t ccValueMomentary;
  void update();
};
#endif
