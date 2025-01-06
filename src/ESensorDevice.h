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
    ONEWIRE,
    I2C0,
    I2C1,
    I2C2,
    I2C3,
    SPI0,
    SPI1,
    SPI2
  };
  
  static const char *BusStrings[10];

  // Initialize the sensor.
  ESensorDevice();

  // Bus controlling the sensor device.
  virtual BUS bus() const;

  // Bus controlling the sensor device as a string (max 8 characters).
  const char *busStr() const { return BusStrings[bus()]; };

  // Address on I2C bus.
  virtual unsigned int address() const;

  // Pin of OneWire bus or chip select pin of device on SPI bus.
  virtual int pin() const;

  // Return name of sensor chip model as character array.
  virtual const char* chip() const;

  // Return unique identifier of sensor chip as character array.
  virtual const char* identifier() const;
  
  // Return true if sensor is available.
  virtual bool available() = 0;
  
  // Report properties of device on stream.
  virtual void report(Stream &stream=Serial);

  // Request a sensor reading.
  void request();

  // Recommended delay between a request() and get().
  virtual unsigned long delayTime() const { return 0; };

  // Retrieve sensor data over an extended period of time.
  // Needs to be called repeatedly until true is returned.
  // time is the elapsed time since request() in milliseconds.
  bool retrieve(unsigned long time);

  // Get a sensor reading from the device
  // and store it in a variable.
  // You need to call request() at least delayTime() before.
  void get();

  // Initiate measurement (request()), wait for delayTime()
  // while calling retrieve(), and get the data (get()).
  // This function may block considerably!
  void read();

  // Time stamp of last sensor reading.
  time_t timeStamp() const;

  
protected:

  // Set internal bus.
  void setInternBus() { Bus = BUS::INTERN; };

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

  // Retrieve a sensor reading. This function is called repeatedly
  // between request() and get() until it returns true.
  // time is the elapsed time since request() in milliseconds.
  // Reimplement this function, if communication with the
  // sensor device requires considerable time.
  virtual bool retrieveData(unsigned long time);

  // Implement this function to get a sensor reading from the
  // device after delayTime() and store it in a variable.
  // Called by get().
  virtual void getData() = 0;

  BUS Bus;
  unsigned int Address;
  int Pin;
  static const int MaxStr = 49;
  char Chip[MaxStr + 1];
  char Identifier[MaxStr + 1];
  bool Measuring;
  bool Retrieving;
  time_t TimeStamp;
  
};


#endif
