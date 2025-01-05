#include <ESensorDevice.h>


const char *ESensorDevice::BusStrings[10] = {
    "unknown",
    "intern",
    "OneWire",
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
  Retrieving(false),
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


void ESensorDevice::setI2CBus(const TwoWire &wire, unsigned int address) {
  if (&wire == &Wire)
    Bus = BUS::I2C0;
#if defined(__IMXRT1052__) || defined(__IMXRT1062__)
  else if (&wire == &Wire1)
    Bus = BUS::I2C1;
  else if (&wire == &Wire2)
    Bus = BUS::I2C2;
#if defined(ARDUINO_TEENSY_MICROMOD)
  else if (&wire == &Wire3)
    Bus = BUS::I2C3;
#endif
#endif
#if defined(__arm__) && defined(TEENSYDUINO) && (defined(__MKL26Z64__) || defined(__MK20DX128__) || defined(__MK20DX256__) || defined(__MK64FX512__) || defined(__MK66FX1M0__))
#ifdef WIRE_IMPLEMENT_WIRE1
  else if (&wire == &Wire1)
    Bus = BUS::I2C1;
#endif
#ifdef WIRE_IMPLEMENT_WIRE2
  else if (&wire == &Wire2)
    Bus = BUS::I2C2;
#endif
#ifdef WIRE_IMPLEMENT_WIRE3
  else if (&wire == &Wire3)
    Bus = BUS::I2C3;
#endif
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
    stream.printf("device %-12s", chip());
    if (bus() != BUS::UNKNOWN) {
      stream.printf(" on %-8s bus", busStr());
      if (address() != 0)
	stream.printf(" at address %04x", address());
      else if (pin() >= 0)
	stream.printf(" at pin     %4d", pin());
      else
	stream.printf("%16s", "");
    }
    else
      stream.printf("%32s", "");
    if (strlen(identifier()) > 0)
      stream.printf(" with ID %s\n", identifier());
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
