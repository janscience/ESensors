/*
#include <SenseDHT.h>


SenseDHT::SenseDHT(uint8_t pin, uint8_t type) :
  ESensorDevice(),
  DHT_Async(pin, type) {
  DelayTime = 500;
  Celsius = NoValue;
  Humidity = NoValue;
  switch (type) {
  case DHT_TYPE_11:
    setChip("DHT11");
    break;
  case DHT_TYPE_12:
    setChip("DHT12");
    break;
  case DHT_TYPE_21:
    setChip("DHT21");
    break;
  case DHT_TYPE_22:
    setChip("DHT22");
    break;
  };
  char is[20];
  sprintf(is, "pin%02d", pin);
  setIdentifier(is);
}


bool SenseDHT::available() {
  return true;
}


bool SenseDHT::retrieveData(unsigned long time) {
  bool r = measure(&Celsius, &Humidity);
  if (r)
    DelayTime = time;
  return r;
}


unsigned long SenseDHT::delayTime() const
{
  return DelayTime;
}


void SenseDHT::getData() {
  measure(&Celsius, &Humidity);
}


TemperatureDHT::TemperatureDHT(SenseDHT *dht, ESensors *sensors)
  : ESensorValue<SenseDHT>(dht, sensors,
			   "temperature", "T", "ºC", "%.1f", 0.5) {
}


float TemperatureDHT::reading() const {
  return SDC->temperature();
}


HumidityDHT::HumidityDHT(SenseDHT *dht, ESensors *sensors)
  : ESensorValue<SenseDHT>(dht, sensors,
			   "humidity", "RH", "", "%.0f", 2.0) {
}


float HumidityDHT::reading() const {
  return SDC->humidity();
}

*/
