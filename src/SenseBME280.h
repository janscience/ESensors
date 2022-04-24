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
#include <SensorDevice.h>
#include <Sensor.h>


// Simple wrapper around Spark Fun BME280 library.
class SenseBME280 : public SensorDevice, protected BME280 {

 public:

  static const float NoValue = -INFINITY;

  // Do not initialize BME280 device yet.
  SenseBME280();
  
  // Initialize BME280 device with address (0x77 or 0x76) on default I2C bus.
  bool beginI2C(uint8_t address=0x77);

  // Initialize BME280 device with address (0x77 or 0x76) on I2C bus.
  bool beginI2C(TwoWire &wire, uint8_t address=0x77);
  
  // Initialize BME280 device on SPI bus with chip select pin.
  bool beginSPI(uint8_t cs_pin);
    
  // Return name of chip as string.
  const char* chip() const { return Chip; };

  // Return unique identifier of sensor chip as character array.
  virtual const char* identifier() const { return ""; };

  // Return true if temperature sensor is available.
  virtual bool available();

  // Recommended delay between a request() and read() in milliseconds.
  virtual unsigned long delay() const;

  // The temperature in degrees celsius.
  // On error, return -INFINITY.
  float temperature() const { return Celsius; };

  // The relative humidity in percent.
  // On error, return -INFINITY.
  float humidity() const { return Humidity; };

  // The pressure in Pascal.
  // On error, return -INFINITY.
  float pressure() const { return Pressure; };

  
 private:

  void init();

  // Request a sensor reading.
  // Reimplement this function, if the sensor device
  // needs to be prepared for a sensor reading in advance.
  virtual void requestData();

  // Implement this function to retrieve a sensor reading from the
  // device and store it in a variable.
  virtual void readData();

  char Chip[8];
  float Celsius;
  float Humidity;
  float Pressure;
  
};


// Base class for sensors that read out SenseBME280.
class SensorBME280 : public Sensor {

 public:

  SensorBME280(SenseBME280 *bme, Sensors *sensors,
	       const char *name, const char *symbol,
	       const char *unit, const char *format);

  // Return true if BME280 sensor is available.
  virtual bool available() { return BME->available(); };

  // Return name of sensor chip model as character array.
  virtual const char* chip() const { return BME->chip(); };

  // Return unique identifier of sensor chip as character array.
  virtual const char* identifier() const { return BME->identifier(); };

  // Recommended delay between a request() and read() in milliseconds.
  virtual unsigned long delay() const { return BME->delay(); };

  
 protected:

  // Request a sensor conversion.
  virtual void requestData();

  // Retrieve a sensor reading from the device.
  virtual void readData();

  SenseBME280 *BME;

};


class TemperatureBME280 : public SensorBME280 {

 public:

  TemperatureBME280(SenseBME280 *bme, Sensors *sensors=0);

  // Return resolution of the temperature readings.
  virtual float resolution() const;

  // The temperature in degrees celsius.
  // On error, return -INFINITY.
  virtual float reading() const;
};


class HumidityBME280 : public SensorBME280 {

 public:

  HumidityBME280(SenseBME280 *bme, Sensors *sensors=0);

  // Return resolution of the humidity readings.
  virtual float resolution() const;

  // The relative humidity in percent.
  // On error, return -INFINITY.
  virtual float reading() const;
};


class AbsoluteHumidityBME280 : public SensorBME280 {

 public:

  AbsoluteHumidityBME280(SenseBME280 *bme, Sensors *sensors=0);

  // Return resolution of the absolute humidity readings.
  virtual float resolution() const;

  // The absolute humidity in g/m^3.
  // On error, return -INFINITY.
  virtual float reading() const;
};


class DewPointBME280 : public SensorBME280 {

 public:

  DewPointBME280(SenseBME280 *bme, Sensors *sensors=0);

  // Return resolution of the dew point readings.
  virtual float resolution() const;

  // The dew point in degrees celsius.
  // On error, return -INFINITY.
  virtual float reading() const;
};


class PressureBME280 : public SensorBME280 {

 public:

  PressureBME280(SenseBME280 *bme, Sensors *sensors=0);

  // Return resolution of the pressure readings.
  virtual float resolution() const;

  // The pressure in Pascal.
  // On error, return -INFINITY.
  virtual float reading() const;
};


class SeaLevelPressureBME280 : public PressureBME280 {

 public:

  // Provide altitude in meter.
  SeaLevelPressureBME280(SenseBME280 *bme, float altitude);

  // Provide altitude in meter.
  SeaLevelPressureBME280(SenseBME280 *bme, Sensors *sensors, float altitude);
  
  // The equivalent sea level pressure in Pascal.
  // On error, return -INFINITY.
  virtual float reading() const;

protected:

  float Altitude;
  
};


#endif
