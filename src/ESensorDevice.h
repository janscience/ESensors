/*
  ESensorDevice - Virtual base class for an environmental sensor device.
  Created by Jan Benda, April 24th, 2022.

  This is the basic interface for reading some data from a sensor device.
  The ESensor class then provides a single sensor reading.
*/

#ifndef ESensorDevice_h
#define ESensorDevice_h


#include <Arduino.h>
#include <TimeLib.h>


class ESensorDevice {

 public:

  static constexpr float NoValue = -INFINITY;

  // Initialize the sensor.
  ESensorDevice();

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

  static const int MaxStr = 49;
  char Chip[MaxStr + 1];
  char Identifier[MaxStr + 1];
  bool Measuring;
  bool Retrieving;
  time_t TimeStamp;
  
};


#endif
