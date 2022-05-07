/*
  LightTSL2591 - read light intensity from AMS TSL2591.
  Created by Jan Benda, April 25nd, 2022.

  Wrapper for [TSL2591MI](https://bitbucket.org/christandlg/tsl2591mi/).

  [Infos, Datasheet, libraries](https://github.com/janscience/ESensors/blob/main/docs/chips/tsl2591.md)

  [Background light measurements](https://github.com/janscience/ESensors/tree/main/docs/parameters/light)
*/

#ifndef LightTSL2591_h
#define LightTSL2591_h


#include <Arduino.h>
#include <Wire.h>
#include <TSL2591TwoWire.h>
#include <ESensorDevice.h>
#include <ESensor.h>
#include <ESensorValue.h>


// Simple wrapper around TSL2591MI library.
class LightTSL2591 : public ESensorDevice, protected TSL2591TwoWire {

 public:

  static const uint8_t AUTO_GAIN = 0xFF;

  // Do not initialize TSL2591 device yet.
  LightTSL2591();

  // Do not initialize TSL2591 device yet.
  LightTSL2591(TwoWire *wire);
 
  // Initialize TSL2591 device on the I2C bus provided by constructor,
  // otherwise on default I2C bus.
  // NOTE: you need to initalize I2C by calling `Wire.begin()` *before*!
  bool begin();

  // Initialize TSL2591 device on an I2C bus.
  // NOTE: you need to initalize I2C by calling `Wire1.begin()` *before*!
  bool begin(TwoWire &wire);

  // Return true if light sensor is available.
  virtual bool available();

  // Recommended delay between a request() and get() in milliseconds.
  virtual unsigned long delayTime() const;

  // Set the integration time of the sensor.
  // One of 0: 100ms, 1: 200ms, 2: 300ms, 3: 400ms, 4: 500ms, 5: 600ms.
  // Set this once right after begin().
  // Returns true on success.
  bool setIntegrationTime(uint8_t time);

  // The gain that was active when getting the data:
  // 0: low (x1), 1: medium (x24.5), 2: high (x400), 3: max (x9200).
  uint8_t gain() const { return Gain; };

  // Set the gain of the sensor.
  // One of 0: low (x1), 1: medium (x24.5), 2: high (x400), 3: max (x9200),
  // or 0xFF (auto gain).
  // You may use TSL2591MI::TSL2591_GAIN_LOW, TSL2591MI::TSL2591_GAIN_MED,
  // TSL2591MI::TSL2591_GAIN_HIGH,  TSL2591MI::TSL2591_GAIN_MAX,
  // LightTSL2591::AUTO_GAIN.
  // Setting auto gain does not set any gain immediately, but whenever new
  // data are retrieved from the sensor, they are checked and if appropriate
  // the gain is changed. Setting a specific gain switches auto gain off.
  // Set this once right after begin().
  // Returns true on success.
  bool setGain(uint8_t gain);

  // Provide temperature in degrees celsius for temperature correction.
  // Temperature correction is applied immediately when retrieving data
  // from the chip in the getData() function.
  void setTemperature(double temperature);
  
  // Temperature corrected channel count of the full spectrum sensor.
  uint16_t channel0() const { return C0DATA; };

  // Temperature corrected channel count of the IR spectrum sensor.
  uint16_t channel1() const { return C1DATA; };
  
  // The IR ratio C1DATA/C0DATA.
  // On error, return -INFINITY.
  float IRRatio() const;
  
  // The irradiance of the full spectrum in W/m^2.
  // On error, return -INFINITY.
  float irradianceFull() const { return IrradianceFull; };

  // The irradiance of the IR spectrum in W/m^2.
  // On error, return -INFINITY.
  float irradianceIR() const { return IrradianceIR; };

  // The irradiance of the visible spectrum in W/m^2.
  // On error, return -INFINITY.
  float irradianceVisible() const { return IrradianceFull - IrradianceIR; };

  // The illuminance in Lux.
  // On error, return -INFINITY.
  float illuminance() const { return Illuminance; };

  
 private:

  void init();

  // Request a sensor reading.
  virtual void requestData();

  // Retrieve a sensor reading from the device.
  virtual void getData();

  unsigned long DelayTime;
  float IrradianceFull;
  float IrradianceIR;
  float Illuminance;

  // data values returned from the chip.
  // counts are temperature adjusted (see
  // [dataheet Figure 14](https://ams.com/documents/20143/36005/TSL2591_DS000338_6-00.pdf),
  // if temperature was provided via setTemperature().
  uint16_t C0DATA;
  uint16_t C1DATA;

  uint16_t MaxData;
  uint8_t Gain;
  bool AutoGain;
  
};


class Channel0TSL2591 : public ESensorValue<LightTSL2591> {

 public:

  Channel0TSL2591(LightTSL2591 *tsl, ESensors *sensors=0);

  // Temperature corrected channel count of the full spectrum sensor.
  virtual float reading() const;
};


class Channel1TSL2591 : public ESensorValue<LightTSL2591> {

 public:

  Channel1TSL2591(LightTSL2591 *tsl, ESensors *sensors=0);

  // Temperature corrected channel count of the IR spectrum sensor.
  virtual float reading() const;
};


class GainTSL2591 : public ESensorValue<LightTSL2591> {

 public:

  GainTSL2591(LightTSL2591 *tsl, ESensors *sensors=0);

  // The gain code that was active when getting the sensor readings.
  // 0: low (x1), 1: medium (x24.5), 2: high (x400), 3: max (x9200).
  virtual float reading() const;
};


class IRRatioTSL2591 : public ESensorValue<LightTSL2591> {

 public:

  IRRatioTSL2591(LightTSL2591 *tsl, ESensors *sensors=0);

  // IR ratio C1DATA / C0DATA.
  virtual float reading() const;
};


class IrradianceFullTSL2591 : public ESensorValue<LightTSL2591> {

 public:

  IrradianceFullTSL2591(LightTSL2591 *tsl, ESensors *sensors=0);

  // The irradiance of the full spectrum in W/m^2.
  // On error, return -INFINITY.
  virtual float reading() const;
};


class IrradianceIRTSL2591 : public ESensorValue<LightTSL2591> {

 public:

  IrradianceIRTSL2591(LightTSL2591 *tsl, ESensors *sensors=0);

  // The irradiance of the IR spectrum in W/m^2.
  // On error, return -INFINITY.
  virtual float reading() const;
};


class IrradianceVisibleTSL2591 : public ESensorValue<LightTSL2591> {

 public:

  IrradianceVisibleTSL2591(LightTSL2591 *tsl, ESensors *sensors=0);

  // The irradiance of the visible spectrum in W/m^2.
  // On error, return -INFINITY.
  virtual float reading() const;
};


class IlluminanceTSL2591 : public ESensorValue<LightTSL2591> {

 public:

  IlluminanceTSL2591(LightTSL2591 *tsl, ESensors *sensors=0);

  // The illuminance in Lux.
  // On error, return -INFINITY.
  virtual float reading() const;
};


#endif
