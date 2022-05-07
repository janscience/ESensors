# Sensor classes

- [`SensorDevice`](#sensordevice): Virtual base class for a sensor device.
- [`Sensor`](#sensor): Virtual base class for reading a value from a sensor.
- [`SensorValue`](#sensorvalue): Template base class for a [`Sensor`](#sensor) reading of a [`SensorDevice`(#sensordevice).
- [`SensorDerived`](#sensorderived): Base class for [`Sensor`](#sensor)s computing a derived measure from several [`Sensor`](#sensor)s.
- [`Sensors`](#sensors): Manage mutliple [`Sensor`](#sensor)s.


## SensorDevice

The virtual [SensorDevice class](../src/SensorDevice.h) interfaces a
sensor chip/device. It provides basic infrastructure for requesting
and retrieving sensor readings.

The actual sensor readings need to be accessed via a [Sensor
class](#sensor).

Member functions:

- `chip()`: name of the chip/device.
- `identifier()`: unique ID string.
- `available()`: availability of the chip/device.
- `report()`: print chip() and identifier() on Serial.
- `request()`: request a sensor reading.
- `delayTime()`: minimum time to wait between request() and get().
- `get()`: retrieve a sensor reading from the device and store it in a variable.
- `read()`: blocking read: initiate measurement (request()), wait for delayTime(), and retrieve the data (get()).
- `timeStamp()`: time stamp of last sensor reading.

Available SensorDevices:

- [`LightTSL2591`](chips/tsl2591.md)
- [`SenseBME280`](chips/bme280.md)


## Sensor

A [Sensor](../src/Sensor.h) is a [SensorDevice](#sensordevice) that
provides a single type of sensor reading. A name, symbol, and a unit
are assigned to the sensor reading.

Member functions in addition to [SensorDevice](#sensordevice):

- `name()`, `setName()`: name of the sensor value.
- `symbol()`, `setSymbol()`: mathematical symbol of the sensor value.
- `unit()`, `setUnit()`: unit of the sensor value as set by setUnit().
- `format()`, `setFormat()`: format string for printing out the sensor value.
- `basicUnit()`: unit of the basic sensor reading.
- `resolution()`, `resolutionStr()`: resolution of the sensor readings in the current unit.
- `report()`: report name, symbol, unit, chip and identity of sensor on Serial.
- `reading()`: sensor reading in the basic unit.
- `value()`: sensor reading in the current unit.
- `valueStr()`: sensor reading as a string.
- `read()`: blocking read: request(), delay(), and get(), and return sensor value.

Member functions for unit conversion:

- `setSIPrefix()`
- `setMicro()`
- `setMilli()`
- `setCenti()`
- `setHecto()`
- `setKilo()`
- `setMega()`
- `setPercent()`

Member functions for unit conversion of temperatures:

- `setKelvin`
- `setFahrenheit()`

Member functions for unit conversion of pressures:

- `setBar`
- `setMilliBar()`
- `setAt()`
- `setAtm()`
- `setMMHg()`
- `setPSI()`
- `setTorr()`

Available Sensors:

- `TemperatureDS18x20`


## SensorValue

A [SensorValue](../src/SensorValue.h) is a [Sensor](#sensor) that owns
a [SensorDevice](#sensordevice) and exposes a single type of sensor
reading of this device. See the documentation of the
[SensorDevice](#sensordevice)s listed above for available
[Sensor](#sensor) classes.


## SensorDerived

A [SensorDerived](../src/SensorDerived.h) is a [Sensor](#sensor) that
does not get its readings from a device but computes it from readings
of other sensors.

Available derived sensors are:

- [`AbsoluteHumidity`](../src/AbsoluteHumidity.h): absolute humidity in g/m^3.
- [`DewPoint`](../src/DewPoint.h): dew point in degrees celsius.
- [`SeaLevelPressure`](../src/SeaLevelPressure.h): pressure at sea level in Pascal.


## Sensors

[Sensors](../src/Sensors.h) manages many [Sensor](#sensor)s.

General member functions:

- `addSensor()`: add a [Sensor](#sensor).
- `size()`: the number of managed [Sensor](#sensor)s.
- `sensors()`: the number of currently available [Sensor](#sensor)s.

Control reading of sensor data:

- `start()`: initialize reading from [Sensor](#sensor)s.
- `request()`: request a reading from all [Sensor](#sensor)s.
- `delayTime()`: the maximum delay time of all the [Sensor](#sensor)s.
- `get()`: get sensor readings from all [Sensor](#sensor)s.
- `read()`: blocking read: `request()`, `delay()`, and `get()`.
- `timeStamp()`: time stamp of last sensor reading.
- `interval()`, `setInterval()`: time interval for repetitive reads used in `update()`.
- `update()`: non-blocking control of requests and gets for all [Sensor](#sensor)s.

Output on Serial:

- `report()`: report properties (name, unit, chip, etc. ) of managed [Sensor](#sensor)s on Serial.
- `setPrintTime()`: control whether and how time stamps are reported.
- `print()`: print sensor names, readings, and units on Serial.
- `printHeader()`: print header with sensor names and units on Serial.
- `printValues()`: print sensor readings on Serial.

Log sensor data into CSV file:

- `openCSV()`: open CSV file on SD card and write header.
- `pendingCSV()`: check whether data buffer is ready for being written to SD card.
- `writeCSV()`: write data buffer to CSV file.
- `closeCSV()`: close CSV file.
