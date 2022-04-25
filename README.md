# TeeSense

Hard- and software for environmental sensors (air and water) for Teensy.


## Sensors library

- [Sensors](src/Sensors.h): Manage environmental sensors.
- [Sensor](src/Sensor.h): Virtual base class for environmental sensors.
- [TemperatureDS18x20](src/TemperatureDS18x20.h): A Sensor that reads temperature from a DS18x20 1-wire device.
- [SenseBME280](src/SenseBME280.h): The Bosch BME280 temperature, humidity, and pressure sensor with many derived measures.


## Examples

In [examples/](examples) you find sketches demonstrating the use of
the TeeSense libraries.

- [sensors](examples/sensors): read sensors and write readings to serial.
- [logger](examples/logger): periodically write sensor readings with time stamp into a CSV file.


## Utilities

In [utils/](utils) you find some useful python scripts.

- [sensors](utils/sensors): plot the content of the csv file written by the [Sensors](src/Sensors.h) library.


## Documentation

The [Documentation](docs/) provides resources on [environmental
parameters](docs/parameters/), [sensor chips](docs/chips/), and [power
supply](docs/power/).

- [Environmental parameters](docs/parameters/): Infos on how two measure
  environmental parameters.
- [Sensor chips](docs/chips/): Development boards and librariers for
  sensor chips.
- [Power supply](docs/power/): Some solutions for power supply.


## Dependencies

TeeSense is based on the following libraries:

- [SdFat version2](https://github.com/greiman/SdFat)
- [SparkFun BME280](https://github.com/sparkfun/SparkFun_BME280_Arduino_Library)

The [SdFat version2](https://github.com/greiman/SdFat) library is
already included in
[Teensyduino](https://www.pjrc.com/teensy/teensyduino.html). When
installing Teensyduino make sure you selected it.

_Note_: you need Arduino 1.8.19 and Teensyduoino 1.56 or higher! When
installing Teensyduoino simply select all libraries for installation.
Remove `SdFat` from your `Arduino/libraries` folder, they are now
supplied by Teensyduoino.

For installing the libraries for the environmental sensors, open in
the Arduino IDE: Tools - Manage libraries. Search for the libraries
and install them.


## Installation

Clone the [TeeSense](https://github.com/janscience/TeeSense) repository
directly into 'Arduino/libraries':
```sh
cd Arduino/libraries
git clone https://github.com/janscience/TeeSense.git
```

Alternatively, download the whole repository as a zip archive (open
https://github.com/janscience/TeeSense in your browser and click on the
green "Code" button). Unpack the zip file:
```sh
cd Arduino/libraries
unzip ~/Downloads/TeeSense-main.zip
```

If you want to edit the TeeSense files, mark the library as developmental:
```sh
cd Arduino/libraries/TeeSense
touch .development
```

Close the Arduino IDE and open it again. Then the Arduino IDE knows
about the TeeSense library and its examples.


## Applications of the TeeSense libraries

TeeRec is used in:

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
