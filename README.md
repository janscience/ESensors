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


## Environmental parameters

### Air

- [temperature](doc/parameters/temperature/)
- [humidity](doc/parameters/humidity/)
- [air pressure](doc/parameters/airpressure/)
- [light](doc/parameters/light/)
- [rain](doc/parameters/rain/)

### Water

- [water conductivity](doc/parameters/conductivity/)
- [turbitity](doc/parameters/turbitity/)
- [water velocity](doc/parameters/velocity/)
- [water level](doc/parameters/waterlevel/)


## General resources

- [Fondriest: environmental
  measurements](https://www.fondriest.com/environmental-measurements/):
  background to many environmental parameters and how to measure them
- [Robust, low-cost data loggers for stream temperature, flow intermittency, and relative conductivity monitoring](https://agupubs.onlinelibrary.wiley.com/doi/pdf/10.1002/2013WR015158)
- [microSoundRecorder](https://github.com/WMXZ-EU/microSoundRecorder) - Environmental Sound Recorder for Teensy 3.6:
  [[github]](https://github.com/WMXZ-EU/microSoundRecorder)
  [[wiki]](https://github.com/WMXZ-EU/microSoundRecorder/wiki/Hardware-setup)
  [[forum]](https://forum.pjrc.com/threads/52175?p=185386&viewfull=1#post185386)


## Power supply

The sensors and the Teensy need some power to run. [Read more.](doc/power/)


## How to find and select libraries for specific chips

First, search in the library manager of the Arduino IDE for the name
of the sensor chip. You usually get a wide selection of libraries, many of
them will work out of the box.

They differ in the bus protocols they support (mostly I2C or SPI or
both) and on which libraries they rely on for the bus protocols.

Criteria for selecting the right library:
- is it working on the Teensy, i.e. does it rely on the right bus librariers?
  (just install the library and run an example sketch)
- is there support for multiple I2C bus systems (e.g. `Wire1` in addition to the standard `Wire`)?
- does the library support low power modes (sleep - request data - wait - get data - sleep)?
- how well and in which language is the library documented?
- is the library alive? (on the other hand, these libraries are usualy
  so simple that they do not really need to be mainted).

For our purpuses:
- we are only interested in the sensor values.
- we only require SI units.
- we do not need support for thresholds, alarms, interrupts, etc.
- derived measures do not even be calculated by the microcontroller.

