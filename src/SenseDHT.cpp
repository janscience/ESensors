#include <SenseDHT.h>


SenseDHT::SenseDHT(uint8_t pin, uint8_t type) :
  ESensorDevice(),
  DHT_Async(pin, type) {
  Celsius = NoValue;
  Humidity = NoValue;
}


bool SenseDHT::available() {
  return true;
}


void SenseDHT::requestData() {
}


unsigned long SenseDHT::delayTime() const
{
  return 2000;
}


void SenseDHT::getData() {
  while (!measure(&Celsius, &Humidity)) {};
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

