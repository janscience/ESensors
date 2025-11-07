#include <ESensorDevice.h>


const char *ESensorDevice::BusStrings[11] = {
    "unknown",
    "intern",
    "SingleWire",   // e.g. DHT22 from Aosong Electronics
    "OneWire",      // e.g. DS18x20
    "I2C-0",
    "I2C-1",
    "I2C-2",
    "I2C-3",
    "SPI-0"
    "SPI-1"
    "SPI-2"
};


ESensorDevice::ESensorDevice() :
  Bus(BUS::UNKNOWN),
  Address(0),
  Pin(-1),
  AddressStr(""),
  PinStr(""),
  Chip(""),
  Identifier(""),
  Measuring(false),
  TimeStamp(0),
  NKeyVals(0) {
}


ESensorDevice::BUS ESensorDevice::bus() const {
  return Bus;
}


void ESensorDevice::setInternBus() {
  Bus = BUS::INTERN;
  add("Bus", BusStrings[bus()]);
}


void ESensorDevice::setSingleWireBus(int pin) {
  Bus = BUS::SINGLEWIRE;
  Address = 0;
  Pin = pin;
  snprintf(PinStr, MaxPin, "%d", Pin);
  PinStr[MaxPin] = '\0';
  strcpy(Identifier, busStr());
  sprintf(Identifier + strlen(Identifier), " %d", pin);
  add("Bus", BusStrings[bus()]);
  add("Pin", PinStr);
  add("Identifier", Identifier);
}


void ESensorDevice::setOneWireBus(int pin) {
  Bus = BUS::ONEWIRE;
  Address = 0;
  Pin = pin;
  snprintf(PinStr, MaxPin, "%d", Pin);
  PinStr[MaxPin] = '\0';
  add("Bus", BusStrings[bus()]);
  add("Pin", PinStr);
}


void ESensorDevice::setI2CBus(const TwoWire &wire, unsigned int address) {
  if (&wire == &Wire)
    Bus = BUS::I2C0;
#if WIRE_INTERFACES_COUNT >= 2
  else if (&wire == &Wire1)
    Bus = BUS::I2C1;
#endif
#if WIRE_INTERFACES_COUNT >= 3
  else if (&wire == &Wire2)
    Bus = BUS::I2C2;
#endif
#if WIRE_INTERFACES_COUNT >= 4
  else if (&wire == &Wire3)
    Bus = BUS::I2C3;
#endif
  Address = address;
  Pin = -1;
  snprintf(AddressStr, MaxPin, "%x", Address);
  AddressStr[MaxPin] = '\0';
  strcpy(Identifier, busStr());
  sprintf(Identifier + strlen(Identifier), " %x", address);
  add("Bus", BusStrings[bus()]);
  add("Address", AddressStr);
  add("Identifier", Identifier);
}


void ESensorDevice::setSPIBus(const SPIClass &spi, unsigned int cspin) {
  if (&spi == &SPI)
    Bus = BUS::SPI0;
#if defined(__MKL26Z64__)
  else if (&spi == &::SPI1)
    Bus = BUS::SPI1;
#elif defined(__MK64FX512__) || defined(__MK66FX1M0__) || defined(__IMXRT1062__)
  else if (&spi == &::SPI1)
    Bus = BUS::SPI1;
  else if (&spi == &::SPI2)
    Bus = BUS::SPI2;
#endif
  Address = 0;
  Pin = cspin;
  snprintf(PinStr, MaxPin, "%d", Pin);
  PinStr[MaxPin] = '\0';
  strcpy(Identifier, busStr());
  sprintf(Identifier + strlen(Identifier), " %d", cspin);
  add("Bus", BusStrings[bus()]);
  add("Pin", PinStr);
  add("Identifier", Identifier);
}


unsigned int ESensorDevice::address() const {
  return Address;
}


int ESensorDevice::pin() const {
  return Pin;
}


const char* ESensorDevice::chip() const {
  return Chip;
}


void ESensorDevice::setChip(const char *chip) {
  strncpy(Chip, chip, MaxStr);
  add("Chip", Chip);
}


const char* ESensorDevice::identifier() const {
  return Identifier;
}


void ESensorDevice::setIdentifier(const char *identifier) {
  strncpy(Identifier, identifier, MaxStr);
  add("Identifier", Identifier);
}


void ESensorDevice::report(Stream &stream) {
  if (available()) {
    stream.printf("sensor device %-12s", chip());
    if (bus() != BUS::UNKNOWN) {
      stream.printf(" on %-10s bus", busStr());
      if (address() != 0)
	stream.printf(" at address %4x", address());
      else if (pin() >= 0)
	stream.printf(" at pin     %4d", pin());
      else
	stream.printf("%16s", "");
    }
    else
      stream.printf("%32s", "");
    if (strlen(identifier()) > 0)
      stream.printf(" with ID %s", identifier());
    stream.println();
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


int ESensorDevice::add(const char *key, const char *value) {
  if ((key == 0) || (value == 0))
    return -1;
  int i = setValue(key, value);
  if (i >= 0)
    return i;
  if (NKeyVals >= MaxKeyVals)
    return -1;
  Keys[NKeyVals] = key;
  Values[NKeyVals] = value;
  return ++NKeyVals;
}


bool ESensorDevice::setValue(size_t index, const char *value) {
  if (index >= NKeyVals)
    return false;
  if (value == 0)
    return false;
  Values[index] = value;
  return true;
}


int ESensorDevice::setValue(const char *key, const char *value) {
  for (size_t k=0; k<NKeyVals; k++) {
    if (strcmp(Keys[k], key) == 0) {
      if (setValue(k, value))
	return k;
      else
	return -1;
    }
  }
  return -1;
}


void ESensorDevice::write(Stream &stream, size_t indent, size_t indent_incr) const {
  if (available()) {
    stream.printf("%*s%s (%s):\n", indent, "", chip(), identifier());
    indent += indent_incr;
    size_t w = 0;
    for (size_t k=0; k<NKeyVals; k++) {
      if (w < strlen(Keys[k]))
	w = strlen(Keys[k]);
    }
    for (size_t k=0; k<NKeyVals; k++) {
      size_t kw = w >= strlen(Keys[k]) ? w - strlen(Keys[k]) : 0;
      stream.printf("%*s%s:%*s %s\n", indent, "", Keys[k], kw, "", Values[k]);
    }
  }
}

