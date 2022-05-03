/*
  AbsoluteHumidity - SensorDerived that computes the absolute humidity from humidity and temperature.
  Created by Jan Benda, May 3nd, 2022.
*/

#ifndef AbsoluteHumidity_h
#define AbsoluteHumidity_h


#include <Arduino.h>
#include <SensorDerived.h>


class AbsoluteHumidity : public SensorDerived {

 public:

  AbsoluteHumidity(Sensor *humidity, Sensor *temperature, Sensors *sensors=0);

  // Absolute humidity in g/m^3 computed from humidity and temperature.
  virtual float compute(float humidity, float temperature,
			float none=0.0) const;
  
};


#endif
