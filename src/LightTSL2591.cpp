#include <LightTSL2591.h>


LightTSL2591::LightTSL2591(Sensors *sensors) :
  Sensor(sensors, "illuminance", "E", "lx", "%8.2f"),
  TSL2591TwoWire() {
  memset(Chip, 0, sizeof(Chip));
  memset(ID, 0, sizeof(ID));
  Delay = 130;
  IrradianceFull = NoValue;
  IrradianceIR = NoValue;
  Illuminance = NoValue;
  C0DATA = 0;
  C1DATA = 0;
  MaxData = 0xFFFF;
  AutoGain = false;
  Gain = 0;
}


LightTSL2591::LightTSL2591(TwoWire *wire, Sensors *sensors) :
  Sensor(sensors, "illuminance", "E", "lx", "%8.2f"),
  TSL2591TwoWire(wire) {
  memset(Chip, 0, sizeof(Chip));
  memset(ID, 0, sizeof(ID));
  Delay = 130;
  IrradianceFull = NoValue;
  IrradianceIR = NoValue;
  Illuminance = NoValue;
  C0DATA = 0;
  C1DATA = 0;
  MaxData = 0xFFFF;
  AutoGain = false;
  Gain = 0;
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
  setGain(TSL2591MI::TSL2591_GAIN_LOW);
  setIntegrationTime(TSL2591MI::TSL2591_INTEGRATION_TIME_100ms);
  setALSEnabled(false);
  setPowerOn(false);
}


bool LightTSL2591::available() {
  return (Chip[0] != '\0');
}


bool LightTSL2591::setIntegrationTime(uint8_t time) {
  bool success = TSL2591MI::setIntegrationTime(time);
  time = TSL2591MI::getIntegrationTime();
  Delay = (time+1)*100 + 30;
  MaxData = time == TSL2591MI::TSL2591_INTEGRATION_TIME_100ms ? 0x8FFF : 0xFFFF;
  return success;
}


bool LightTSL2591::setGain(uint8_t gain) {
  if (gain == AUTO_GAIN) {
    AutoGain = true;
    return true;
  }
  AutoGain = false;
  return TSL2591MI::setGain(gain);
}


void LightTSL2591::setTemperature(double temperature) {
  setSensorTemperature(temperature);
}


float LightTSL2591::resolution() const {
  return Factor*1.0;  // XXXX Set to right value!
}


void LightTSL2591::requestData() {
  // power up and enable:
  measure();
}


unsigned long LightTSL2591::delay() const
{
  return Delay;
}


void LightTSL2591::getData() {
  if (hasValue()) {
    setChannel(TSL2591MI::TSL2591_CHANNEL_0);
    C0DATA = getValue();
    IrradianceFull = getIrradiance();
    Illuminance = getBrightness();
    setChannel(TSL2591MI::TSL2591_CHANNEL_1);
    C1DATA = getValue();
    IrradianceIR = getIrradiance();
    Gain = TSL2591MI::getGain();
    if (AutoGain) {
      if ((C0DATA < 64 || C1DATA < 64) &&
	  Gain < TSL2591MI::TSL2591_GAIN_MAX)
	setGain(Gain+1);
      else if ((C0DATA > (MaxData >> 2) || C1DATA > (MaxData >> 2)) &&
	  Gain > 0)
	setGain(Gain-1);
      AutoGain = true;
    }
  }
  // back to sleep:
  setALSEnabled(false);
  setPowerOn(false);
}


float LightTSL2591::IRRatio() const {
  return C0DATA > 0 ? float(C1DATA)/float(C0DATA) : -INFINITY;
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


void SensorTSL2591::getData() {
  TSL->get();
}


Channel0TSL2591::Channel0TSL2591(LightTSL2591 *tsl, Sensors *sensors)
  : SensorTSL2591(tsl, sensors, "channel0", "C0", "counts", "%5.0f") {
}


float Channel0TSL2591::reading() const {
  return TSL->channel0();
}


Channel1TSL2591::Channel1TSL2591(LightTSL2591 *tsl, Sensors *sensors)
  : SensorTSL2591(tsl, sensors, "channel1", "C1", "counts", "%5.0f") {
}


float Channel1TSL2591::reading() const {
  return TSL->channel1();
}


GainTSL2591::GainTSL2591(LightTSL2591 *tsl, Sensors *sensors)
  : SensorTSL2591(tsl, sensors, "gain", "g", "", "%1.0f") {
}


float GainTSL2591::reading() const {
  return TSL->gain();
}


IRRatioTSL2591::IRRatioTSL2591(LightTSL2591 *tsl, Sensors *sensors)
  : SensorTSL2591(tsl, sensors, "IRratio", "R", "", "%4.2f") {
}


float IRRatioTSL2591::reading() const {
  return TSL->IRRatio();
}


IrradianceFullTSL2591::IrradianceFullTSL2591(LightTSL2591 *tsl, Sensors *sensors)
  : SensorTSL2591(tsl, sensors, "irradiance full", "E_e full", "W/cm^2", "%8.3f") {
}


float IrradianceFullTSL2591::reading() const {
  return TSL->irradianceFull();
}


IrradianceIRTSL2591::IrradianceIRTSL2591(LightTSL2591 *tsl, Sensors *sensors)
  : SensorTSL2591(tsl, sensors, "irradiance IR", "E_e IR", "W/cm^2", "%8.3f") {
}


float IrradianceIRTSL2591::reading() const {
  return TSL->irradianceIR();
}


IrradianceVisibleTSL2591::IrradianceVisibleTSL2591(LightTSL2591 *tsl, Sensors *sensors)
  : SensorTSL2591(tsl, sensors, "irradiance visible", "E_e vis", "W/cm^2", "%8.3f") {
}


float IrradianceVisibleTSL2591::reading() const {
  return TSL->irradianceVisible();
}

