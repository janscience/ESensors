/*
  TemperatureDS3231 - read temperature of a DS3231 real-time clock.
  Created by Jan Benda, January 18th, 2025.
  Based on https://github.com/PaulStoffregen/DS1307RTC

  The DS3231 is a temperature compensated real-time clock. As such it
  provides a temperature reading. The temperature is updated
  automaticlaly every 64s.

  The [DS3231 data
  sheet](https://www.analog.com/media/en/technical-documentation/data-sheets/ds3231.pdf).
*/

#ifndef TemperatureDS3231_h
#define TemperatureDS3231_h


#include <Arduino.h>
#include <Wire.h>
#include <ESensor.h>


class TemperatureDS3231 : public ESensor {

 public:
  
  // Initialize device on I2C bus.
  TemperatureDS3231(TwoWire &wire=Wire);
  
  // Initialize device on I2C bus.
  TemperatureDS3231(ESensors *sensors=0, TwoWire &wire=Wire);
  
  // Initialize device on I2C bus.
  void begin(TwoWire &wire=Wire);

  // Return true if device is available.
  virtual bool available() const;

  // Recommended delay between a request() and read() in milliseconds.
  virtual unsigned long delayTime() const { return 1; };

  // The temperature in degrees celsius.
  // On error, return -INFINITY.
  virtual float reading() const;
  
  
 private:

  // Request a temperature conversion.
  virtual void requestData();

  // Retrieve a temperature reading from the device.
  virtual void getData();

  TwoWire  *I2CBus;
  float Celsius;
};


#endif
