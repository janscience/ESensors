#include <LightBH1750.h>


LightBH1750::LightBH1750(ESensors *sensors)
  : ESensor(sensors, "illuminance", "E", "lx", "%6.5g", 1.0),
    hp_BH1750() {
  DelayTime = 500;
  Illuminance = NoValue;
}

  
bool LightBH1750::begin(uint8_t address) {
  if (! hp_BH1750::begin(address))
    return false;
  init();
  return true;
}

  
bool LightBH1750::begin(TwoWire &wire, uint8_t address) {
  if (! hp_BH1750::begin(address, &wire))
    return false;
  init();
  return true;
}


void LightBH1750::init() {
  setChip("BH1750");
}


bool LightBH1750::available() {
  return (strlen(chip()) > 0);
}


void LightBH1750::requestData() {
  hp_BH1750::start();
}


unsigned long LightBH1750::delayTime() const
{
  return DelayTime;
}


void LightBH1750::getData() {
  if (hp_BH1750::hasValue()) {
    Illuminance = hp_BH1750::getLux();
    //adjustSettings(90);
  }
}

