#ifndef RuiMIDIFSR_h
#define RuiMIDIFSR_h

#include "RuiMIDIUtil.h"

class RuiMIDIFSR {
  int16_t peakValue;
  bool waiting;
  bool calculatingVelocity;
  uint16_t waitTime;
  uint64_t timer;
  uint16_t velocityWindow;

 public:
  RuiMIDIFSR(int t_idx);
  int idx;
  bool noteOn;
  int16_t rawValue;
  int16_t constrainedValue;
  int8_t ccValue;
  int8_t afterTouchValue;
  int8_t velocityValue;
  void update();
};
#endif
