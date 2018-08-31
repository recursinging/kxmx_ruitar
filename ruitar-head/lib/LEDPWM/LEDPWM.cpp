#include "LEDPWM.h"

LEDPWM::LEDPWM(int dat, int lat, int clk) {
  _dat = dat;
  _lat = lat;
  _clk = clk;
  pwmbuffer[12] = {0};
}

void LEDPWM::write(void) {
  digitalWrite(_lat, LOW);
  for (int c = 11; c >= 0; c--) {
//    	  Serial.print("buf: ");
//    	  Serial.print(c);
//    	  Serial.print(" - ");
//    	  Serial.println(pwmbuffer[c]);
    for (int b = 11; b >= 0; b--) {
      digitalWrite(_clk, LOW);
      if (pwmbuffer[c] & (1 << b)) {
        digitalWrite(_dat, HIGH);
      } else {
        digitalWrite(_dat, LOW);
      }
      digitalWrite(_clk, HIGH);
    }
  }
  digitalWrite(_clk, LOW);
  digitalWrite(_lat, HIGH);
  digitalWrite(_lat, LOW);
}

void LEDPWM::setPWM(int chan, uint16_t pwm) {
  if (pwm > ((uint16_t) 4095)) {
    pwm = 4095;
  }
  if (chan > 11) {
    chan = 11;
  }
  pwmbuffer[chan] = pwm;
          Serial.print("Setting");
          Serial.print(pwm);
          Serial.print(" to ");
          Serial.println(chan);
}

void LEDPWM::begin() {
  memset(pwmbuffer, 0, 24);
  pinMode(_clk, OUTPUT);
  pinMode(_dat, OUTPUT);
  pinMode(_lat, OUTPUT);
  digitalWrite(_lat, LOW);
}
