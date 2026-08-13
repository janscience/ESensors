#include <VoltageADC.h>


VoltageADC::VoltageADC(ESensors *sensors, int pin, float maxvolt) :
  ESensor(sensors, "voltage", "V", "V", "%.4f"),
  Bits(10),
  Averaging(4),
  BitStr("10"),
  AvrgStr("4") {
  setInternBus();
  setChip("ADC");
  add("Bits", BitStr);
  add("Averaging", AvrgStr);
  begin(pin, maxvolt);
}


void VoltageADC::begin(int pin, float maxvolt) {
  MaxVoltage = maxvolt;
  Voltage = NoValue;
  if (pin >= 0) {
    setInternBus(pin);
    pinMode(pin, INPUT);
    analogReadResolution(Bits);
    char ident[8];
    sprintf(ident, "ADC-%u", pin);
    setIdentifier(ident);
    sprintf(BitStr, "%u", Bits);
    setAveraging(Averaging);
    MaxInt = 1 << Bits;
    setResolution(MaxVoltage/MaxInt);
    MaxInt--;
  }
}


bool VoltageADC::available() const {
  return (Pin >= 0);
}


void VoltageADC::getData() {
  if (Pin < 0)
    return;
  int r = analogRead(Pin);
  Voltage = MaxVoltage*r/MaxInt;
}


float VoltageADC::reading() const {
  return Voltage;
}


void VoltageADC::setAveraging(uint8_t avrg) {
  if ((avrg == 1) || (avrg == 4) || (avrg == 8) || (avrg == 16) || (avrg == 32)) {
    Averaging = avrg;
    analogReadAveraging(Averaging);
    sprintf(AvrgStr, "%u", Averaging);
  }
}
