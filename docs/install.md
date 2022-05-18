# Installation

You can install the ESensors library via the Library manager of the
Arduino IDE (Tools menu). Install all its dependencies. That's it!

For a manual installation from the [ESensors github
repository](https://github.com/janscience/ESensors), install all the
libraries ESensors is depending on and then clone the repository, as
described in the following.


## Dependencies

The ESensors library is based on the following libraries:

- [SdFat version2](https://github.com/greiman/SdFat)
- [SparkFun BME280](https://github.com/sparkfun/SparkFun_BME280_Arduino_Library)
- [TSL2591MI](https://bitbucket.org/christandlg/tsl2591mi/)

The [SdFat version2](https://github.com/greiman/SdFat) library is
already included in
[Teensyduino](https://www.pjrc.com/teensy/teensyduino.html). When
installing Teensyduino make sure you selected it.

_Note_: you need Arduino 1.8.19 and Teensyduino 1.56 or higher! When
installing Teensyduino simply select all libraries for installation.
Remove `SdFat` from your `Arduino/libraries` folder, it is now
supplied by Teensyduino.

For installing the libraries for the environmental sensors, open in
the Arduino IDE: Tools - Manage libraries. Search for the libraries
and install them.


## Installation

Clone the [ESensors](https://github.com/janscience/ESensors) repository
directly into 'Arduino/libraries':
```sh
cd Arduino/libraries
git clone https://github.com/janscience/ESensors.git
```

Alternatively, download the whole repository as a zip archive (open
https://github.com/janscience/ESensors in your browser and click on the
green "Code" button). Unpack the zip file:
```sh
cd Arduino/libraries
unzip ~/Downloads/ESensors-main.zip
```

If you want to edit the ESensors files, mark the library as developmental:
```sh
cd Arduino/libraries/ESensors
touch .development
```

Close the Arduino IDE and open it again. Then the Arduino IDE knows
about the ESensors library and its examples.
