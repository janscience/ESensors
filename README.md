![arduino-lint](https://github.com/janscience/ESensors/actions/workflows/arduino-lint.yml/badge.svg)

# ESensors

A library for environmental sensors (air and water) for Teensy and
Arduino with additional background information.


## [ESensors](https://github.com/janscience/ESensors) library


### Features

- Blocking and non-blocking reads from many sensors in parallel.
- Sensor readings in adaptable units.
- Output of sensor properties and readings on Serial and into CSV files on SD card.
- Hardware independent derived measures, like for example, dew point and absolute humidity.

### Currently supported sensors

- [BH1750](docs/chips/bh1750.md): [light intensity](docs/parameters/light/md)
- [BME280](docs/chips/bme280.md): [air pressure](docs/parameters/airpressure.md), [temperature](docs/parameters/temperature.md), and [humidity](docs/parameters/humidity.md)
- [DS18x20](docs/chips/ds18x20.md): [temperature](docs/parameters/temperature.md)
- [TSL2591](docs/chips/tsl2591.md): [light intensity](docs/parameters/light/md)


### Documentation

- [Installation instructions](docs/install.md)
- [User guide](docs/userguide.md)
- [Class overview](docs/classes.md)
- [Sensor chips](docs/chips/): Infos on development boards and libraries for
  specific sensor chips.


## Environmental parameters

- [Parameters](docs/parameters/): Infos on principles, methods, and
  available chips for measuring various environmental parameters.


## Power supply

- [Power supply](docs/power/): Some solutions for power supply.


## Examples

In [examples/](examples) you find sketches demonstrating the use of
the ESensors library.

- [sensors](examples/sensors): read sensors and write readings to serial.
- [logger](examples/logger): periodically write sensor readings with time stamp into a CSV file.
- [snoozelogger](examples/snoozelogger): same as [logger example](examples/logger), but with hibernate between sensor readings.


## Utilities

In [utils/](utils) you find useful python scripts.

- [sensors.py](utils/sensors.py): plot the content of the csv file written by the [ESensors](doc/classes.md#esensors) library.


## Applications of the ESensors library

ESensors is used in:

- [EOD-Logger](https://github.com/janscience/EOD-Logger): A 2-electrode
  logger for recording electric-organ discharges of electric fish.

- [TeeGrid](https://github.com/janscience/TeeGrid): Electrode arrays
  based on 8-16channel recording devices for recording electric fish
  behavior in natural habitats (see [Henninger et
  al. 2018](https://doi.org/10.1523/JNEUROSCI.0350-18.2018) and
  [Henninger et al. 2020](https://doi.org/10.1242/jeb.206342)).

- [FishFinder](https://github.com/janscience/FishFinder): A
  replacement for the usual and horrible RadioShack/MP3 player
  combination for recording electric fish EODs in their natural
  habitats with lot's of additional features (display, online
  analysis, acoustiv feedabck, environmental parameters).
