#include <DewPoint.h>


DewPoint::DewPoint(ESensor *humidity, ESensor *temperature, ESensors *sensors)
  : DerivedESensor(humidity, temperature, sensors,
		   "dew point", "Tdp", "ºC", "%5.1f", 0.35) {
}


float DewPoint::compute(float humidity, float temperature,
			float none) const {
  // Magnus formula with Arden Buck equation:
  const float b = 18.678;
  const float c = 257.14;
  const float d = 234.5;
  float gamma = log(humidity*exp((b-temperature/d)*(temperature/(c+temperature))));
  return c * gamma/(b - gamma);
}

