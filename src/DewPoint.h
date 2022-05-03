/*
  DewPoint - SensorDerived that computes the dew point from temperature and humidity.
  Created by Jan Benda, May 3nd, 2022.
*/

#ifndef DewPoint_h
#define DewPoint_h


#include <Arduino.h>
#include <SensorDerived.h>


class DewPoint : public SensorDerived {

 public:

  DewPoint(Sensor *temperature, Sensor *humidity, Sensors *sensors=0);

  // The dew point in degrees celsius.
  virtual float compute(float temperature, float humidity,
			float none=0.0) const;
  
};


#endif
