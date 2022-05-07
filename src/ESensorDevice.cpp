#include <ESensorDevice.h>


ESensorDevice::ESensorDevice() :
  Chip(""),
  Identifier(""),
  Measuring(false),
  TimeStamp(0) {
}


const char* ESensorDevice::chip() const {
  return Chip;
}


void ESensorDevice::setChip(const char *chip) {
  strncpy(Chip, chip, MaxStr);
}


const char* ESensorDevice::identifier() const {
  return Identifier;
}


void ESensorDevice::setIdentifier(const char *identifier) {
  strncpy(Identifier, identifier, MaxStr);
}


void ESensorDevice::report() {
  if (available()) {
    Serial.printf("device %s", chip());
    if (strlen(identifier()) > 0)
      Serial.printf(" (ID: %s)\n", identifier());
  }
}


void ESensorDevice::request() {
  if (Measuring)
    return;
  requestData();
  Measuring = true;
}


void ESensorDevice::requestData() {
}


void ESensorDevice::get() {
  if (!Measuring)
    return;
  getData();
  TimeStamp = now();
  Measuring = false;
}


void ESensorDevice::read() {
  request();
  delay(delayTime());
  get();
}


time_t ESensorDevice::timeStamp() const {
  return TimeStamp;
}
