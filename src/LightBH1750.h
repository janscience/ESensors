/*
  LightBH1750 - read light intensity from BH1750.
  Created by Jan Benda, May 30th, 2022.

  Wrapper for [hp_BH1750](https://github.com/Starmbi/hp_BH1750)

  [Infos, Datasheet, libraries](https://github.com/janscience/ESensors/blob/main/docs/chips/bh1750.md)

  [Background light measurements](https://github.com/janscience/ESensors/tree/main/docs/parameters/light)
*/

#ifndef LightBH1750_h
#define LightBH1750_h


#include <Arduino.h>
#include <Wire.h>
#include <hp_BH1750.h>
#include <ESensor.h>


// Simple wrapper around hp_BH1750 library.
class LightBH1750 : public ESensor, protected hp_BH1750 {

 public:

  // Do not initialize BH1750 device yet.
  LightBH1750(ESensors *sensors=0);
 
  // Initialize BH1750 device on default I2C bus.
  // NOTE: you need to initalize I2C by calling `Wire.begin()` *before*!
  bool begin(uint8_t address=BH1750_TO_GROUND);

  // Initialize BH1750 device on an I2C bus.
  // NOTE: you need to initalize I2C by calling `Wire1.begin()` *before*!
  bool begin(TwoWire &wire, uint8_t address=BH1750_TO_GROUND);

  // Return true if light sensor is available.
  virtual bool available();

  // Recommended delay between a request() and get() in milliseconds.
  virtual unsigned long delayTime() const;

  // Illuminance in Lux.
  virtual float reading() const { return Illuminance; };

  
 private:

  void init();

  // Request a sensor reading.
  virtual void requestData();

  // Retrieve a sensor reading from the device.
  virtual void getData();

  float Illuminance;
  
};


#endif
