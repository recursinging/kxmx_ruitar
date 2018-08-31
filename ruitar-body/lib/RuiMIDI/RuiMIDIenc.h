#ifndef RuiMIDIenc_h
#define RuiMIDIenc_h

#include "RuiMIDIUtil.h"

class RuiMIDIenc {
  int8_t buffer;

 public:
  RuiMIDIenc(uint8_t t_idx);
  int idx;
  int8_t ccValue;
  void update();
};
#endif
