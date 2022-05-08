# Humidity

Relative humidity, RH, measured in percent. 

[Wikipedia](https://en.wikipedia.org/wiki/Humidity)


## Hardware

- [Bosch BME280](../chips/bme280.md) is the best!

- [Testing Various Low-Cost Hygrometers](https://www.kandrsmith.org/RJS/Misc/hygrometers.html)

- [Comparison](https://www.kandrsmith.org/RJS/Misc/Hygrometers/calib_many.html)

- Texas Instruments HDC1080


## Absolute humidity

Mass of water vapor in a given volume of air.

See [EnvironmentCalculations.cpp](https://github.com/finitespace/BME280/blob/master/src/EnvironmentCalculations.cpp) for conversion from relative humidity.

Implemented in [class AbsoluteHumidity](../../src/AbsoluteHumidity.h).


## Dew point

Temperature below which airborne water vapor condenses.

Computed from relative humidity and temperature. See
[wikipedia](https://en.wikipedia.org/wiki/Dew_point)
for details.

The dew point *T<sub>dp</sub>* can be computed
from relative humidity (*RH*, given as a fraction, not percent) and temperature *T* in degrees celsius according to Magnus formula

![Magnus](images/magnus-formula.svg)

with *b* = 17.62 and *c* = 243.12°C.

An improved approximation of *&gamma;(T,RH)* is

![Magnus Arden Buck](images/magnus-arden-buck.svg)

with *b* = 18.678, *c* = 257.14°C, *d* = 234.5°C.

The latter is implemented in [class DewPoint](../../src/DewPoint.h).
