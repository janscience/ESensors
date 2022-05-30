# Sensor chips

## Temperature

- [Dallas DS18x20](ds18x20.md)

## Pressure

- [Bosch Sensortec BME280](bme280.md)


## Light intensity

- [AMS TSL2591 light-to-digital converter](tsl2591.md)
- [BH1750 ambient light sensor](bh1750.md)


## How to find and select libraries for specific chips

First, search in the library manager of the Arduino IDE for the name
of the sensor chip. You usually get a wide selection of libraries, many of
them will work out of the box.

Criteria for selecting the right library:
- does the library support non-blocking retrieval of sensor value?
- is there support for multiple I2C bus systems (e.g. `Wire1` in addition to the standard `Wire`)?
- does the library support low power modes of the sensor chip (sleep - request data - wait - get data - sleep)?
- is it working on the Teensy, i.e. does it rely on the right bus librariers?
  (usually no problem, just install the library and run an example sketch
  to check)
- how well and in which language is the library documented?
- is the library alive? (on the other hand, these libraries are usualy
  so simple that they do not really need to be mainted).

For our purposes:
- we are only interested in the sensor values.
- we only require SI units.
- we do not need support for thresholds, alarms, interrupts, etc.
- we can easily compute derived measures ourselves.

