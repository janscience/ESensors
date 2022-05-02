#include <Sensors.h>
#include <Sensor.h>


Sensor::Sensor() :
  SensorDevice(),
  Name(""),
  Symbol(""),
  BasicUnit(""),
  Unit(""),
  Format("%.2f"),
  Factor(1.0),
  Offset(0.0),
  Resolution(1.0) {
}


Sensor::Sensor(const char *name, const char *symbol, const char *unit,
	       const char *format, float resolution) :
  Sensor() {
  strcpy(BasicUnit, unit);
  setName(name);
  setSymbol(symbol);
  setUnit(unit, 1.0, 0.0);
  setFormat(format);
  setResolution(resolution);
}


Sensor::Sensor(Sensors *sensors, const char *name, const char *symbol,
	       const char *unit, const char *format, float resolution) :
  Sensor(name, symbol, unit, format, resolution) {
  if (sensors != 0)
    sensors->addSensor(*this);
}


const char* Sensor::name() const {
  return Name;
}


void Sensor::setName(const char *name) {
  strcpy(Name, name);
}


void Sensor::setName(const char *name, const char *symbol) {
  strcpy(Name, name);
  strcpy(Symbol, symbol);
}


const char* Sensor::symbol() const {
  return Symbol;
}


void Sensor::setSymbol(const char *symbol) {
  strcpy(Symbol, symbol);
}


const char* Sensor::basicUnit() const {
  return BasicUnit;
}


const char* Sensor::unit() const {
  return Unit;
}


void Sensor::setUnit(const char *unit, float factor, float offset) {
  strcpy(Unit, unit);
  Factor = factor;
  Offset = offset;
}


void Sensor::setUnit(const char *unit, float factor, float offset,
		     const char *format) {
  strcpy(Unit, unit);
  Factor = factor;
  Offset = offset;
  strcpy(Format, format);
}


void Sensor::setUnit(const char *unit, float factor, const char *format) {
  strcpy(Unit, unit);
  Factor = factor;
  Offset = 0.0;
  strcpy(Format, format);
}


const char* Sensor::format() const {
  return Format;
}


void Sensor::setFormat(const char *format) {
  strcpy(Format, format);
}


void Sensor::setResolution(float resolution) {
  Resolution = resolution;
}


float Sensor::resolution() const {
  return Factor*Resolution;
}


int Sensor::resolutionStr(char *s) const {
  return sprintf(s, Format, resolution());
}


void Sensor::report() {
  if (available()) {
    char rs[10];
    resolutionStr(rs);
    Serial.printf("%s %s", name(), symbol());
    if (strlen(unit()) > 0)
      Serial.printf(" (%s)", unit());
    Serial.print(":");
    if (strlen(chip()) > 0)
      Serial.printf("\t on %s device", chip());
    if (strlen(identifier()) > 0)
      Serial.printf(" (ID: %s)", identifier());
    Serial.printf(" at a resolution of %s%s.\n", rs, unit());
  }
}


float Sensor::value() const {
  return Factor*reading() + Offset;
}


int Sensor::valueStr(char *s) const {
  return sprintf(s, Format, value());
}


float Sensor::read() {
  SensorDevice::read();
  return value();
}


void Sensor::setSIPrefix(const char *prefix, float factor, int decimals) {
  char us[20];
  sprintf(us, "%s%s", prefix, unit());
  char fs[10];
  strcpy(fs, format());
  char *pp = strrchr(fs, '.');
  if (pp != 0 ) {
    pp++;
    int d = atoi(pp);
    d += decimals;
    if (d < 0)
      d = 0;
    *pp = '0' + d;
  }
  setUnit(us, factor, fs);
}


void Sensor::setPercent() {
  setUnit("%", 100.0, 0.0, "%5.1f");
}


void Sensor::setKelvin() {
  setUnit("K", 1.0, 273.15, "%.2f");
}


void Sensor::setFahrenheit() {
  setUnit("F", 9.0/5.0, 32.0, "%.2f");
}


void Sensor::setBar() {
  setUnit("bar", 1e-5, "%.5f");
}


void Sensor::setMilliBar() {
  setUnit("mbar", 0.01, "%.2f");
}


void Sensor::setAt() {
  setUnit("at", 0.0000101971621298, "%.5f");
}


void Sensor::setAtm() {
  setUnit("atm", 0.00000986923266716, "%.5f");
}


void Sensor::setMMHg() {
  setUnit("mmHg", 0.00750061575846, "%.2f");
}


void Sensor::setPSI() {
  setUnit("psi", 0.00014503773773, "%.4f");
}


void Sensor::setTorr() {
  setUnit("torr", 0.00750061682704, "%.2f");
}

