#include <SenseBME280.h>


SenseBME280::SenseBME280() :
  ESensorDevice(),
  BME280() {
  Celsius = NoValue;
  Humidity = NoValue;
  Pressure = NoValue;
}

  
bool SenseBME280::beginI2C(uint8_t address) {
  settings.I2CAddress = address;
  if (! BME280::beginI2C())
    return false;
  init();
  return true;
}


bool SenseBME280::beginI2C(TwoWire &wire, uint8_t address) {
  settings.I2CAddress = address;
  if (! BME280::beginI2C(wire))
    return false;
  init();
  return true;
}


bool SenseBME280::beginSPI(uint8_t cs_pin) {
  if (! BME280::beginSPI(cs_pin))
    return false;
  init();
  return true;
}


void SenseBME280::init() {
  uint8_t chip_id = readRegister(BME280_CHIP_ID_REG);
  switch (chip_id) {
  case 0x58: setChip("BMP280"); break;
  case 0x60: setChip("BME280"); break;
  }
  setIdentifier("");
  setFilter(0); // 0 (off) to 4. Filter coefficient. Table 28 in data sheet.
  setStandbyTime(1); // 0 to 7 valid. Time between readings. Table 27 in data sheet.
  setTempOverSample(1); // powers of two from 0 to 16 are valid. 0 disables temp sensing. Table 24 in data sheet.
  setPressureOverSample(1); // powers of two from 0 to 16 are valid. 0 disables pressure sensing. Table 23 in data sheet.
  setHumidityOverSample(1); // powers of two from 0 to 16 are valid. 0 disables humidity sensing. table 19 in data sheet.
  setMode(MODE_SLEEP); // power down
}


bool SenseBME280::available() {
  return (strlen(chip()) > 0);
}


void SenseBME280::requestData() {
  setMode(MODE_FORCED); // wake up sensor and take reading
}


unsigned long SenseBME280::delayTime() const
{
  return 50;  // this is generous, <10 for no oversampling , <40 for 16x oversampling
}


void SenseBME280::getData() {
  BME280_SensorMeasurements measurements;
  readAllMeasurements(&measurements, 0);
  Celsius = measurements.temperature;
  Humidity = 0.01*measurements.humidity;
  Pressure = measurements.pressure;
}


TemperatureBME280::TemperatureBME280(SenseBME280 *bme, ESensors *sensors)
  : ESensorValue<SenseBME280>(bme, sensors,
			      "temperature", "T", "ºC", "%.2f", 0.01) {
}


float TemperatureBME280::reading() const {
  return SDC->temperature();
}


HumidityBME280::HumidityBME280(SenseBME280 *bme, ESensors *sensors)
  : ESensorValue<SenseBME280>(bme, sensors,
			      "humidity", "RH", "", "%.3f", 0.03) {
}


float HumidityBME280::reading() const {
  return SDC->humidity();
}


PressureBME280::PressureBME280(SenseBME280 *bme, ESensors *sensors)
  : ESensorValue<SenseBME280>(bme, sensors,
			      "pressure", "P", "Pa", "%.0f", 3.3) {
}


float PressureBME280::reading() const {
  return SDC->pressure();
}

