/*
  ESensorValue - Template base class for a sensor reading of an ESensorDevice.
  Created by Jan Benda, April 30th, 2022.
*/

#ifndef ESensorValue_h
#define ESensorValue_h


#include <Arduino.h>
#include <ESensor.h>


// Subclass ESensorValue and implement its reading() function to return
// a specific type of sensor reading from ESensorDevice class S.
// S is a ESensor or ESensorDevice that provides multiple types of
// sensor readings.
template <class S>
class ESensorValue : public ESensor {

 public:

  ESensorValue(S *s, const char *name, const char *symbol,
	       const char *unit, const char *format,
	       float resolution) :
    ESensor(0, name, symbol, unit, format, resolution),
    SDev(s) {};

  ESensorValue(S *s, ESensors *sensors,
	       const char *name, const char *symbol,
	       const char *unit, const char *format,
	       float resolution) :
    ESensor(sensors, name, symbol, unit, format, resolution),
    SDev(s) {};

  // Return the sensor device.
  virtual ESensorDevice *device();

  // Return true if sensor device is available.
  virtual bool available() { return SDev->available(); };

  // Bus controlling the sensor device.
  virtual BUS bus() const { return SDev->bus(); };

  // Address on I2C bus.
  virtual unsigned int address() const { return SDev->address(); };

  // Pin of OneWire bus or chip select pin of device on SPI bus.
  virtual int pin() const { return SDev->pin(); };

  // Return name of sensor chip model as character array.
  virtual const char* chip() const { return SDev->chip(); };

  // Return unique identifier of sensor chip as character array.
  virtual const char* identifier() const { return SDev->identifier(); };

  // Recommended delay between a request() and get() in milliseconds.
  virtual unsigned long delayTime() const { return SDev->delayTime(); };

  
 protected:

  // Request a sensor conversion.
  virtual void requestData() { return SDev->request(); };

  // Retrieve a sensor reading from the device.
  virtual void getData() { return SDev->get(); };

  // The ESensor or ESensorDevice.
  S *SDev;

};


template <class S>
ESensorDevice *ESensorValue<S>::device() {
  return SDev;
}


#endif
