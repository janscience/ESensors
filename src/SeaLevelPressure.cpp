#include <SeaLevelPressure.h>


SeaLevelPressure::SeaLevelPressure(ESensor *pressure, ESensor *temperature,
				   float altitude, ESensors *sensors)
  : DerivedESensor(pressure, temperature, sensors,
		   "sea level pressure", "P0", "Pa", "%5.1f", 1.0),
    Altitude(altitude) {
  setFormat(pressure->format());
}


float SeaLevelPressure::compute(float pressure, float temperature,
				float none) const {
  return pressure / pow(1.0 - ((0.0065 * Altitude) / (temperature + (0.0065 * Altitude) + 273.15)), 5.257);
}
