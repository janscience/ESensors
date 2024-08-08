# Installation

You can install the ESensors library via the Library manager of the
Arduino IDE (Tools menu). Install all its dependencies. That's it!

Make sure that you have a recent Arduino IDE (version > 2.0) and the
corresponding Teensy support (> 1.58). See the [TeeRec installation
instructions](https://github.com/janscience/TeeRec/blob/main/docs/install.md#arduino-ide-and-teensyduino)
for details.

For an installation from the [ESensors github
repository](https://github.com/janscience/ESensors), install all the
libraries ESensors is depending on and then clone the repository, as
described in the following. This is preferred over the installation
via the library manager if you need the latest developments or if you
need to change a few things in the library.


## Dependencies

The ESensors library is based on the following libraries:

- [SparkFun BME280](https://github.com/sparkfun/SparkFun_BME280_Arduino_Library)
- [TSL2591MI](https://bitbucket.org/christandlg/tsl2591mi/)

For installing the libraries for the environmental sensors, open in
the Arduino IDE: Tools - Manage libraries. Search for the libraries
and install them.


## Download from github

If you want the latest development version of ESensors, then instad of
installing the library vie the Arduino IDE, you can clone it directly
from github.

Clone the [ESensors](https://github.com/janscience/ESensors) repository
directly into 'Arduino/libraries':
```sh
cd Arduino/libraries
git clone https://github.com/janscience/ESensors.git
```

For later updates, change into the `Arduino/libraries/ESensors` directory
and pull the updates from the directoy:
```sh
cd Arduino/libraries/ESensors
git pull origin main
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
otherwise the Arduino IDE complains.

Close the Arduino IDE and open it again. Then the Arduino IDE knows
about the ESensors library and its examples.


## Upload new ESensors version to Arduino library manager

See
[TeeRec](https://github.com/janscience/TeeRec/blob/main/docs/install.md#arduino-ide-and-teensyduino)
for instructions on how to upload a new ESensors version to the
Arduino library manager.

