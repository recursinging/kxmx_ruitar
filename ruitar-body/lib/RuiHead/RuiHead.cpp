#include "RuiHead.h"
//#include <i2c_t3.h>
#include <Wire.h>


RuiHeadClass::RuiHeadClass() {
  _reg[RH_REG_LEN] = {0};
  _read = 0;
  _mod = 0;
  _cmd = 0;
  _addr = 0;
  _state = 0;
  memset(_reg, 0, sizeof(_reg));
}

// destructor
RuiHeadClass::~RuiHeadClass() {
}

void RuiHeadClass::errorEvent(void) {
//  Serial.print("FAIL - ");
//  switch (Wire.status()) {
//  case I2C_TIMEOUT:
//    Serial.print("I2C timeout\n");
//    Wire2.resetBus();
//    break;
//  case I2C_ADDR_NAK:
//    Serial.print("Slave addr not acknowledged\n");
//    break;
//  case I2C_DATA_NAK:
//    Serial.print("Slave data not acknowledged\n");
//    break;
//  case I2C_ARB_LOST:
//    Serial.print("Arbitration Lost, possible pullup problem\n");
//    Wire2.resetBus();
//    break;
//  case I2C_BUF_OVF:
//    Serial.print("I2C buffer overflow\n");
//    break;
//  case I2C_NOT_ACQ:
//    Serial.print("Cannot acquire bus, possible stuck SDA/SCL\n");
//    Wire2.resetBus();
//    break;
//  case I2C_DMA_ERR:
//    Serial.print("DMA Error\n");
//    break;
//  default:
//    break;
//  }
}

void RuiHeadClass::begin() {
  Wire2.begin();
  Wire2.setClock(RH_FREQ);

//  Serial.print("Initializing RuiHeadClass I2C...");
//  Wire2.begin(I2C_MASTER, 0, I2C_PINS_3_4, I2C_PULLUP_EXT, RH_FREQ,
//      I2C_OP_MODE_ISR);
//  Wire2.setDefaultTimeout(50000); // 50ms
//  Wire2.onError(RuiHeadClass::errorEvent);
//  Serial.println("...done!");
}

void RuiHeadClass::update() {

    // Reading from Slave ------------------------------------------------------
    Wire2.beginTransmission(RH_ADDR);         // slave addr
    Wire2.write(RH_READ);                       // READ command
    Wire2.write(RH_STATE);                       // memory address
    Wire2.requestFrom(RH_ADDR, RH_REG_LEN - RH_STATE); // NON-blocking read (request 256 bytes)
    int idx = RH_STATE;
    while (Wire2.available()) {
      _reg[idx] = Wire2.read();
      idx++;
    }

    if (_mod) {
      //Serial.println("Writing data to head from BODY");
      Wire2.beginTransmission(RH_ADDR);         // slave addr
      Wire2.write(RH_WRITE);                      // WRITE command
      Wire2.write(RH_K0LEDR);                       // memory address
      //Serial.println("Sending registers...");
      Wire2.write(_reg, RH_FLAGS);               // write 256 byte block
//      Wire2.sendTransmission(I2C_STOP); // NON-blocking write (when not specified I2C_STOP is implicit)
//      Wire2.finish(50000);
      //Serial.println("...done!");
      _mod = 0;
    }


//  // Reading from Slave ------------------------------------------------------
//  Wire2.beginTransmission(RH_ADDR);         // slave addr
//  Wire2.write(RH_READ);                       // READ command
//  Wire2.write(RH_STATE);                       // memory address
//  Wire2.endTransmission(I2C_NOSTOP, 500000); // blocking write (NOSTOP triggers RepSTART on next I2C command)
//  Wire2.sendRequest(RH_ADDR, RH_REG_LEN - RH_STATE, I2C_STOP); // NON-blocking read (request 256 bytes)
//  Wire2.finish(50000);
//  int idx = RH_STATE;
//  while (Wire2.available()) {
//    _reg[idx] = Wire2.readByte();
//    idx++;
//  }
//
//  if (_mod) {
//    //Serial.println("Writing data to head from BODY");
//    Wire2.beginTransmission(RH_ADDR);         // slave addr
//    Wire2.write(RH_WRITE);                      // WRITE command
//    Wire2.write(RH_K0LEDR);                       // memory address
//    //Serial.println("Sending registers...");
//    Wire2.write(_reg, RH_FLAGS);               // write 256 byte block
//    Wire2.sendTransmission(I2C_STOP); // NON-blocking write (when not specified I2C_STOP is implicit)
//    Wire2.finish(50000);
//    //Serial.println("...done!");
//    _mod = 0;
//  }

}

