/*
  SeaLevelPressure - DerivedESensor that computes the equivalent sea level pressure from pressure and temperature.
  Created by Jan Benda, May 3nd, 2022.
*/

#ifndef SeaLevelPressure_h
#define SeaLevelPressure_h


#include <Arduino.h>
#include <DerivedESensor.h>


class SeaLevelPressure : public DerivedESensor {

 public:

  // Provide altitude in meter.
  SeaLevelPressure(ESensor *pressure, ESensor *temperature, float altitude,
		   ESensors *sensors=0);

  // The equivalent sea level pressure in Pascal
  // computed from pressure and temperature.
  // see https://keisan.casio.com/exec/system/1224575267
  // derivation: https://keisan.casio.com/keisan/image/Convertpressure.pdf
  virtual float compute(float pressure, float temperature,
			float none=0.0) const;

protected:

  float Altitude;

};


#endif
