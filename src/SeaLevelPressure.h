/*
  SeaLevelPressure - SensorDerived that computes the equivalent sea level pressure from pressure and temperature.
  Created by Jan Benda, May 3nd, 2022.
*/

#ifndef SeaLevelPressure_h
#define SeaLevelPressure_h


#include <Arduino.h>
#include <SensorDerived.h>


class SeaLevelPressure : public SensorDerived {

 public:

  // Provide altitude in meter.
  SeaLevelPressure(Sensor *pressure, Sensor *temperature, float altitude,
		   Sensors *sensors=0);

  // The equivalent sea level pressure in Pascal
  // computed from pressure and temperature.
  virtual float compute(float pressure, float temperature,
			float none=0.0) const;

protected:

  float Altitude;

};


#endif
