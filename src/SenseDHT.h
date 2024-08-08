/*
  SenseDHT - read temperature and humidity from Aosong DHT11 or DHT20.
  Created by Jan Benda, July 24nd, 2023.

  Wrapper for [DHT Sensors Non-Blocking](https://github.com/toannv17/DHT-Sensors-Non-Blocking) library by Toan Nguyen.

  The [DHT22 Datasheet](http://www.adafruit.com/datasheets/DHT22.pdf).
*/

#ifndef SenseDHT_h
#define SenseDHT_h

/*
#include <Arduino.h>
#include <DHT_Async.h>
#include <ESensorDevice.h>
#include <ESensorValue.h>


class SenseDHT : public ESensorDevice, protected DHT_Async {

 public:

  SenseDHT(uint8_t pin, uint8_t type);

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

  
 private:

  // Retrieve a sensor reading.
  virtual bool retrieveData(unsigned long time);

  // Get a sensor reading from the device.
  virtual void getData();

  unsigned long DelayTime;
  float Celsius;
  float Humidity;
  
};


class TemperatureDHT : public ESensorValue<SenseDHT> {

 public:

  TemperatureDHT(SenseDHT *dht, ESensors *sensors=0);

  // The temperature in degrees celsius.
  // On error, return -INFINITY.
  virtual float reading() const;
};


class HumidityDHT : public ESensorValue<SenseDHT> {

 public:

  HumidityDHT(SenseDHT *dht, ESensors *sensors=0);

  // The relative humidity as a fraction.
  // On error, return -INFINITY.
  virtual float reading() const;
};

*/
#endif
