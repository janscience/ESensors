#include <DewPoint.h>


DewPoint::DewPoint(ESensor *humidity, ESensor *temperature, ESensors *sensors)
  : DerivedESensor(humidity, temperature, sensors,
		   "dew point", "Tdp", "ºC", "%5.1f", 0.35) {
}


float DewPoint::compute(float humidity, float temperature,
			float none) const {
  const float b = 17.62;
  const float c = 243.12;
  float gamma = log(humidity) + (b * temperature)/(c + temperature);
  return c * gamma/(b - gamma);
}

