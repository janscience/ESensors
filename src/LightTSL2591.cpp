#include <LightTSL2591.h>


LightTSL2591::LightTSL2591() :
  SensorDevice(),
  TSL2591TwoWire() {
  memset(Chip, 0, sizeof(Chip));
  memset(ID, 0, sizeof(ID));
  Delay = 130;
  IrradianceFull = NoValue;
  IrradianceIR = NoValue;
  IrradianceVisible = NoValue;
  Channel0 = 0;
  Channel1 = 0;
}


LightTSL2591::LightTSL2591(TwoWire *wire) :
  SensorDevice(),
  TSL2591TwoWire(wire) {
  memset(Chip, 0, sizeof(Chip));
  memset(ID, 0, sizeof(ID));
  Delay = 130;
  IrradianceFull = NoValue;
  IrradianceIR = NoValue;
  IrradianceVisible = NoValue;
  Channel0 = 0;
  Channel1 = 0;
}

  
bool LightTSL2591::begin() {
  if (! TSL2591TwoWire::begin() &&
      ! TSL2591TwoWire::begin(&Wire))
    return false;
  init();
  return true;
}

  
bool LightTSL2591::begin(TwoWire &wire) {
  if (! TSL2591TwoWire::begin(&wire))
    return false;
  init();
  return true;
}


void LightTSL2591::init() {
  strcpy(Chip, "TSL2591");
  sprintf(ID, "%02X", getID());
  resetToDefaults();
  setGain(TSL2591MI::TSL2591_GAIN_HIGH);
  // Example measurement with LED white light and 100ms integration time:
  // gain | channel0 | channel1 | scale
  // LOW  |    59    |    11    |   1/1
  // MED  |  1403    |   253    |  24/23
  // HIGH | 24200    |  4280    | 410/390
  //
  // Example measurement with LED white light and 400ms integration time:
  // gain | channel0 | channel1 | scale
  // LOW  |   146    |    27    |   1/1
  // MED  |  3478    |   628    |  24/23
  // HIGH | 60100    | 10610    | 412/393
  
  setIntegrationTime(TSL2591MI::TSL2591_INTEGRATION_TIME_400ms);
  // Example measurement with LED white light and medium gain:
  // inttime | channel0 | channel1 | scale
  // 100ms   |      711 |      129 |    1/1
  // 200ms   |     1407 |      254 | 1.98/1.97
  // 300ms   |     2100 |      380 | 2.95/2.95
  //
  // Example measurement with LED white light and low gain:
  // inttime | channel0 | channel1 | scale
  // 100ms   |       29 |        6 |    1/1 
  // 200ms   |       59 |       11 | 2.03/1.83
  // 300ms   |       88 |       16 | 3.03/2.67
  
  setALSEnabled(false);
  setPowerOn(false);
}


bool LightTSL2591::available() {
  return (Chip[0] != '\0');
}


void LightTSL2591::requestData() {
  // power up and enable:
  measure();
}


unsigned long LightTSL2591::delay() const
{
  return Delay;
}


bool LightTSL2591::setIntegrationTime(uint8_t time) {
  bool success = TSL2591MI::setIntegrationTime(time);
  time = TSL2591MI::getIntegrationTime();
  Delay = (time+1)*100 + 30;
  return success;
}


bool LightTSL2591::setGain(uint8_t gain) {
  return TSL2591MI::setGain(gain);
}


void LightTSL2591::setTemperature(double temperature) {
  setSensorTemperature(temperature);
}


void LightTSL2591::readData() {
  if (hasValue()) {
    setChannel(TSL2591MI::TSL2591_CHANNEL_0);
    Channel0 = getValue();
    IrradianceFull = getIrradiance();
    setChannel(TSL2591MI::TSL2591_CHANNEL_1);
    Channel1 = getValue();
    IrradianceIR = getIrradiance();
    IrradianceVisible = IrradianceFull - IrradianceIR;
  }
  // back to sleep:
  setALSEnabled(false);
  setPowerOn(false);
}


SensorTSL2591::SensorTSL2591(LightTSL2591 *tsl, Sensors *sensors,
			     const char *name, const char *symbol,
			     const char *unit, const char *format)
  : Sensor(sensors, name, symbol, unit, format),
    TSL(tsl) {
}


float SensorTSL2591::resolution() const {
  return Factor*0.01;  // XXXX Set to right value!
}


void SensorTSL2591::requestData() {
  TSL->request();
}


void SensorTSL2591::readData() {
  TSL->read();
}


Channel0TSL2591::Channel0TSL2591(LightTSL2591 *tsl, Sensors *sensors)
  : SensorTSL2591(tsl, sensors, "channel0", "C0", "counts", "%.0f") {
}


float Channel0TSL2591::reading() const {
  return TSL->channel0();
}


Channel1TSL2591::Channel1TSL2591(LightTSL2591 *tsl, Sensors *sensors)
  : SensorTSL2591(tsl, sensors, "channel1", "C1", "counts", "%.0f") {
}


float Channel1TSL2591::reading() const {
  return TSL->channel1();
}


IrradianceFullTSL2591::IrradianceFullTSL2591(LightTSL2591 *tsl, Sensors *sensors)
  : SensorTSL2591(tsl, sensors, "irradiance full", "E_e full", "W/cm^2", "%.3f") {
}


float IrradianceFullTSL2591::reading() const {
  return TSL->irradianceFull();
}


IrradianceIRTSL2591::IrradianceIRTSL2591(LightTSL2591 *tsl, Sensors *sensors)
  : SensorTSL2591(tsl, sensors, "irradiance IR", "E_e IR", "W/cm^2", "%.3f") {
}


float IrradianceIRTSL2591::reading() const {
  return TSL->irradianceIR();
}


IrradianceVisibleTSL2591::IrradianceVisibleTSL2591(LightTSL2591 *tsl, Sensors *sensors)
  : SensorTSL2591(tsl, sensors, "irradiance visible", "E_e vis", "W/cm^2", "%.3f") {
}


float IrradianceVisibleTSL2591::reading() const {
  return TSL->irradianceVisible();
}

