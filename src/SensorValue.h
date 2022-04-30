/*
  SensorValue - Template base class for a sensor reading of a SensorDevice.
  Created by Jan Benda, April 30th, 2022.
*/

#ifndef SensorValue_h
#define SensorValue_h


#include <Arduino.h>
#include <Sensor.h>


// Subclass SensorValue and implement its reading() function to return
// a specific type of sensor reading from S.

// S is a Sensor or SensorDevice that provides multiple types of
// sensor readings.
template <class S>
class SensorValue : public Sensor {

 public:

  SensorValue(S *s,
	      const char *name, const char *symbol,
	      const char *unit, const char *format,
	      float resolution) :
    Sensor(0, name, symbol, unit, format, resolution),
    SDC(s) {};

  SensorValue(S *s, Sensors *sensors,
	      const char *name, const char *symbol,
	      const char *unit, const char *format,
	      float resolution) :
    Sensor(sensors, name, symbol, unit, format, resolution),
    SDC(s) {};

  // Return true if sensor device is available.
  virtual bool available() { return SDC->available(); };

  // Return name of sensor chip model as character array.
  virtual const char* chip() const { return SDC->chip(); };

  // Return unique identifier of sensor chip as character array.
  virtual const char* identifier() const { return SDC->identifier(); };

  // Recommended delay between a request() and get() in milliseconds.
  virtual unsigned long delayTime() const { return SDC->delayTime(); };

  
 protected:

  // Request a sensor conversion.
  virtual void requestData() { return SDC->request(); };

  // Retrieve a sensor reading from the device.
  virtual void getData() { return SDC->get(); };

  // The Sensor or SensorDevice.
  S *SDC;

};


#endif
