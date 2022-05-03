# Installation

First, make sure that you install all the libraries needed by Sensors.


## Dependencies

Sensors is based on the following libraries:

- [SdFat version2](https://github.com/greiman/SdFat)
- [SparkFun BME280](https://github.com/sparkfun/SparkFun_BME280_Arduino_Library)
- [TSL2591MI](https://bitbucket.org/christandlg/tsl2591mi/)

The [SdFat version2](https://github.com/greiman/SdFat) library is
already included in
[Teensyduino](https://www.pjrc.com/teensy/teensyduino.html). When
installing Teensyduino make sure you selected it.

_Note_: you need Arduino 1.8.19 and Teensyduoino 1.56 or higher! When
installing Teensyduoino simply select all libraries for installation.
Remove `SdFat` from your `Arduino/libraries` folder, it is now
supplied by Teensyduoino.

For installing the libraries for the environmental sensors, open in
the Arduino IDE: Tools - Manage libraries. Search for the libraries
and install them.


## Installation

Clone the [Sensors](https://github.com/janscience/Sensors) repository
directly into 'Arduino/libraries':
```sh
cd Arduino/libraries
git clone https://github.com/janscience/Sensors.git
```

Alternatively, download the whole repository as a zip archive (open
https://github.com/janscience/Sensors in your browser and click on the
green "Code" button). Unpack the zip file:
```sh
cd Arduino/libraries
unzip ~/Downloads/Sensors-main.zip
```

If you want to edit the Sensors files, mark the library as developmental:
```sh
cd Arduino/libraries/Sensors
touch .development
```

Close the Arduino IDE and open it again. Then the Arduino IDE knows
about the Sensors library and its examples.
