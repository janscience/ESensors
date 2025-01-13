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
  Chip(""),
  Identifier(""),
  Measuring(false),
  TimeStamp(0) {
}


ESensorDevice::BUS ESensorDevice::bus() const {
  return Bus;
}


void ESensorDevice::setOneWireBus(int pin) {
  Bus = BUS::ONEWIRE;
  Address = 0;
  Pin = pin;
}


void ESensorDevice::setSingleWireBus(int pin) {
  Bus = BUS::SINGLEWIRE;
  Address = 0;
  Pin = pin;
  strcpy(Identifier, busStr());
  sprintf(Identifier + strlen(Identifier), " %d", pin);
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
  strcpy(Identifier, busStr());
  sprintf(Identifier + strlen(Identifier), " %x", address);
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
  strcpy(Identifier, busStr());
  sprintf(Identifier + strlen(Identifier), " %d", cspin);
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
}


const char* ESensorDevice::identifier() const {
  return Identifier;
}


void ESensorDevice::setIdentifier(const char *identifier) {
  strncpy(Identifier, identifier, MaxStr);
}


void ESensorDevice::report(Stream &stream) {
  if (available()) {
    stream.printf("sensor device %-12s", chip());
    if (bus() != BUS::UNKNOWN) {
      stream.printf(" on %-8s bus", busStr());
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
