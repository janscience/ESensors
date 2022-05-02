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


void Sensor::parseFormat(char *prefix, int *width,
			 int *decimals, char *ftype) const {
  *prefix = '\0';
  *width = -1;
  *decimals = -1;
  *ftype = '\0';
  const char *sp = Format;
  // percent:
  if (*sp != '%')
    return;
  ++sp;
  // prefix:
  while (*sp == '0' || *sp == '+' || *sp == '-')
    *(prefix++) = *(sp++);
  *prefix = '\0';
  // width:
  char ws[10];
  char *wp = ws;
  while (isdigit(*sp))
    *(wp++) = *(sp++);
  *wp = '\0';
  if (strlen(ws) > 0)
    *width = atoi(ws);
  // decimals:
  if (*sp == '.') {
    ++sp;
    char *wp = ws;
    while (isdigit(*sp))
      *(wp++) = *(sp++);
    *wp = '\0';
    if (strlen(ws) > 0)
      *decimals = atoi(ws);
  }
  // format type:
  while (*sp != '\0')
    *(ftype++) = *(sp++);
  *ftype = '\0';
}


void Sensor::adaptFormat(int decimals) {
  // parse format string:
  char fpref[10];
  int width;
  int decis;
  char ftype[10];
  parseFormat(fpref, &width, &decis, ftype);
  // adapt format:
  if (strcmp(ftype, "f") == 0) {
    int org_decis = decis;
    if (decis >= 0) {
      decis += decimals;
      if (decis < 0)
	decis = 0;
    }
    if (width >= 0) {
      if (org_decis > 0 && decis == 0)
	width--;
      else if (org_decis == 0 && decis > 0)
	width++;
    }
  }
  // assemble format string:
  if (width >= 0 && decis >= 0)
    sprintf(Format, "%%%s%d.%d%s", fpref, width, decis, ftype);
  else if (width >= 0)
    sprintf(Format, "%%%s%d%s", fpref, width, ftype);
  else if (decis >= 0)
    sprintf(Format, "%%%s.%d%s", fpref, decis, ftype);
  else
    sprintf(Format, "%%%s%s", fpref, ftype);
}


void Sensor::setSIPrefix(const char *prefix, float factor, int decimals) {
  // new unit string:
  char us[20];
  sprintf(us, "%s%s", prefix, unit());
  // set unit:
  setUnit(us, factor);
  adaptFormat(decimals);
}


void Sensor::setPercent() {
  setUnit("%", 100.0);
  adaptFormat(-2);
}


void Sensor::setKelvin() {
  setUnit("K", 1.0, 273.15);
}


void Sensor::setFahrenheit() {
  setUnit("F", 9.0/5.0, 32.0);
}


void Sensor::setBar() {
  setUnit("bar", 1e-5);
  adaptFormat(5);
}


void Sensor::setMilliBar() {
  setUnit("mbar", 0.01);
  adaptFormat(2);
}


void Sensor::setAt() {
  setUnit("at", 0.0000101971621298);
  adaptFormat(5);
}


void Sensor::setAtm() {
  setUnit("atm", 0.00000986923266716);
  adaptFormat(5);
}


void Sensor::setMMHg() {
  setUnit("mmHg", 0.00750061575846);
  adaptFormat(2);
}


void Sensor::setPSI() {
  setUnit("psi", 0.00014503773773);
  adaptFormat(4);
}


void Sensor::setTorr() {
  setUnit("torr", 0.00750061682704);
  adaptFormat(2);
}

