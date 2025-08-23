#include <TemperatureSTS4x.h>


TemperatureSTS4x::TemperatureSTS4x(ESensors *sensors)
  : ESensor(sensors, "temperature", "T", "ºC", "%.1f", 0.2) {
  setChip("STS4x");
  Precision = STS4x_HIGH;
}


TemperatureSTS4x::TemperatureSTS4x(TwoWire &wire, STS4xAddress addr)
  : TemperatureSTS4x(0, wire, addr) {
}


TemperatureSTS4x::TemperatureSTS4x(ESensors *sensors, TwoWire &wire,
				   STS4xAddress addr)
  : TemperatureSTS4x(sensors) {
  begin(wire, addr);
}


void TemperatureSTS4x::begin(TwoWire &wire, STS4xAddress addr) {
  Celsius = NoValue;
  I2CBus = &wire;
  I2CAddr = addr;
  setI2CBus(wire, addr);
  // read serial number:
  I2CBus->beginTransmission(I2CAddr);
  I2CBus->write((uint8_t)0x89); 
  I2CBus->endTransmission();
  delay(10);
  I2CBus->requestFrom(I2CAddr, 4);
  if (I2CBus->available() == 4) {
    uint8_t s0 = I2CBus->read(); 
    uint8_t s1 = I2CBus->read(); 
    uint8_t s2 = I2CBus->read(); 
    uint8_t s3 = I2CBus->read();
    char serial[12];
    sprintf(serial, "%02X-%02X-%02X-%02X", s0, s1, s2, s3);
    setIdentifier(serial);
  };
}


bool TemperatureSTS4x::available() {
  I2CBus->beginTransmission(I2CAddr);
  return (I2CBus->endTransmission() == 0);
}


void TemperatureSTS4x::requestData() {
  I2CBus->beginTransmission(I2CAddr);
  I2CBus->write((uint8_t)Precision); 
  I2CBus->endTransmission();
}


void TemperatureSTS4x::getData() {
  Celsius = NoValue;
  I2CBus->requestFrom(I2CAddr, 2);
  if (I2CBus->available() == 2) {
    uint8_t t0 = I2CBus->read(); 
    uint8_t t1 = I2CBus->read(); 
    int16_t st = t0*256 + t1;
    Celsius = 175.0*st/65535.0 - 45.0;
  }
}


float TemperatureSTS4x::reading() const {
  return Celsius;
}


void TemperatureSTS4x::setPrecision(STS4xPrecision precision) {
  Precision = precision;
}

