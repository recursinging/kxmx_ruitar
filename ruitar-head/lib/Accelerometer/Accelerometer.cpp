#include "Accelerometer.h"

Accelerometer::Accelerometer() {
}

// destructor
Accelerometer::~Accelerometer() {
}

void Accelerometer::begin() {
  SPI.begin();
  SPI.setDataMode(SPI_MODE3);

  // Hardware mistake - use pin 14 instead of 13 for SCK
  SPI.setSCK(14);
  pinMode(CS, OUTPUT);
  digitalWrite(CS, HIGH);
  SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE3));

  // Set the Accelerometer data range
  //writeRegister(DATA_FORMAT, 0x00); // 2G
  //writeRegister(DATA_FORMAT, 0x01); // 4G
  writeRegister(DATA_FORMAT, 0x02); // 8G
  //writeRegister(DATA_FORMAT, 0x03); // 16G

  // Disable interrupts
  writeRegister(INT_ENABLE, 0x00);

  // Put the Accelerometer into Measurement Mode by writing 0x08 to the POWER_CTL register.
  writeRegister(POWER_CTL, 0x08);

  // Set the data rate register
  // writeRegister(BW_RATE, 0x0A); // 100Hz
  writeRegister(BW_RATE, 0x0D);  // 800Hz
  //writeRegister(BW_RATE, 0x0F);  // 3200hz

  // Clear the interrupts from the INT_SOURCE register.
  readRegister(INT_SOURCE, 1, _buff);
}

void Accelerometer::read(uint8_t* xyz) {
  readRegister(DATAX0, 6, xyz);
}

void Accelerometer::read(uint16_t* x, uint16_t* y, uint16_t* z) {
  //Reading 6 bytes of data starting at register DATAX0 will retrieve the x,y and z acceleration values from the Accelerometer.
  //The results of the read operation will get stored to the _buff[] buffer.
  readRegister(DATAX0, 6, _buff);

  // Each Axis @ All g Ranges: 10 Bit Resolution (2 Bytes)
  *x = (int16_t) ((((int) _buff[1]) << 8) | _buff[0]);
  *y = (int16_t) ((((int) _buff[3]) << 8) | _buff[2]);
  *z = (int16_t) ((((int) _buff[5]) << 8) | _buff[4]);

}

void Accelerometer::writeRegister(uint8_t registerAddress, uint8_t value) {
  digitalWrite(CS, LOW);
  SPI.transfer(registerAddress);
  SPI.transfer(value);
  digitalWrite(CS, HIGH);
}

void Accelerometer::readRegister(uint8_t registerAddress, uint8_t numBytes,
    uint8_t * values) {

  //Since we're performing a read operation, the most significant bit of the register address should be set.
  uint8_t address = 0x80 | registerAddress;

  //If we're doing a multi-byte read, bit 6 needs to be set as well.
  if (numBytes > 1) {
    address = address | 0x40;
  }

  digitalWrite(CS, LOW);
  SPI.transfer(address);
  for (uint8_t i = 0; i < numBytes; i++) {
    values[i] = SPI.transfer(0x00);
  }
  digitalWrite(CS, HIGH);
}

/********************************************************************/
/*                                                                  */
void print_byte(byte val){
  int i;
  Serial.print("B");
  for(i=7; i>=0; i--){
    Serial.print(val >> i & 1, BIN);
  }
}

// Print Register Values to Serial Output =
// Can be used to Manually Check the Current Configuration of Device
void Accelerometer::printAllRegister() {
  byte _b;
  Serial.print("0x00: ");
  readRegister(0x00, 1, &_b);
  print_byte(_b);
  Serial.println("");
  int i;
  for (i=29;i<=57;i++){
    Serial.print("0x");
    Serial.print(i, HEX);
    Serial.print(": ");
    readRegister(i, 1, &_b);
    print_byte(_b);
    Serial.println("");
  }
}


