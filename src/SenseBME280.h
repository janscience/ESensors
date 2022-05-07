/*
  SenseBME280 - read temperature, humidity, and pressure from Bosch BME280.
  Created by Jan Benda, April 22nd, 2022.

  Wrapper for [SparkFun BME280 Arduino Library](https://github.com/sparkfun/SparkFun_BME280_Arduino_Library).

  Only supports forced mode and burst reading.

  [Bosch Sensortec Website](https://www.bosch-sensortec.com/products/environmental-sensors/humidity-sensors-bme280/)

  The [BME280
  Datasheet](https://www.bosch-sensortec.com/media/boschsensortec/downloads/datasheets/bst-bme280-ds002.pdf).
*/

#ifndef SenseBME280_h
#define SenseBME280_h


#include <Arduino.h>
#include <Wire.h>
#include <SparkFunBME280.h>
#include <ESensorDevice.h>
#include <ESensorValue.h>


// Simple wrapper around Spark Fun BME280 library.
class SenseBME280 : public ESensorDevice, protected BME280 {

 public:

  static const float NoValue = -INFINITY;

  // Do not initialize BME280 device yet.
  SenseBME280();
  
  // Initialize BME280 device with address (0x77 or 0x76) on default I2C bus.
  // NOTE: you need to initalize I2C by calling `Wire.begin()` *before*!
  bool beginI2C(uint8_t address=0x77);

  // Initialize BME280 device with address (0x77 or 0x76) on I2C bus.
  // NOTE: you need to initalize I2C by calling `Wire.begin()` *before*!
  bool beginI2C(TwoWire &wire, uint8_t address=0x77);
  
  // Initialize BME280 device on SPI bus with chip select pin.
  bool beginSPI(uint8_t cs_pin);

  // Return true if sensor is available.
  virtual bool available();

  // Recommended delay between a request() and get() in milliseconds.
  virtual unsigned long delayTime() const;

  // The temperature in degrees celsius.
  // On error, return -INFINITY.
  float temperature() const { return Celsius; };

  // The relative humidity as a fraction.
  // On error, return -INFINITY.
  float humidity() const { return Humidity; };

  // The pressure in Pascal.
  // On error, return -INFINITY.
  float pressure() const { return Pressure; };

  
 private:

  void init();

  // Request a sensor reading.
  virtual void requestData();

  // Retrieve a sensor reading from the device.
  virtual void getData();

  float Celsius;
  float Humidity;
  float Pressure;
  
};


class TemperatureBME280 : public ESensorValue<SenseBME280> {

 public:

  TemperatureBME280(SenseBME280 *bme, ESensors *sensors=0);

  // The temperature in degrees celsius.
  // On error, return -INFINITY.
  virtual float reading() const;
};


class HumidityBME280 : public ESensorValue<SenseBME280> {

 public:

  HumidityBME280(SenseBME280 *bme, ESensors *sensors=0);

  // The relative humidity as a fraction.
  // On error, return -INFINITY.
  virtual float reading() const;
};


class PressureBME280 : public ESensorValue<SenseBME280> {

 public:

  PressureBME280(SenseBME280 *bme, ESensors *sensors=0);

  // The pressure in Pascal.
  // On error, return -INFINITY.
  virtual float reading() const;
};


#endif
