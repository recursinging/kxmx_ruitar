#include "Encoder.h"
#include "Accelerometer.h"
#include "i2c_t3.h"
#include "Adafruit_TLC5947.h"
#include "RuitarHeadDefines.h"

#define KNOB_0A 9
#define KNOB_0B 8
#define KNOB_1A 7
#define KNOB_1B 6
#define KNOB_2A 5
#define KNOB_2B 4
#define KNOB_3A 3
#define KNOB_3B 2

#define SW0 16
#define SW1 17
#define SW2 21
#define SW3 22

#define LEDPWM_DAT 0
#define LEDPWM_LAT 1
#define LEDPWM_CLK 20

#define HEAD_RESET 15


// Function prototypes
void receiveEvent(size_t count);
void requestEvent(void);
void isrSW0();
void isrSW1();
void isrSW2();
void isrSW3();
void pr_byte(uint8_t val);
void allRegisters(void);

Encoder knob0 = Encoder(KNOB_0B, KNOB_0A);
Encoder knob1 = Encoder(KNOB_1B, KNOB_1A);
Encoder knob2 = Encoder(KNOB_2B, KNOB_2A);
Encoder knob3 = Encoder(KNOB_3B, KNOB_3A);

Accelerometer adxl = Accelerometer();

//LEDPWM pwm = LEDPWM(LEDPWM_DAT, LEDPWM_LAT, LEDPWM_CLK);
Adafruit_TLC5947 pwm = Adafruit_TLC5947(1, LEDPWM_CLK, LEDPWM_DAT, LEDPWM_LAT);

uint8_t _reg[RH_REG_LEN];
volatile uint8_t _read;
volatile uint8_t _mod;
volatile uint8_t _cmd;
volatile uint8_t _state;
volatile size_t _addr;

uint32_t _elapsed;
uint16_t _rate;
uint8_t _debug;

void initialize() {
  // Setup for Slave mode, address 0x44, pins 18/19, external pullups, 400kHz
  Wire.begin(I2C_SLAVE, RH_ADDR, I2C_PINS_18_19, I2C_PULLUP_EXT, RH_FREQ);
  Wire.resetBus();
  // register events
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("Setting up the Ruitar Head...");

  // init vars
  _reg[RH_REG_LEN] = {0};
  _debug = 1;
  _read = 0;
  _mod = 0;
  _cmd = 0;
  _addr = 0;
  _state = 0;
  _elapsed = 0;
  _rate = 0;

  pinMode(SW0, INPUT);
  attachInterrupt(SW0, isrSW0, CHANGE);

  pinMode(SW1, INPUT);
  attachInterrupt(SW1, isrSW1, CHANGE);

  pinMode(SW2, INPUT);
  attachInterrupt(SW2, isrSW2, CHANGE);

  pinMode(SW3, INPUT);
  attachInterrupt(SW3, isrSW3, CHANGE);

  pinMode(HEAD_RESET, INPUT_PULLUP);

  initialize();

  delay(100);

  Serial.print("Starting the ADXL...");
  adxl.begin();
  Serial.println("...OK");

  delay(100);
  Serial.print("Starting the PWM controller...");
  pwm.begin();
  Serial.println("...OK");

  delay(100);
  pinMode(LED_BUILTIN, OUTPUT);
   Serial.print("Blinking...");
  for (size_t i = 0; i < 4; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(50);
    digitalWrite(LED_BUILTIN, LOW);
    delay(50);
    digitalWrite(LED_BUILTIN, HIGH);
  }

  delay(100);

  uint16_t on = 4096;
  uint16_t off = 0;
  for (int i = 0; i < 12; i++) {
    pwm.setPWM(i, on);
    pwm.write();
    delay(50);
    pwm.setPWM(i, off);
    pwm.write();
    delay(50);
  }
  Serial.println("...OK");

  Serial.println("...finished");
}

uint32_t indicateReset = 0;

