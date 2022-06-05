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
#include <ESensorValue.h>


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

  // Set measurement quality. One of
  // BH1750_QUALITY_HIGH, BH1750_QUALITY_HIGH2, BH1750_QUALITY_LOW
  void setQuality(BH1750Quality quality);

  // Set measurement time register. The higher the more sensitive.
  // Between 31 and 254.
  void setMTReg(int mtreg);

  // If set true, after each measurement the integration time and
  // quality are adjusted to ensure the next measurement to not not
  // exceed the measurement range.
  void setAutoRanging(bool autorange=true);

  // Return true if light sensor is available.
  virtual bool available();

  // Recommended delay between a request() and get() in milliseconds.
  virtual unsigned long delayTime() const;

  // Illuminance in Lux.
  virtual float reading() const { return Illuminance; };

  // Illuminance in Lux.
  float illuminance() const { return Illuminance; };
  
  // Raw sensor reading.
  uint16_t rawData() const { return RawData; };
  
  // Quality of the last sensor reading.
  int quality() const { return Quality; };
  
  // Measurement time register value of the last sensor reading.
  int mtReg() const { return MTReg; };

  
 private:

  void init();

  // Request a sensor reading.
  virtual void requestData();

  // Retrieve a sensor reading from the device.
  virtual void getData();

  float Illuminance;
  uint16_t RawData;
  BH1750Quality Quality;
  int MTReg;
  bool AutoRange;
  
};


class RawBH1750 : public ESensorValue<LightBH1750> {

 public:

  RawBH1750(LightBH1750 *bh, ESensors *sensors=0);

  // Raw sensor reading.
  virtual float reading() const;
};


class QualityBH1750 : public ESensorValue<LightBH1750> {

 public:

  QualityBH1750(LightBH1750 *bh, ESensors *sensors=0);

  // Quality setting of last sensor reading.
  // 0: HIGH, 1: HIGH2, 3: LOW 
  virtual float reading() const;
};


class TimeBH1750 : public ESensorValue<LightBH1750> {

 public:

  TimeBH1750(LightBH1750 *bh, ESensors *sensors=0);

  // Time setting of last sensor reading.
  virtual float reading() const;
};


#endif
