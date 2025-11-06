# ESensor classes

- [`ESensorDevice`](#esensordevice): Virtual base class for an environmental sensor device.
- [`ESensor`](#esensor): Virtual base class for reading a value from an environmental sensor.
- [`ESensorValue`](#esensorvalue): Template base class for a [`ESensor`](#esensor) reading of a [`ESensorDevice`](#esensordevice).
- [`DerivedESensor`](#derivedesensor): Base class for [`ESensor`](#esensor)s computing a derived measure from other [`ESensor`](#esensor)s.
- [`ESensors`](#esensors): Manage mutliple [`ESensor`](#esensor)s.


## ESensorDevice

The virtual [ESensorDevice class](../src/ESensorDevice.h) interfaces a
sensor chip/device. It provides basic infrastructure for requesting
and retrieving sensor readings and for handling a device's metadata.

The actual sensor readings need to be accessed via a [ESensor
class](#esensor) - see [ESensorValue](#esensorvalue) below.

Member functions:

- `chip()`: name of the chip/device.
- `identifier()`: unique ID string.
- `bus()`, `busStr()`: bus that controls the chip.
- `address()`: address of the chip on an I2C bus.
- `pin()`: pin of the chip on an SPI or OneWire bus.
- `available()`: availability of the chip/device.
- `report()`: print chip(), bus(), address() or pin() and identifier() on stream.
- `request()`: request a sensor reading.
- `delayTime()`: minimum time to wait between request() and get().
- `retrieve()`: retrieve sensor data over an extended period of time.
- `get()`: get a sensor reading from the device and store it in a variable.
- `read()`: blocking read: initiate measurement (request()), wait for delayTime(), and retrieve the data (get()).
- `timeStamp()`: time stamp of last sensor reading.
- `metadata()`: the number of key-value pairs available in the device's metadata.
- `key()`: return key of the index-th metadata entry.
- `value()`: return value of the index-th metadata entry.

Available ESensorDevices:

- [`LightTSL2591`](chips/tsl2591.md)
- [`SenseBME280`](chips/bme280.md)
- [`SenseDHT`](chips/dht.md)


## ESensor

An [ESensor](../src/Sensor.h) is an [ESensorDevice](#esensordevice) that
provides a single type of sensor reading. A name, symbol, and a unit
are assigned to the sensor reading.

Member functions in addition to [ESensorDevice](#esensordevice):

- `name()`, `setName()`: name of the sensor value.
- `symbol()`, `setSymbol()`: mathematical symbol of the sensor value.
- `unit()`, `setUnit()`: unit of the sensor value as set by setUnit().
- `format()`, `compactFormat()`, `setFormat()`: format strings for printing out the sensor value.
- `basicUnit()`: unit of the basic sensor reading.
- `resolution()`, `resolutionStr()`: resolution of the sensor readings in the current unit.
- `report()`: report name, symbol, unit, resolution, chip and identity of sensor on stream.
- `reading()`: sensor reading in the basic unit.
- `value()`: sensor reading in the current unit.
- `valueStr()`: sensor reading as a string.
- `read()`: blocking read: request(), retrieve(), and get(), and return sensor value.

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

Available ESensors:

- [`TemperatureDS18x20`](chips/ds18x20.md)
- [`LightBH1750`](chips/bh1750.md)


## ESensorValue

An [ESensorValue](../src/ESensorValue.h) is an [ESensor](#esensor)
that owns a pointer to an [ESensorDevice](#esensordevice) and exposes
a single type of sensor reading of this device. See the documentation
of the [ESensorDevice](#esensordevice)s listed above for available
[ESensor](#esensor) classes.


## DerivedESensor

A [DerivedESensor](../src/DerivedESensor.h) is an [ESensor](#esensor) that
does not get its readings from a device but computes it from readings
of other sensors.

Available derived sensors are:

- [`AbsoluteHumidity`](../src/AbsoluteHumidity.h): absolute humidity in g/m^3.
- [`DewPoint`](../src/DewPoint.h): dew point in degrees celsius.
- [`SeaLevelPressure`](../src/SeaLevelPressure.h): pressure at sea level in Pascal.


## ESensors

[ESensors](../src/ESensors.h) manages many [ESensor](#esensor)s.

General member functions:

- `addSensor()`: add an [ESensor](#esensor).
- `size()`: the number of managed [ESensor](#esensor)s.
- `sensors()`: the number of currently available [ESensor](#esensor)s.

Control reading of sensor data:

- `start()`: initialize reading from [ESensor](#esensor)s.
- `request()`: request a reading from all [ESensor](#esensor)s.
- `delayTime()`: the maximum delay time of all the [ESensor](#esensor)s.
- `get()`: get sensor readings from all [ESensor](#esensor)s.
- `read()`: blocking read: `request()`, `delay()`, and `get()`.
- `timeStamp()`: time stamp of last sensor reading.
- `interval()`, `setInterval()`: time interval for repetitive reads used in `update()`.
- `update()`: non-blocking control of request() and get() for all [ESensor](#esensor)s.

Output on stream:

- `reportDevices()`: report properties (chip, bus, address/pin, identifier)
  of managed [ESensor](#esensor)s chips.
- `report()`: report properties (name, unit, resolution, chip, etc.) of managed [ESensor](#esensor)s.
- `setPrintTime()`: control whether and how time stamps are reported.
- `print()`: print sensor names, readings, and units.
- `printHeader()`: print header with sensor names and units.
- `printValues()`: print sensor readings.

Log sensor data into CSV file:

- `openCSV()`: open CSV file on SD card and write header.
- `pendingCSV()`: check whether data buffer is ready for being written to SD card.
- `writeCSV()`: write data buffer to CSV file.
- `closeCSV()`: close CSV file.
