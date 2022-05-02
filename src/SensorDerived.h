/*
  SensorDerived - Base class for sensors computing a derived measure from several Sensors.
  Created by Jan Benda, May 2nd, 2022.
*/

#ifndef SensorDerived_h
#define SensorDerived_h


#include <Arduino.h>


class SensorDerived : public Sensor {

 public:

  // Initialize the sensor and set name, mathematical symbol, basic unit,
  // format, and resolution of sensor readings.
  // Use sensor1.reading() and sensor2.reading() to compute a derived measure.
  SensorDerived(Sensor *sensor1, Sensor *sensor2,
		const char *name, const char *symbol, const char *unit,
		const char *format, float resolution=1.0);

  // Initialize the sensor and set name, mathematical symbol, basic unit,
  // format, and resolution of sensor readings.
  // Use sensor1.reading(), sensor2.reading(), and sensor3.reading()
  // to compute a derived measure.
  SensorDerived(Sensor *sensor1, Sensor *sensor2, Sensor *sensor3,
		const char *name, const char *symbol, const char *unit,
		const char *format, float resolution=1.0);

  // Initialize the sensor, add it to sensors, and set name,
  // mathematical symbol, basic unit, format, and resolution of sensor
  // readings.
  // Use sensor1.reading() and sensor2.reading() to compute a derived measure.
  SensorDerived(Sensor *sensor1, Sensor *sensor2,
		Sensors *sensors, const char *name, const char *symbol,
		const char *unit, const char *format, float resolution=1.0);

  // Initialize the sensor, add it to sensors, and set name,
  // mathematical symbol, basic unit, format, and resolution of sensor
  // readings.
  // Use sensor1.reading(), sensor2.reading(), and sensor3.reading()
  // to compute a derived measure.
  SensorDerived(Sensor *sensor1, Sensor *sensor2, Sensor *sensor3,
		Sensors *sensors, const char *name, const char *symbol,
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
  virtual float reading() const = 0;

  
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
  Sensor *Snsr[MaxSnsr];
  
};


#endif