void loop() {

//  Serial.println("OK");
//  delay(1000);

  uint32_t start = micros();

  // Always read the ADXL and poll the knobs and buttons
  adxl.read(&_reg[RH_ACCLX]);

  _reg[RH_K0CNT] = (int8_t) knob0.read() / 4;
  _reg[RH_K1CNT] = (int8_t) knob1.read() / 4;
  _reg[RH_K2CNT] = (int8_t) knob2.read() / 4;
  _reg[RH_K3CNT] = (int8_t) knob3.read() / 4;
  _reg[RH_STATE] = _state;

  if (_read) {
    // Values have been read... reset now.
    knob0.write(0);
    knob1.write(0);
    knob2.write(0);
    knob3.write(0);
    memset(&_reg[RH_K0CNT], 0, 4);
    _read = 0;
  }

  if (_mod) {
    // Write PWM Registers
   // Serial.println("Write PWM Registers:");
    for (int i = 12; i > 0; i--) {
      int ledIdx = i - 1;
      int msbIdx = (i * 2) - 1;
      int lsbIdx = (i * 2) - 2;
      uint16_t intensity = (uint16_t) ((((uint16_t) _reg[msbIdx]) << 8) | _reg[lsbIdx]);
      pwm.setPWM(ledIdx, intensity);
    }
    pwm.write();
    _mod = 0;
  }

  uint32_t elapsed = (micros() - start);
  _elapsed += elapsed;
  _rate++;
  if (_elapsed > 500000) {
    _reg[RH_RFRSH] = _rate >> 8;
    _reg[RH_RFRSH + 1] = (uint8_t) _rate;
    _elapsed = 0;
    _rate = 0;
    if (_debug) {
      allRegisters();
    }
  }

}

//
// handle Rx Event (incoming I2C request/data)
//
void receiveEvent(size_t count) {
  if (count) {
    // grab command
    _cmd = Wire.readByte();

    Serial.print("Got CMD: ");
    Serial.println(_cmd);

    count--;
    switch (_cmd) {
    case RH_WRITE:
      _addr = Wire.readByte();         // grab _addr
      count--;
      if (count && (_addr + count) < RH_STATE) { // STATE is the RW Boundary register
        Wire.read(&_reg[_addr], count); // copy Rx data to register buffer
        _mod = 1;
      }
      break;

    case RH_READ:
      _addr = Wire.readByte();                // grab _addr
      break;
    }
  }
}

//
// handle Tx Event (outgoing I2C data)
//
void requestEvent(void) {
  switch (_cmd) {
  case RH_READ:
    //Serial.println("HEAD Recieved READ command");
    Wire.write(&_reg[_addr], RH_REG_LEN - _addr); // fill Tx buffer (from _addr location to end of mem)
    break;
  }
}

void isrSW0() {
  _state = (_state & ~(1 << RH_SW0BIT)) | (digitalReadFast(SW0) << RH_SW0BIT);
}

void isrSW1() {
  _state = (_state & ~(1 << RH_SW1BIT)) | (digitalReadFast(SW1) << RH_SW1BIT);
}

void isrSW2() {
  _state = (_state & ~(1 << RH_SW2BIT)) | (digitalReadFast(SW2) << RH_SW2BIT);
}

void isrSW3() {
  _state = (_state & ~(1 << RH_SW3BIT)) | (digitalReadFast(SW3) << RH_SW3BIT);
}

void pr_byte(uint8_t val) {
  int i;
  Serial.print("B");
  for (i = 7; i >= 0; i--) {
    Serial.print(val >> i & 1, BIN);
  }
}

