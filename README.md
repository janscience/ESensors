# TeeSense

Hard- and software for environmental sensors (air and water) for Teensy.

## Air

- [air pressure](airpressure/)
- [light](light/)
- [rain](rain/)

## Water

- [water conductivity](conductivity/)
- [turbitity](turbitity/)
- [water velocity](velocity/)
- [water level](waterlevel/)


## Libraries

First, search in the library manager of the Arduino IDE for the name
of the sensor chip. You usually get a wide selection of libraries, many of
them will work out of the box.

They differ in the bus protocols they support (mostly I2C or SPI or
both) and on which libraries they rely on for the bus protocols.

Criteria for selecting the right library:
- is it working on the Teensy, i.e. does it rely on the right bus librariers?
  (just install the library and run an example sketch)
- is there support for multiple I2C bus systems (e.g. `Wire1` in addition to the standard `Wire`)?
- how well and in which language is the library documented?
- is the library alive? (on the other hand, these libraries are usualy
  so simple that they do not really need to be mainted).

For our purpuses we do not need support for thresholds, alarms,
interrupts, etc. We are only interested in the sensor values.


## General resources

- [Fondriest: environmental
  measurements](https://www.fondriest.com/environmental-measurements/):
  background to many environmental parameters and how to measure them
- [Robust, low-cost data loggers for stream temperature, flow intermittency, and relative conductivity monitoring](https://agupubs.onlinelibrary.wiley.com/doi/pdf/10.1002/2013WR015158)
