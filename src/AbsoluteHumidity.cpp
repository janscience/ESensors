#include <AbsoluteHumidity.h>


AbsoluteHumidity::AbsoluteHumidity(ESensor *humidity, ESensor *temperature, ESensors *sensors)
  : DerivedESensor(humidity, temperature, sensors,
		   "absolute humidity", "H", "g/m^3", "%.1f", 0.1) {
}


float AbsoluteHumidity::compute(float humidity, float temperature,
				float none) const {
  // from https://github.com/finitespace/BME280/blob/master/src/EnvironmentCalculations.cpp
  const float mw = 18.01534; 	// molar mass of water g/mol
  const float R = 8.31447215; 	// universal gas constant J/mol/K
  temperature = pow(2.718281828, (17.67 * temperature) / (temperature + 243.5));
  return (6.112 * temperature * 100.0 * humidity * mw)/((273.15 + temperature) * R);
}

