#include <ESensorDevice.h>


ESensorDevice::ESensorDevice() :
  Chip(""),
  Identifier(""),
  Measuring(false),
  Retrieving(false),
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
  Retrieving = true;
}


void ESensorDevice::requestData() {
}


bool ESensorDevice::retrieve(unsigned long time) {
  if (!Measuring or !Retrieving)
    return true;
  bool r = retrieveData(time);
  if (r)
    Retrieving = false;
  return r;
}


bool ESensorDevice::retrieveData(unsigned long time) {
  return true;
}


void ESensorDevice::get() {
  if (!Measuring)
    return;
  getData();
  TimeStamp = now();
  Measuring = false;
  Retrieving = false;
}


void ESensorDevice::read() {
  request();
  elapsedMillis time = 0;
  while (time < delayTime()) {
    unsigned long delaytime = time;
    if (retrieve(delaytime))
      break;
  }
  if (time < delayTime())
    delay(delayTime() - time);
  get();
}


time_t ESensorDevice::timeStamp() const {
  return TimeStamp;
}
