# Sensors

[Hard-](docs/) and software for environmental sensors (air and water)
for Teensy and Arduino.


## Sensors library

- [Sensors](src/Sensors.h): Manage environmental sensors.
- [SensorDevice](src/SensorDevice.h): Virtual base class for a sensor device.
- [Sensor](src/Sensor.h): Virtual base class for reading a value from a sensor.
- [SensorValue](src/SensorValue.h): Template base class for a sensor reading of a SensorDevice.
- [SensorDerived](src/SensorDerived.h): Base class for sensors computing a derived measure from several Sensors.

- [AbsoluteHumidity](src/AbsoluteHumidity.h): Compute absolute humidity from relative humidity and temperature.
- [DewPoint](src/DewPoint.h): Compute dew point from relative humidity and temperature.
- [SeaLevelPressure](src/SeaLevelPressure.h): Estimate sea level pressure from pressure, temperature, and known altitude.

- [TemperatureDS18x20](src/TemperatureDS18x20.h): A Sensor that reads temperature from a DS18x20 1-wire device.
- [SenseBME280](src/SenseBME280.h): The Bosch BME280 temperature, humidity, and pressure sensor with many derived measures.
- [LightTSL2591](src/LightTSL2591.h): Read light intensity from AMS TSL2591.


## Documentation

- [Installation instructions](docs/install.md)
- [User guide](docs/userguide.md)

The [Documentation](docs/) also provides resources on [environmental
parameters](docs/parameters/), [sensor chips](docs/chips/), and [power
supply](docs/power/):

- [Environmental parameters](docs/parameters/): Infos on how two measure
  environmental parameters.
- [Sensor chips](docs/chips/): Development boards and librariers for
  sensor chips.
- [Power supply](docs/power/): Some solutions for power supply.


## Examples

In [examples/](examples) you find sketches demonstrating the use of
the Sensors libraries.

- [sensors](examples/sensors): read sensors and write readings to serial.
- [logger](examples/logger): periodically write sensor readings with time stamp into a CSV file.
- [snoozelogger](examples/snoozelogger): same as [logger example](examples/logger), but with hibernate between sensor readings.


## Utilities

In [utils/](utils) you find useful python scripts.

- [sensors](utils/sensors): plot the content of the csv file written by the [Sensors](src/Sensors.h) library.


## Applications of the Sensors libraries

Sensors is used in:

- [TeeGrid](https://github.com/janscience/TeeGrid): Electrode arrays
  based on 8-16channel recording devices for recording electric fish
  behavior in natural habitats (see [Henninger et
  al. 2018](https://doi.org/10.1523/JNEUROSCI.0350-18.2018) and
  [Henninger et al. 2020](https://doi.org/10.1242/jeb.206342)).

Further planed applications are:

- Fishfinder: A replacement for the usual and horrible RadioShack/MP3
  player combination for recording electric fish EODs in their natural
  habitats with lot's of additional features (display, online
  analysis, environmental parameters).
