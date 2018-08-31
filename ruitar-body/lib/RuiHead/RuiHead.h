#ifndef RuitarHead_h
#define RuitarHead_h

#include <Arduino.h>
#include "RuiHeadDefines.h"

class RuiHeadClass {
public:
  RuiHeadClass();
  void begin();
  void update();

  void knob0(uint16_t r, uint16_t g, uint16_t b);
  void knob1(uint16_t r, uint16_t g, uint16_t b);
  void knob2(uint16_t r, uint16_t g, uint16_t b);
  void knob3(uint16_t r, uint16_t g, uint16_t b);

  void red(int t_idx, uint16_t intensity);
  void green(int t_idx, uint16_t intensity);
  void blue(int t_idx, uint16_t intensity);

  int8_t knob(int t_idx);

  int8_t knob0();
  int8_t knob1();
  int8_t knob2();
  int8_t knob3();

  bool button(int t_idx);

  bool button0();
  bool button1();
  bool button2();
  bool button3();

  int16_t accelX();
  int16_t accelY();
  int16_t accelZ();

  int16_t refreshRate();

  ~RuiHeadClass();
private:
  uint8_t _reg[RH_REG_LEN];
  uint8_t _read;
  uint8_t _mod;
  uint8_t _cmd;
  uint8_t _state;
  int _addr;
  static void errorEvent(void);
};

extern RuiHeadClass RuiHead;

#endif