void allRegisters(void) {
  Serial.println("#### Registers ####");
  Serial.print("K0LEDR - RW - ");
  Serial.print(RH_K0LEDR, HEX);
  Serial.print(" - ");
  Serial.println(
      (uint16_t) ((((uint16_t) _reg[RH_K0LEDR + 1]) << 8) | _reg[RH_K0LEDR]));
  Serial.print("K0LEDG - RW - ");
  Serial.print(RH_K0LEDG, HEX);
  Serial.print(" - ");
  Serial.println(
      (uint16_t) ((((uint16_t) _reg[RH_K0LEDG + 1]) << 8) | _reg[RH_K0LEDG]));
  Serial.print("K0LEDB - RW - ");
  Serial.print(RH_K0LEDB, HEX);
  Serial.print(" - ");
  Serial.println(
      (uint16_t) ((((uint16_t) _reg[RH_K0LEDB + 1]) << 8) | _reg[RH_K0LEDB]));

  Serial.print("K1LEDR - RW - ");
  Serial.print(RH_K1LEDR, HEX);
  Serial.print(" - ");
  Serial.println(((((int16_t) _reg[RH_K1LEDR + 1]) << 8) | _reg[RH_K1LEDR]));
  Serial.print("K1LEDG - RW - ");
  Serial.print(RH_K1LEDG, HEX);
  Serial.print(" - ");
  Serial.println(((((int16_t) _reg[RH_K1LEDG + 1]) << 8) | _reg[RH_K1LEDG]));
  Serial.print("K1LEDB - RW - ");
  Serial.print(RH_K1LEDB, HEX);
  Serial.print(" - ");
  Serial.println(((((int16_t) _reg[RH_K1LEDB + 1]) << 8) | _reg[RH_K1LEDB]));

  Serial.print("K2LEDR - RW - ");
  Serial.print(RH_K2LEDR, HEX);
  Serial.print(" - ");
  Serial.println(((((int16_t) _reg[RH_K2LEDR + 1]) << 8) | _reg[RH_K2LEDR]));
  Serial.print("K2LEDG - RW - ");
  Serial.print(RH_K2LEDG, HEX);
  Serial.print(" - ");
  Serial.println(((((int16_t) _reg[RH_K2LEDG + 1]) << 8) | _reg[RH_K2LEDG]));
  Serial.print("K2LEDB - RW - ");
  Serial.print(RH_K2LEDB, HEX);
  Serial.print(" - ");
  Serial.println(((((int16_t) _reg[RH_K2LEDB + 1]) << 8) | _reg[RH_K2LEDB]));

  Serial.print("K3LEDR - RW - ");
  Serial.print(RH_K3LEDR, HEX);
  Serial.print(" - ");
  Serial.println(((((int16_t) _reg[RH_K3LEDR + 1]) << 8) | _reg[RH_K3LEDR]));
  Serial.print("K3LEDG - RW - ");
  Serial.print(RH_K3LEDG, HEX);
  Serial.print(" - ");
  Serial.println(((((int16_t) _reg[RH_K3LEDG + 1]) << 8) | _reg[RH_K3LEDG]));
  Serial.print("K3LEDB - RW - ");
  Serial.print(RH_K3LEDB, HEX);
  Serial.print(" - ");
  Serial.println(((((int16_t) _reg[RH_K3LEDB + 1]) << 8) | _reg[RH_K3LEDB]));

  Serial.print("FLAGS - RW - ");
  Serial.print(RH_FLAGS, HEX);
  Serial.print(" - ");
  pr_byte(_reg[RH_FLAGS]);
  Serial.println();

  Serial.print("STATE - R0 - ");
  Serial.print(RH_STATE, HEX);
  Serial.print(" - ");
  pr_byte(_reg[RH_STATE]);
  Serial.println();

  Serial.print("K0CNT - R0 - ");
  Serial.print(RH_K0CNT, HEX);
  Serial.print(" - ");
  Serial.println((int8_t)_reg[RH_K0CNT]);

  Serial.print("K1CNT - R0 - ");
  Serial.print(RH_K1CNT, HEX);
  Serial.print(" - ");
  Serial.println((int8_t)_reg[RH_K1CNT]);

  Serial.print("K2CNT - R0 - ");
  Serial.print(RH_K2CNT, HEX);
  Serial.print(" - ");
  Serial.println((int8_t)_reg[RH_K2CNT]);

  Serial.print("K3CNT - R0 - ");
  Serial.print(RH_K3CNT, HEX);
  Serial.print(" - ");
  Serial.println((int8_t)_reg[RH_K3CNT]);

  Serial.print("ACCLX - R0 - ");
  Serial.print(RH_ACCLX, HEX);
  Serial.print(" - ");
  Serial.println(
      (int16_t) ((((int16_t) _reg[RH_ACCLX + 1]) << 8) | _reg[RH_ACCLX]));
  Serial.print("ACCLY - R0 - ");
  Serial.print(RH_ACCLY, HEX);
  Serial.print(" - ");
  Serial.println(
      (int16_t) ((((int16_t) _reg[RH_ACCLY + 1]) << 8) | _reg[RH_ACCLY]));
  Serial.print("ACCLZ - R0 - ");
  Serial.print(RH_ACCLZ, HEX);
  Serial.print(" - ");
  Serial.println(
      (int16_t) ((((int16_t) _reg[RH_ACCLZ + 1]) << 8) | _reg[RH_ACCLZ]));

  Serial.print("RFRSH - R0 - ");
  Serial.print(RH_RFRSH, HEX);
  Serial.print(" - ");
  Serial.print(((((int16_t) _reg[RH_RFRSH + 1]) << 8) | _reg[RH_RFRSH]));
  Serial.println("Hz");
  Serial.println("###################");

}
