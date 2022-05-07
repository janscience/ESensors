# Sensor classes

## SensorDevice

The [SensorDevice class](../src/SensorDevice.h) interfaces a sensor
chip/device. It provides basic infrastructure for requesting and
retrieving sensor readings.

The actual sensor readings need to be accessed via a Sensor class.

Member functions:

- `chip()`: name of the chip/device.
- `identifier()`: unique ID string.
- `available()`: availability of the chip/device.
- `report()`: print chip() and identifier() on Serial.
- `request()`: request a sensor reading.
- `delayTime()`: minimum time to wait between request() and get().
- `get()`: retrieve a sensor reading from the device and store it in a variable.
- `read()`: initiate measurement (request()), wait for delayTime(), and retrieve the data (get()).
- `timeStamp()`: time stamp of last sensor reading.

Available SensorDevices:

- [`LightTSL2591`](chips/tsl2591md)
- [`SenseBME280`](chips/bme280.md)


## Sensor

A Sensor is a SensorDevice that provides a single type of sensor
reading. A name, symbol, and a unit are assigned to the sensor
reading.

Member functions in addition to SensorDevice:

- `name()`, `setName()`: name of the sensor value.
- `symbol()`, `setSymbol()`: mathematical symbol of the sensor value.
- `unit()`, `setUnit()`: unit of the sensor value as set by setUnit().
- `format()`, `setFormat()`: format string for printing out the sensor value.
- `basicUnit()`: unit of the basic sensor reading.
- `resolution()`, `resolutionStr()`: resolution of the sensor readings in the current unit.
- `report()`: report name, symbol, unit, chip and identity of sensor on Serial.
- `reading()`: sensor reading in the basic unit.
- `value()`: sensor reading in the current unit.
- `valueStr()`: sensor reading as string.
- `read()`: request(), delay(), and get(), and return sensor value.

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

A sensor that owns a SensorDevice and exposes a single type of sensor
reading of this device. See the documentation of the SensorDevices
listed above for a list of available classes.


## SensorDerived

A Sensor that does not get its readings from a device but computes it
from readings of various sensors.

Available derived sensors are:

- `AbsoluteHumidity`
- `DewPoint`
- `SeaLevelPressure`


## Sensors

Container managing many Sensors.

Member functions:

- `addSensor()`:
- `size()`:
- `sensors()`:
- `interval()`, `setInterval()`:
- `report()`:
- `start()`:
- `request()`:
- `delayTime()`:
- `get()`:
- `update()`:
- `read()`:
- `setPrintTime()`:
- `print()`:
- `printHeader()`:
- `printValues()`:
- `openCSV()`:
- `pendingCSV()`:
- `writeCSV()`:
- `closeCSV()`:
