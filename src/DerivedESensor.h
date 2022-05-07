/*
  DerivedESensor - Base class for sensors computing a derived measure from several Sensors.
  Created by Jan Benda, May 2nd, 2022.
*/

#ifndef DerivedESensor_h
#define DerivedESensor_h


#include <Arduino.h>
#include <ESensor.h>


class DerivedESensor : public ESensor {

 public:

  // Initialize the sensor and set name, mathematical symbol, basic unit,
  // format, and resolution of sensor readings.
  // Use sensor1.reading() and sensor2.reading() to compute a derived measure.
  DerivedESensor(ESensor *sensor1, ESensor *sensor2,
		 const char *name, const char *symbol, const char *unit,
		 const char *format, float resolution=1.0);

  // Initialize the sensor and set name, mathematical symbol, basic unit,
  // format, and resolution of sensor readings.
  // Use sensor1.reading(), sensor2.reading(), and sensor3.reading()
  // to compute a derived measure.
  DerivedESensor(ESensor *sensor1, ESensor *sensor2, ESensor *sensor3,
		 const char *name, const char *symbol, const char *unit,
		 const char *format, float resolution=1.0);

  // Initialize the sensor, add it to sensors, and set name,
  // mathematical symbol, basic unit, format, and resolution of sensor
  // readings.
  // Use sensor1.reading() and sensor2.reading() to compute a derived measure.
  DerivedESensor(ESensor *sensor1, ESensor *sensor2,
		 ESensors *sensors, const char *name, const char *symbol,
		 const char *unit, const char *format, float resolution=1.0);

  // Initialize the sensor, add it to sensors, and set name,
  // mathematical symbol, basic unit, format, and resolution of sensor
  // readings.
  // Use sensor1.reading(), sensor2.reading(), and sensor3.reading()
  // to compute a derived measure.
  DerivedESensor(ESensor *sensor1, ESensor *sensor2, ESensor *sensor3,
		 ESensors *sensors, const char *name, const char *symbol,
		 const char *unit, const char *format, float resolution=1.0);

  // Return name of sensor chip models as character array.
  virtual const char* chip() const;

  // Return unique identifiers of sensor chips as character array.
  virtual const char* identifier() const;
  
  // Return true if sensors are available.
  virtual bool available();

  // Recommended delay between a request() and get().
  virtual unsigned long delayTime() const;

  // The sensor reading in the basic unit.
  // On error, return -INFINITY.
  // Calls compute() with the respective sensor readings.
  virtual float reading() const;

  // Compute the derived sensor quantity from sensor readings.
  // The values are passed in the same order as the Sensors
  // were provided to the constructer.
  virtual float compute(float sensor1, float sensor2, float sensor3=0.0) const = 0;

  
protected:

  // Request a sensor reading.
  virtual void requestData();

  // Implement this function to retrieve a sensor reading from the
  virtual void getData();

  mutable char DChip[3*MaxStr];
  mutable char DIdentifier[3*MaxStr];

  // The sensors with the primary data:
  size_t NSnsr;
  static const size_t MaxSnsr = 3;
  ESensor *Snsr[MaxSnsr];
  
};


#endif
