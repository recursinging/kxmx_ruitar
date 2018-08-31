#ifndef LEDPWM_H
#define LEDPWM_H

#include "Arduino.h"

class LEDPWM {
 public:
  LEDPWM(int dat, int lat, int clk);
  void begin();
  void setPWM(int chan, uint16_t pwm);
  void write();

 private:
  uint16_t pwmbuffer[];
  uint8_t _clk, _dat, _lat;
};


#endif
