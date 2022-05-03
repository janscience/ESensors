#include <SeaLevelPressure.h>


SeaLevelPressure::SeaLevelPressure(Sensor *pressure, Sensor *temperature,
				   float altitude, Sensors *sensors)
  : SensorDerived(pressure, temperature, sensors,
		  "sea level pressure", "P0", "Pa", "%5.1f", 1.0),
    Altitude(altitude) {
  setFormat(pressure->format());
}


float SeaLevelPressure::compute(float pressure, float temperature,
				float none) const {
  // see https://keisan.casio.com/exec/system/1224575267
  // derivation: https://keisan.casio.com/keisan/image/Convertpressure.pdf
  return pressure / pow(1.0 - ((0.0065 * Altitude) / (temperature + (0.0065 * Altitude) + 273.15)), 5.257);
}
