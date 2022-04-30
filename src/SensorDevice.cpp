#include <SensorDevice.h>


SensorDevice::SensorDevice() :
  Chip(""),
  Identifier(""),
  Measuring(false),
  TimeStamp(0) {
}


const char* SensorDevice::chip() const {
  return Chip;
}


void SensorDevice::setChip(const char *chip) {
  strncpy(Chip, chip, MaxStr);
}


const char* SensorDevice::identifier() const {
  return Identifier;
}


void SensorDevice::setIdentifier(const char *identifier) {
  strncpy(Identifier, identifier, MaxStr);
}


void SensorDevice::report() {
  if (available()) {
    Serial.printf("device %s", chip());
    if (strlen(identifier()) > 0)
      Serial.printf(" (ID: %s)\n", identifier());
  }
}


void SensorDevice::request() {
  if (Measuring)
    return;
  requestData();
  Measuring = true;
}


void SensorDevice::requestData() {
}


void SensorDevice::get() {
  if (!Measuring)
    return;
  getData();
  TimeStamp = now();
  Measuring = false;
}


void SensorDevice::read() {
  request();
  delay(delayTime());
  get();
}


time_t SensorDevice::timeStamp() const {
  return TimeStamp;
}
