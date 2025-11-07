#include <LightBH1750.h>


const char *LightBH1750::QualityStrings[3] = {"HIGH", "HIGH2", "LOW"};
const char *LightBH1750::AutoRangeStrings[2] = {"off", "on"};


LightBH1750::LightBH1750(ESensors *sensors)
  : ESensor(sensors, "illuminance", "E", "lx", "%6.5g", 0.113),
    hp_BH1750() {
  Illuminance = NoValue;
  RawData = 0;
  Quality = BH1750_QUALITY_HIGH;
  MTReg = 0;
  AutoRange = false;
  MTRegStr[0] = '\0';
}

  
bool LightBH1750::begin(uint8_t address) {
  if (! hp_BH1750::begin(address))
    return false;
  setI2CBus(Wire, address);
  init();
  return true;
}

  
bool LightBH1750::begin(TwoWire &wire, uint8_t address) {
  if (! hp_BH1750::begin(address, &wire))
    return false;
  setI2CBus(wire, address);
  init();
  return true;
}


void LightBH1750::init() {
  setChip("BH1750");
  setQuality(BH1750_QUALITY_HIGH);
  setMTReg(hp_BH1750::getMtreg());
  setAutoRanging(AutoRange);
}


void LightBH1750::setQuality(BH1750Quality quality) {
  hp_BH1750::setQuality(quality);
  quality = hp_BH1750::getQuality();
  const char *qstr = 0;
  if (quality == BH1750_QUALITY_HIGH)
    qstr = QualityStrings[0];
  else if (quality == BH1750_QUALITY_HIGH2)
    qstr = QualityStrings[1];
  else if (quality == BH1750_QUALITY_LOW)
    qstr = QualityStrings[2];
  add("Quality", qstr);
}


void LightBH1750::setMTReg(int mtreg) {
  hp_BH1750::writeMtreg(mtreg);
  snprintf(MTRegStr, 4, "%d", hp_BH1750::getMtreg());
  MTRegStr[3] = '\0';
  add("MTreg", MTRegStr);
}


void LightBH1750::setAutoRanging(bool autorange) {
  AutoRange = autorange;
  add("Autorange", AutoRangeStrings[AutoRange]);
}


bool LightBH1750::available() const {
  return (strlen(chip()) > 0);
}


void LightBH1750::requestData() {
  hp_BH1750::start();
}


unsigned long LightBH1750::delayTime() const
{
  return hp_BH1750::getMtregTime() + hp_BH1750::getTimeOffset() + 10;
}


void LightBH1750::getData() {
  if (hp_BH1750::hasValue()) {
    Illuminance = hp_BH1750::getLux();
    RawData = hp_BH1750::getRaw();
    Quality = hp_BH1750::getQuality();
    MTReg = hp_BH1750::getMtreg();
    if (AutoRange)
      hp_BH1750::adjustSettings(1);
  }
}


RawBH1750::RawBH1750(LightBH1750 *bh, ESensors *sensors)
  : ESensorValue<LightBH1750>(bh, sensors,
			      "raw", "d", "counts", "%5.0f", 1.0) {
}


float RawBH1750::reading() const {
  return SDev->rawData();
}


QualityBH1750::QualityBH1750(LightBH1750 *bh, ESensors *sensors)
  : ESensorValue<LightBH1750>(bh, sensors,
			      "quality", "Q", "", "%5.0f", 1.0) {
}


float QualityBH1750::reading() const {
  return SDev->quality() - 0x20;
}


TimeBH1750::TimeBH1750(LightBH1750 *bh, ESensors *sensors)
  : ESensorValue<LightBH1750>(bh, sensors,
			      "mtreg", "MT", "", "%5.0f", 1.0) {
}


float TimeBH1750::reading() const {
  return SDev->mtReg();
}

