#include <LightTSL2591.h>


LightTSL2591::LightTSL2591(TwoWire *wire) :
  SensorDevice(),
  TSL2591TwoWire(wire) {
  memset(Chip, 0, sizeof(Chip));
  IrradianceFull = NoValue;
  IrradianceIR = NoValue;
  IrradianceVisible = NoValue;
  Channel0 = 0;
  Channel1 = 0;
}

  
bool LightTSL2591::begin() {
  if (! TSL2591TwoWire::begin())
    return false;
  init();
  return true;
}


void LightTSL2591::init() {
  strcpy(Chip, "TSL2591");
  resetToDefaults();
  setGain(TSL2591MI::TSL2591_GAIN_MED);
  setIntegrationTime(TSL2591MI::TSL2591_INTEGRATION_TIME_100ms);
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
  return 410; // XXX set it to maximum integration time 
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

