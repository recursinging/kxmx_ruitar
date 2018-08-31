#ifndef SynthUtil_h
#define SynthUtil_h

#ifndef ARDUINO

#include <cstdint>
#include <stdio.h>

#define constrain(amt, low, high) ({ \
  typeof(amt) _amt = (amt); \
  typeof(low) _low = (low); \
  typeof(high) _high = (high); \
  (_amt < _low) ? _low : ((_amt > _high) ? _high : _amt); \
})

inline long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

#include <chrono>
inline long micros() {
  std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
  auto duration = now.time_since_epoch();
  auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration);
  duration -= microseconds;
  return (long)(microseconds.count());
}

#else

#include <Arduino.h>
#include <Audio.h>

#endif

#include "RuiMIDIUtil.h"
#include "RuiPreset.h"

class RuiSynthUtil {
public:

};


#endif
