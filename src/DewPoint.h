/*
  DewPoint - DerivedESensor that computes the dew point from humidity and temperature.
  Created by Jan Benda, May 3nd, 2022.
*/

#ifndef DewPoint_h
#define DewPoint_h


#include <Arduino.h>
#include <DerivedESensor.h>


class DewPoint : public DerivedESensor {

 public:

  DewPoint(ESensor *humidity, ESensor *temperature, ESensors *sensors=0);

  // Dew point in degrees celsius computed from humidity and temperature.
  virtual float compute(float humidity, float temperature,
			float none=0.0) const;
  
};


#endif
