/*
  LightTSL2591 - read light intensity from AMS TSL2591.
  Created by Jan Benda, April 25nd, 2022.

  Wrapper for [TSL2591MI](https://bitbucket.org/christandlg/tsl2591mi/).

  [Infos, Datasheet, libraries](https://github.com/janscience/TeeSense/blob/main/docs/chips/tsl2591.md)

  [Background light measurements](https://github.com/janscience/TeeSense/tree/main/docs/parameters/light)
*/

#ifndef LightTSL2591_h
#define LightTSL2591_h


#include <Arduino.h>
#include <Wire.h>
#include <TSL2591TwoWire.h>
#include <SensorDevice.h>
#include <Sensor.h>


// Simple wrapper around TSL2591MI library.
class LightTSL2591 : public SensorDevice, protected TSL2591TwoWire {

 public:

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
    
  // Return name of chip as string.
  const char* chip() const { return Chip; };

  // Return identifier of sensor chip as character array (always 50).
  virtual const char* identifier() const { return ID; };

  // Return true if light sensor is available.
  virtual bool available();

  // Recommended delay between a request() and read() in milliseconds.
  virtual unsigned long delay() const;

  // Set the integration time of the sensor.
  // One of 0: 100ms, 1: 200ms, 2: 300ms, 3: 400ms, 4: 500ms, 5: 600ms.
  // Set this once right after begin().
  // Returns true on success.
  bool setIntegrationTime(uint8_t time);

  // Set the gain of the sensor.
  // One of 0: low (x1), 1: medium (x24.5), 2: high (x400), 3: max (x9200).
  // Set this once right after begin().
  // Returns true on success.
  bool setGain(uint8_t gain);

  // Provide temperature in degrees celsius for temperature correction.
  // Temperature correction is applied immediately when retrieving data
  // from the chip in the readData() function.
  void setTemperature(double temperature);

  // Temperature corrected channel count of the full spectrum sensor.
  uint16_t channel0() const { return Channel0; };

  // Temperature corrected channel count of the IR spectrum sensor.
  uint16_t channel1() const { return Channel1; };
  
  // The irradiance of the full spectrum in W/m^2.
  // On error, return -INFINITY.
  float irradianceFull() const { return IrradianceFull; };

  // The irradiance of the IR spectrum in W/m^2.
  // On error, return -INFINITY.
  float irradianceIR() const { return IrradianceIR; };

  // The irradiance of the visible spectrum in W/m^2.
  // On error, return -INFINITY.
  float irradianceVisible() const { return IrradianceVisible; };

  
 private:

  void init();

  // Request a sensor reading.
  virtual void requestData();

  // Retrieve a sensor reading from the device.
  virtual void readData();

  char Chip[8];
  char ID[4];
  float IrradianceFull;
  float IrradianceIR;
  float IrradianceVisible;

  // data values returned from the chip.
  // counts are temperature adjusted (see
  // [dataheet Figure 14](https://ams.com/documents/20143/36005/TSL2591_DS000338_6-00.pdf),
  // if temperature is provided.
  uint16_t Channel0;
  uint16_t Channel1;
  
};


// Base class for sensors that read out LightTSL2591.
class SensorTSL2591 : public Sensor {

 public:

  SensorTSL2591(LightTSL2591 *tsl, Sensors *sensors,
		const char *name, const char *symbol,
		const char *unit, const char *format);

  // Return true if TSL2591 sensor chip is available.
  virtual bool available() { return TSL->available(); };

  // Return name of sensor chip model as character array.
  virtual const char* chip() const { return TSL->chip(); };

  // Return unique identifier of sensor chip as character array.
  virtual const char* identifier() const { return TSL->identifier(); };

  // Return resolution of the irradiance readings.
  virtual float resolution() const;

  // Recommended delay between a request() and read() in milliseconds.
  virtual unsigned long delay() const { return TSL->delay(); };

  
 protected:

  // Request a sensor conversion.
  virtual void requestData();

  // Retrieve a sensor reading from the device.
  virtual void readData();

  LightTSL2591 *TSL;

};


class Channel0TSL2591 : public SensorTSL2591 {

 public:

  Channel0TSL2591(LightTSL2591 *tsl, Sensors *sensors=0);

  // Temperature corrected channel count of the full spectrum sensor.
  virtual float reading() const;
};


class Channel1TSL2591 : public SensorTSL2591 {

 public:

  Channel1TSL2591(LightTSL2591 *tsl, Sensors *sensors=0);

  // Temperature corrected channel count of the IR spectrum sensor.
  virtual float reading() const;
};


class IrradianceFullTSL2591 : public SensorTSL2591 {

 public:

  IrradianceFullTSL2591(LightTSL2591 *tsl, Sensors *sensors=0);

  // The irradiance of the full spectrum in W/m^2.
  // On error, return -INFINITY.
  virtual float reading() const;
};


class IrradianceIRTSL2591 : public SensorTSL2591 {

 public:

  IrradianceIRTSL2591(LightTSL2591 *tsl, Sensors *sensors=0);

  // The irradiance of the IR spectrum in W/m^2.
  // On error, return -INFINITY.
  virtual float reading() const;
};


class IrradianceVisibleTSL2591 : public SensorTSL2591 {

 public:

  IrradianceVisibleTSL2591(LightTSL2591 *tsl, Sensors *sensors=0);

  // The irradiance of the visible spectrum in W/m^2.
  // On error, return -INFINITY.
  virtual float reading() const;
};


#endif
