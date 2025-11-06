/*
  ESensorDevice - Virtual base class for an environmental sensor device.
  Created by Jan Benda, April 24th, 2022.

  This is the basic interface for reading some data from a sensor device.
  The ESensor class then provides a single sensor reading.
*/

#ifndef ESensorDevice_h
#define ESensorDevice_h


#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <TimeLib.h>


class ESensorDevice {

 public:

  static constexpr float NoValue = -INFINITY;

  enum BUS {
    UNKNOWN,
    INTERN,
    SINGLEWIRE,
    ONEWIRE,
    I2C0,
    I2C1,
    I2C2,
    I2C3,
    SPI0,
    SPI1,
    SPI2
  };
  
  static const char *BusStrings[11];

  // Initialize the sensor.
  ESensorDevice();

  // Bus controlling the sensor device.
  virtual BUS bus() const;

  // Bus controlling the sensor device as a string (max 8 characters).
  const char *busStr() const { return BusStrings[bus()]; };

  // Address on I2C bus.
  virtual unsigned int address() const;
  
  // Address on I2C bus as a string.
  virtual const char *addressStr() const { return AddressStr; };

  // Pin of OneWire bus or chip select pin of device on SPI bus.
  virtual int pin() const;
  
  // Pin as a string.
  virtual const char *pinStr() const { return PinStr; };

  // Return name of sensor chip model as character array.
  virtual const char* chip() const;

  // Return unique identifier of sensor chip as character array.
  virtual const char* identifier() const;

  // The number of key-value pairs available in the device's metadata.
  virtual size_t metadata() const { return NKeyVals; };

  // Return key of the index-th metadata entry.
  virtual const char *key(size_t index) const { return Keys[index]; };

  // Return value of the index-th metadata entry.
  virtual const char *value(size_t index) const { return Values[index]; };
  
  // Return true if sensor is available.
  virtual bool available() = 0;
  
  // Report properties of device on stream.
  virtual void report(Stream &stream=Serial);

  // Request a sensor reading.
  void request();

  // Recommended delay between a request() and get() in miiliseconds.
  virtual unsigned long delayTime() const { return 0; };

  // Get a sensor reading from the device
  // and store it in a variable.
  // You need to call request() at least delayTime() before.
  void get();

  // Initiate measurement (request()), wait for delayTime(), and get
  // the data (get()).
  // This function may block considerably!
  void read();

  // Time stamp of last sensor reading.
  time_t timeStamp() const;

  
protected:

  // Set internal bus.
  void setInternBus();

  // Set SingleWire bus and its data pin.
  // Also set identifier to bus name plus data pin.
  void setSingleWireBus(int pin);

  // Set OneWire bus and its data pin.
  void setOneWireBus(int pin);

  // Set I2C bus and address that controls the chip.
  // Also set identifier to bus name plus I2C address.
  void setI2CBus(const TwoWire &wire, unsigned int address);

  // Set SPI bus and CS pin that controls the chip.
  // Also set identifier to bus name plus CS pin.
  void setSPIBus(const SPIClass &spi, unsigned int cspin);

  // Set the name of the chip.
  void setChip(const char *chip);

  // Set the unique identifier of the chip.
  void setIdentifier(const char *identifier);

  // Request a sensor reading.
  // Reimplement this function, if the sensor device
  // needs to be prepared for a sensor reading in advance.
  virtual void requestData();

  // Implement this function to get a sensor reading from the
  // device after delayTime() and store it in a variable.
  // Called by get().
  virtual void getData() = 0;

  // If key already exists, the set value of this key.
  // Otherwise, add a new key-value pair to the device's metadata.
  // The strings are not copied, only pointers are stored.
  // Make sure to pass in static strings.
  // Return the index of the set or added key-value pair.
  // If nothing was added, return -1.
  int add(const char *key, const char *value);

  // Set value of key-value pair at index.
  // Return true on success, i.e. when index is valid.
  bool setValue(size_t index, const char *value);

  // Set value of key-value pair.
  // Return the index of key on succes, otherwise -1.
  int setValue(const char *key, const char *value);

  BUS Bus;
  unsigned int Address;
  int Pin;
  static const int MaxPin = 5;
  char AddressStr[MaxPin + 1];
  char PinStr[MaxPin + 1];
  static const int MaxStr = 49;
  char Chip[MaxStr + 1];
  char Identifier[MaxStr + 1];
  bool Measuring;
  time_t TimeStamp;
  
  static const size_t MaxKeyVals = 8;
  const char *Keys[MaxKeyVals];
  const char *Values[MaxKeyVals];
  size_t NKeyVals;
  
};


#endif
