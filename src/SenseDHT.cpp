#include <SenseDHT.h>


SenseDHT::SenseDHT(uint8_t pin, uint8_t type) :
  ESensorDevice(),
  DHT_Async(pin, type),
  Celsius(NoValue),
  Humidity(NoValue) {
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
  setSingleWireBus(pin);
}


bool SenseDHT::available() const {
  return true;
}


void SenseDHT::requestData() {
  // cooldown, idle, and begin measurement:
  for (uint8_t k=0; k<3; k++)
    measure(&Celsius, &Humidity, false);
}


unsigned long SenseDHT::delayTime() const
{
  return 300;
}


void SenseDHT::getData() {
  elapsedMillis time = 0;
  bool r = false;
  while (!r && time < 30)
    r = measure(&Celsius, &Humidity, false);
  if (r)
    Humidity *= 0.01;
}


TemperatureDHT::TemperatureDHT(SenseDHT *dht, ESensors *sensors)
  : ESensorValue<SenseDHT>(dht, sensors,
			   "temperature", "T", "ºC", "%.1f", 0.5) {
}


float TemperatureDHT::reading() const {
  return SDev->temperature();
}


HumidityDHT::HumidityDHT(SenseDHT *dht, ESensors *sensors)
  : ESensorValue<SenseDHT>(dht, sensors,
			   "humidity", "RH", "", "%.3f", 0.02) {
}


float HumidityDHT::reading() const {
  return SDev->humidity();
}
