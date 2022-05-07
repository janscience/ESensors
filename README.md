![arduino-lint](https://github.com/janscience/ESensors/actions/workflows/arduino-lint.yml/badge.svg)

# ESensors

A library and background information for environmental sensors (air
and water) for Teensy and Arduino.


## [ESensors](https://github.com/janscience/ESensors) library

- [Installation instructions](docs/install.md)
- [User guide](docs/userguide.md)
- [Class overview](docs/classes.md)
- [Sensor chips](docs/chips/): Infos on development boards and libraries for
  specific sensor chips.


## Environmental parameters

- [Parameters](docs/parameters/): Infos on how two measure
  environmental parameters.


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


## Applications of the ESensors libraries

ESensors is used in:

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
