#include <TemperatureDS3231.h>


#define DS1307_CTRL_ID 0x68 


TemperatureDS3231::TemperatureDS3231(TwoWire &wire)
  : TemperatureDS3231(0, wire) {
}


TemperatureDS3231::TemperatureDS3231(ESensors *sensors, TwoWire &wire)
  : ESensor(sensors, "temperature-rtc", "Tc", "ºC", "%.2f", 0.25) {
  setChip("DS3231");
  begin(wire);
}


void TemperatureDS3231::begin(TwoWire &wire) {
  Celsius = NoValue;
  I2CBus = &wire;
  setI2CBus(wire, DS1307_CTRL_ID);
}


bool TemperatureDS3231::available() {
  I2CBus->beginTransmission(DS1307_CTRL_ID);
  return (I2CBus->endTransmission() == 0);
}


void TemperatureDS3231::requestData() {
  // Temperatures are read every 64s.
  // No way to influence this.
}


void TemperatureDS3231::getData() {
  Celsius = NoValue;
  I2CBus->beginTransmission(DS1307_CTRL_ID);
  I2CBus->write((uint8_t)0x11); 
  if (I2CBus->endTransmission() == 0) {
    I2CBus->requestFrom(DS1307_CTRL_ID, 2);
    if (I2CBus->available() == 2) {
      int8_t temp1 = I2CBus->read(); 
      uint8_t temp2 = I2CBus->read() >> 6;
      Celsius = temp1 + 0.25*temp2;
    }
  }
}


float TemperatureDS3231::reading() const {
  return Celsius;
}

