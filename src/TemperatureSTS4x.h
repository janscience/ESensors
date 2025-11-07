/*
  TemperatureSTS4x - read temperature from a Sensirion STS4x chip.
  Created by Jan Benda, August 23rd, 2025.

  The [STS4x data
  sheet](https://github.com/janscience/ESensors/tree/main/docs/chips/datasheets/sts4x.pdf).
*/

#ifndef TemperatureSTS4x_h
#define TemperatureSTS4x_h


#include <Arduino.h>
#include <Wire.h>
#include <ESensor.h>


enum STS4xAddress
{
  STS4x_ADDR1 = 0x44,
  STS4x_ADDR2 = 0x45,
  STS4x_ADDR3 = 0x46
};


enum STS4xPrecision
{
  STS4x_HIGH = 0xFD,
  STS4x_MEDIUM = 0xF6,
  STS4x_LOW = 0xE0
};


class TemperatureSTS4x : public ESensor {

 public:
  
  // You need to call begin() in oder to initialize the device.
  TemperatureSTS4x(ESensors *sensors=0);
  
  // Initialize device on I2C bus with address.
  TemperatureSTS4x(TwoWire &wire, STS4xAddress addr);
  
  // Initialize device on I2C bus with address.
  TemperatureSTS4x(ESensors *sensors, TwoWire &wire, STS4xAddress addr);
  
  // Initialize device on I2C bus with address.
  void begin(TwoWire &wire, STS4xAddress addr);

  // Return true if device is available.
  virtual bool available();

  // Recommended delay between a request() and read() in milliseconds.
  virtual unsigned long delayTime() const { return 10; };

  // The temperature in degrees celsius.
  // On error, return -INFINITY.
  virtual float reading() const;

  // Set precision (repeatability) of temperature measurements.
  void setPrecision(STS4xPrecision precision);
  
  
 private:

  // Request a temperature conversion.
  virtual void requestData();

  // Retrieve a temperature reading from the device.
  virtual void getData();

  TwoWire  *I2CBus;
  STS4xAddress I2CAddr;
  STS4xPrecision Precision;
  float Celsius;
  
  static const char *PrecisionStrings[3];
};


#endif
