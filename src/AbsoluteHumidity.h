/*
  AbsoluteHumidity - SensorDerived that computes the absolute humidity from temperature and humidity.
  Created by Jan Benda, May 3nd, 2022.
*/

#ifndef AbsoluteHumidity_h
#define AbsoluteHumidity_h


#include <Arduino.h>
#include <SensorDerived.h>


class AbsoluteHumidity : public SensorDerived {

 public:

  AbsoluteHumidity(Sensor *temperature, Sensor *humidity, Sensors *sensors=0);

  // Absolute humidity in g/m^3.
  virtual float compute(float temperature, float humidity,
			float none=0.0) const;
  
};


#endif
