/*
  ESensorValue - Template base class for a sensor reading of an ESensorDevice.
  Created by Jan Benda, April 30th, 2022.
*/

#ifndef ESensorValue_h
#define ESensorValue_h


#include <Arduino.h>
#include <ESensor.h>


// Subclass ESensorValue and implement its reading() function to return
// a specific type of sensor reading from S.

// S is a ESensor or ESensorDevice that provides multiple types of
// sensor readings.
template <class S>
class ESensorValue : public ESensor {

 public:

  ESensorValue(S *s, const char *name, const char *symbol,
	       const char *unit, const char *format,
	       float resolution) :
    ESensor(0, name, symbol, unit, format, resolution),
    SDC(s) {};

  ESensorValue(S *s, ESensors *sensors,
	       const char *name, const char *symbol,
	       const char *unit, const char *format,
	       float resolution) :
    ESensor(sensors, name, symbol, unit, format, resolution),
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

  // The ESensor or ESensorDevice.
  S *SDC;

};


#endif
