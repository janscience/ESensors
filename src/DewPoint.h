/*
  DewPoint - SensorDerived that computes the dew point from humidity and temperature.
  Created by Jan Benda, May 3nd, 2022.
*/

#ifndef DewPoint_h
#define DewPoint_h


#include <Arduino.h>
#include <SensorDerived.h>


class DewPoint : public SensorDerived {

 public:

  DewPoint(Sensor *humidity, Sensor *temperature, Sensors *sensors=0);

  // Dew point in degrees celsius computed from humidity and temperature.
  virtual float compute(float humidity, float temperature,
			float none=0.0) const;
  
};


#endif
