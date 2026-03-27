#include <VoltageADC.h>


VoltageADC::VoltageADC(ESensors *sensors, uint8_t pin, float maxvolt) :
  ESensor(sensors, "voltage", "V", "V", "%.4f"),
  Bits(10) {
  setInternBus();
  begin(pin, maxvolt);
}


void VoltageADC::begin(uint8_t pin, float maxvolt) {
  Pin = pin;
  MaxVoltage = maxvolt;
  Voltage = NoValue;
  if (Pin >= 0) {
    pinMode(Pin, INPUT);
    analogReadResolution(Bits);
    analogReadAveraging(1);  // 4, 8, 16, 32
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

