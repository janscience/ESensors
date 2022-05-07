/*
  AbsoluteHumidity - DerivedESensor that computes the absolute humidity from humidity and temperature.
  Created by Jan Benda, May 3nd, 2022.
*/

#ifndef AbsoluteHumidity_h
#define AbsoluteHumidity_h


#include <Arduino.h>
#include <DerivedESensor.h>


class AbsoluteHumidity : public DerivedESensor {

 public:

  AbsoluteHumidity(ESensor *humidity, ESensor *temperature, ESensors *sensors=0);

  // Absolute humidity in g/m^3 computed from realtive humidity (fraction)
  // and temperature (degrees celsius).
  virtual float compute(float humidity, float temperature,
			float none=0.0) const;
  
};


#endif
