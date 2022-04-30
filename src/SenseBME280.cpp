#include <SenseBME280.h>


SenseBME280::SenseBME280() :
  SensorDevice(),
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
  Humidity = measurements.humidity;
  Pressure = measurements.pressure;
}


TemperatureBME280::TemperatureBME280(SenseBME280 *bme, Sensors *sensors)
  : SensorValue<SenseBME280>(bme, sensors,
			     "temperature", "T", "ºC", "%.2f", 0.01) {
}


float TemperatureBME280::reading() const {
  return SDC->temperature();
}


HumidityBME280::HumidityBME280(SenseBME280 *bme, Sensors *sensors)
  : SensorValue<SenseBME280>(bme, sensors,
			     "humidity", "RH", "%", "%.1f", 0.07) {
}


float HumidityBME280::reading() const {
  return SDC->humidity();
}


AbsoluteHumidityBME280::AbsoluteHumidityBME280(SenseBME280 *bme,
					       Sensors *sensors)
  : SensorValue<SenseBME280>(bme, sensors,
			     "absolute humidity", "H", "g/m^3", "%.1f", 0.1) {
}


float AbsoluteHumidityBME280::reading() const {
  // from https://github.com/finitespace/BME280/blob/master/src/EnvironmentCalculations.cpp
  float temp = SDC->temperature();
  float humidity = SDC->humidity();
  const float mw = 18.01534; 	// molar mass of water g/mol
  const float R = 8.31447215; 	// universal gas constant J/mol/K
  temp = pow(2.718281828, (17.67 * temp) / (temp + 243.5));
  return (6.112 * temp * humidity * mw)/((273.15 + temp) * R);
}


DewPointBME280::DewPointBME280(SenseBME280 *bme, Sensors *sensors)
  : SensorValue<SenseBME280>(bme, sensors,
			     "dew point", "Tdp", "ºC", "%.1f", 0.35) {
}


float DewPointBME280::reading() const {
  // https://en.wikipedia.org/wiki/Dew_point
  float temp = SDC->temperature();
  float humidity = SDC->humidity();
  const float b = 17.62;
  const float c = 243.12;
  float gamma = log(0.01*humidity) + (b * temp)/(c + temp);
  return c * gamma/(b - gamma);
}


PressureBME280::PressureBME280(SenseBME280 *bme, Sensors *sensors)
  : SensorValue<SenseBME280>(bme, sensors,
			     "pressure", "P", "Pa", "%.0f", 3.3) {
}


float PressureBME280::reading() const {
  return SDC->pressure();
}


SeaLevelPressureBME280::SeaLevelPressureBME280(SenseBME280 *bme,
					       float altitude)
  : PressureBME280(bme, 0),
    Altitude(altitude) {
  setName("sea level pressure", "P0");
}


SeaLevelPressureBME280::SeaLevelPressureBME280(SenseBME280 *bme,
					       Sensors *sensors,
					       float altitude)
  : PressureBME280(bme, sensors),
    Altitude(altitude) {
  setName("sea level pressure", "P0");
}


float SeaLevelPressureBME280::reading() const {
  // see https://keisan.casio.com/exec/system/1224575267
  // derivation: https://keisan.casio.com/keisan/image/Convertpressure.pdf
  float pressure = SDC->pressure();
  float temp = SDC->temperature();
  return pressure / pow(1.0 - ((0.0065 * Altitude) / (temp + (0.0065 * Altitude) + 273.15)), 5.257);
}
