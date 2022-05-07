/*
  ESensorDevice - Virtual base class for an environmental sensor device.
  Created by Jan Benda, April 24th, 2022.

  This is the basic interface for reading some data from a sensor device.
  The ESensor class then retrieves a single sensor reading.
*/

#ifndef ESensorDevice_h
#define ESensorDevice_h


#include <Arduino.h>
#include <TimeLib.h>


class ESensorDevice {

 public:

  static const float NoValue = -INFINITY;

  // Initialize the sensor.
  ESensorDevice();

  // Return name of sensor chip model as character array.
  virtual const char* chip() const;

  // Return unique identifier of sensor chip as character array.
  virtual const char* identifier() const;
  
  // Return true if sensor is available.
  virtual bool available() = 0;
  
  // Report properties of device on serial monitor.
  virtual void report();

  // Request a sensor reading.
  void request();

  // Recommended delay between a request() and get().
  virtual unsigned long delayTime() const { return 0; };

  // Retrieve a sensor reading from the device
  // and store it in a variable.
  // You need to call request() at least delayTime() before.
  void get();

  // Initiate measurement (request()), wait for delayTime(), and retrieve
  // the data (get()).
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

  // Implement this function to retrieve a sensor reading from the
  // device and store it in a variable.
  // Called by get().
  virtual void getData() = 0;

  static const int MaxStr = 50;
  char Chip[MaxStr];
  char Identifier[MaxStr];
  bool Measuring;
  time_t TimeStamp;
  
};


#endif
