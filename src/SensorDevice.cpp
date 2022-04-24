#include <SensorDevice.h>


SensorDevice::SensorDevice() :
  Measuring(false),
  TimeStamp(0) {
}


const char* SensorDevice::chip() const {
  return "";
}


const char* SensorDevice::identifier() const {
  return "";
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


void SensorDevice::read() {
  if (!Measuring)
    return;
  readData();
  TimeStamp = now();
  Measuring = false;
}


time_t SensorDevice::timeStamp() const {
  return TimeStamp;
}