void RuiHeadClass::red(int t_idx, uint16_t intensity) {
  int addr;
  switch (t_idx) {
  case 0:
    addr = RH_K0LEDR;
    break;
  case 1:
    addr = RH_K1LEDR;
    break;
  case 2:
    addr = RH_K2LEDR;
    break;
  case 3:
    addr = RH_K3LEDR;
    break;
  default:
    return;
    break;
  }
  _reg[addr] = (uint8_t) intensity;
  _reg[addr + 1] = (uint8_t) (intensity >> 8);
  _mod = 1;
}
void RuiHeadClass::green(int t_idx, uint16_t intensity) {
  int addr;
  switch (t_idx) {
  case 0:
    addr = RH_K0LEDG;
    break;
  case 1:
    addr = RH_K1LEDG;
    break;
  case 2:
    addr = RH_K2LEDG;
    break;
  case 3:
    addr = RH_K3LEDG;
    break;
  default:
    return;
    break;
  }
  _reg[addr] = (uint8_t) intensity;
  _reg[addr + 1] = (uint8_t) (intensity >> 8);
  _mod = 1;
}
void RuiHeadClass::blue(int t_idx, uint16_t intensity) {
  int addr;
  switch (t_idx) {
  case 0:
    addr = RH_K0LEDB;
    break;
  case 1:
    addr = RH_K1LEDB;
    break;
  case 2:
    addr = RH_K2LEDB;
    break;
  case 3:
    addr = RH_K3LEDB;
    break;
  default:
    return;
    break;
  }
  _reg[addr] = (uint8_t) intensity;
  _reg[addr + 1] = (uint8_t) (intensity >> 8);
  _mod = 1;
}

void RuiHeadClass::knob0(uint16_t r, uint16_t g, uint16_t b) {
  _reg[RH_K0LEDR] = (uint8_t) r;
  _reg[RH_K0LEDR + 1] = (uint8_t) (r >> 8);
  _reg[RH_K0LEDG] = (uint8_t) g;
  _reg[RH_K0LEDG + 1] = (uint8_t) (g >> 8);
  _reg[RH_K0LEDB] = (uint8_t) b;
  _reg[RH_K0LEDB + 1] = (uint8_t) (b >> 8);
  _mod = 1;
}
void RuiHeadClass::knob1(uint16_t r, uint16_t g, uint16_t b) {
  _reg[RH_K1LEDR] = (uint8_t) r;
  _reg[RH_K1LEDR + 1] = (uint8_t) (r >> 8);
  _reg[RH_K1LEDG] = (uint8_t) g;
  _reg[RH_K1LEDG + 1] = (uint8_t) (g >> 8);
  _reg[RH_K1LEDB] = (uint8_t) b;
  _reg[RH_K1LEDB + 1] = (uint8_t) (b >> 8);
  _mod = 1;
}
void RuiHeadClass::knob2(uint16_t r, uint16_t g, uint16_t b) {
  _reg[RH_K2LEDR] = (uint8_t) r;
  _reg[RH_K2LEDR + 1] = (uint8_t) (r >> 8);
  _reg[RH_K2LEDG] = (uint8_t) g;
  _reg[RH_K2LEDG + 1] = (uint8_t) (g >> 8);
  _reg[RH_K2LEDB] = (uint8_t) b;
  _reg[RH_K2LEDB + 1] = (uint8_t) (b >> 8);
  _mod = 1;
}
void RuiHeadClass::knob3(uint16_t r, uint16_t g, uint16_t b) {
  _reg[RH_K3LEDR] = (uint8_t) r;
  _reg[RH_K3LEDR + 1] = (uint8_t) (r >> 8);
  _reg[RH_K3LEDG] = (uint8_t) g;
  _reg[RH_K3LEDG + 1] = (uint8_t) (g >> 8);
  _reg[RH_K3LEDB] = (uint8_t) b;
  _reg[RH_K3LEDB + 1] = (uint8_t) (b >> 8);
  _mod = 1;
}

int8_t RuiHeadClass::knob(int t_idx) {
  switch (t_idx) {
  case 0:
    return knob0();
    break;
  case 1:
    return knob1();
    break;
  case 2:
    return knob2();
    break;
  case 3:
    return knob3();
    break;
  default:
    return 0;
    break;
  }
}

int8_t RuiHeadClass::knob0() {
  return _reg[RH_K0CNT];
}
int8_t RuiHeadClass::knob1() {
  return _reg[RH_K1CNT];
}
int8_t RuiHeadClass::knob2() {
  return _reg[RH_K2CNT];
}
int8_t RuiHeadClass::knob3() {
  return _reg[RH_K3CNT];
}

bool RuiHeadClass::button(int t_idx) {
  switch (t_idx) {
  case 0:
    return button0();
    break;
  case 1:
    return button1();
    break;
  case 2:
    return button2();
    break;
  case 3:
    return button3();
    break;
  default:
    return false;
    break;
  }
}

bool RuiHeadClass::button0() {
  return (_reg[RH_STATE] >> RH_SW0BIT) & 1;
}
bool RuiHeadClass::button1() {
  return (_reg[RH_STATE] >> RH_SW1BIT) & 1;
}
;
bool RuiHeadClass::button2() {
  return (_reg[RH_STATE] >> RH_SW2BIT) & 1;
}
bool RuiHeadClass::button3() {
  return (_reg[RH_STATE] >> RH_SW3BIT) & 1;
}

int16_t RuiHeadClass::accelX() {
  return ((((int16_t) _reg[RH_ACCLX + 1]) << 8) | _reg[RH_ACCLX]);
}
int16_t RuiHeadClass::accelY() {
  return ((((int16_t) _reg[RH_ACCLY + 1]) << 8) | _reg[RH_ACCLY]);
}
int16_t RuiHeadClass::accelZ() {
  return ((((int16_t) _reg[RH_ACCLZ + 1]) << 8) | _reg[RH_ACCLZ]);
}
int16_t RuiHeadClass::refreshRate() {
  return ((((int16_t) _reg[RH_RFRSH + 1]) << 8) | _reg[RH_RFRSH]);
}

RuiHeadClass RuiHead;
