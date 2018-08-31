#ifndef Accelerometer_h
#define Accelerometer_h
#include "SPI.h"

#define CS 10

//ADXL345 Register Addresses
#define DEVID   0x00  //Device ID Register
#define THRESH_TAP  0x1D  //Tap Threshold
#define OFSX    0x1E  //X-axis offset
#define OFSY    0x1F  //Y-axis offset
#define OFSZ    0x20  //Z-axis offset
#define DURATION  0x21  //Tap Duration
#define LATENT    0x22  //Tap latency
#define WINDOW    0x23  //Tap window
#define THRESH_ACT  0x24  //Activity Threshold
#define THRESH_INACT  0x25  //Inactivity Threshold
#define TIME_INACT  0x26  //Inactivity Time
#define ACT_INACT_CTL 0x27  //Axis enable control for activity and inactivity detection
#define THRESH_FF 0x28  //free-fall threshold
#define TIME_FF   0x29  //Free-Fall Time
#define TAP_AXES  0x2A  //Axis control for tap/double tap
#define ACT_TAP_STATUS  0x2B  //Source of tap/double tap

#define BW_RATE   0x2C  //Data rate and power mode control
#define POWER_CTL 0x2D  //Power Control Register
#define INT_ENABLE  0x2E  //Interrupt Enable Control
#define INT_SOURCE  0x30  //Source of interrupts
#define DATA_FORMAT 0x31  //Data format control
#define DATAX0    0x32  //X-Axis Data 0

#define DATAX1    0x33  //X-Axis Data 1
#define DATAY0    0x34  //Y-Axis Data 0
#define DATAY1    0x35  //Y-Axis Data 1
#define DATAZ0    0x36  //Z-Axis Data 0
#define DATAZ1    0x37  //Z-Axis Data 1

#define FIFO_CTL  0x38  //FIFO control
#define FIFO_STATUS 0x39  //FIFO status

/****************************** ERRORS ******************************/
#define ACCEL_OK			1		// No Error
#define ACCEL_ERROR		0		// Error Exists

#define ACCEL_NO_ERROR	0		// Initial State
#define ACCEL_READ_ERROR	1		// Accelerometer Reading Error
#define ACCEL_BAD_ARG		2		// Bad Argument

class Accelerometer {
public:
  Accelerometer();
  void begin();
  void read(uint8_t* xyz);
  void read(uint16_t* x, uint16_t* y, uint16_t* z);
  void printAllRegister();

  ~Accelerometer();
private:
  uint8_t _buff[6];   //  6 Bytes Buffer
  void readRegister(uint8_t registerAddress, uint8_t numBytes,
      uint8_t * values);
  void writeRegister(uint8_t registerAddress, uint8_t value);
};
#endif
