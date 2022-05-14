# User guide

The [ESensors library](classes.md) is a high
level interface to various sensor chips. It

1. provides a common interface to various sensors,

2. reports sensor values with flexible names and units,

3. manages multiple sensors, and

4. provides a non-blocking interface to read out sensor values in parallel.


## Content

- [Using a single sensor](#using-a-single-sensor)
- [Sensor names and units](#sensor-names-and-units)
- [Chips with multiple sensors](#chips-with-multiple-sensors)
- [Derived sensor readings](#derived-sensor-readings)
- [Managing multiple sensors](#managing-multiple-sensors)
- [Non-blocking reads](#non-blocking-reads)
- [Writing CSV files](#writing-csv-files)
- [Reporting on Serial](#reporting-on-serial)
- [Time stamps](#time-stamps)


## Using a single sensor

Any class derived from the [ESensor class](classes.md#esensor) can read
a specific environmental parameter from a sensor chip/device.

For example, the DS18x20 only reads temperature. Include the header
file, [TemperatureDS18x20.h](../src/TemperatureDS18x20.h), initialize
the temperature sensor, and retrieve the sensor readings:

```cpp
#include <TemperatureDS18x20.h>

TemperatureDS18x20 temp(10);  // DATA on pin 10

void setup() {
  // no further initialization necessary for DS18x20.
}

void loop() {
  float T = temp.read();   // blocking read!
  // ... do something with T ...
}

```

## Sensor names and units

Each [ESensor](classes.md#esensor) has a name, a mathematical symbol,
and a unit specifying what exactly is returned by the sensor.  It also
provides a format string that can be used to format the returned
value.

```cpp
void loop() {
  float T = temp.read();
  char sv[10];
  sprintf(sv, temp.format(), T);   // alternatively use temp.valueStr()
  Serial.printf("%s %s=%s%s\n", temp.name(), temp.symbol(), sv, temp.unit());
}
```

This produces

```txt
temperature T=21.62ºC
temperature T=21.62ºC
temperature T=21.63ºC
```

Change the name and the symbol to indicate more precisely what has
been measured, using the `setName()` and `setSymbol()` functions.

You can also change the unit via `setUnit()`, that provides a new unit
and a factor and offset to be used to compute the sensor value for
this unit. The [ESensor](classes.md#esensor) class provides a number
of functions that you can use to change the SI unit prefix
(e.g. `setMilli()`, `setKilo()`, etc., to change a fraction to percent
(`setPercent()`), or to change degree Celsius to Kelvin
(`setKelvin()`), for example. These functions also modify the format
string in a smart way. Or adapt the format string directly via
`setFormat()`.

Change names and units according to your needs in the setup function.

```cpp
void setup() {
  temp.setName("air temperature");
  temp.setSymbol("T_air");
  temp.setKelvin();
}
```

This produces

```txt
air temperature T_air=294.77K
air temperature T_air=294.77K
air temperature T_air=294.78K
```

The sensor reading can always be retrieved in its original unit
(`basicUnit()`) via the `reading()` function instead of `value()`.


## Chips with multiple sensors

Some chips provide multiple types of sensor readings, for example
temperature and humidity. They then need to be passed to specific
[ESensor class](classes.md#esensor)es, each providing access to one type
of sensor reading. These chips are interfaced via a [ESensorDevice
class](classes.md#esensordevice), that does not expose a value and a
unit. This is what the accessing classes, derived from the
[ESensorValue template class](classes.md#esensorvalue), do.  They own a
pointer to the sensor device and retrieve one specific type of sensor
reading.

An example is the [Bosch BME280](chips/bme280.md) chip. It measures
temperature, humidity, and pressure. You can use it like this:

```cpp
#include <SenseBME280.h>

SenseBME280 bme;               // the ESensorDevice.
TemperatureBME280 temp(&bme);  // a ESensorValue.
HumidityBME280 hum(&bme);      // another ESensorValue.
PressureBME280 pres(&bme);     // a third ESensorValue.

void setup() {
  Wire.begin();                // init the I2C bus.
  bme.beginI2C(Wire, 0x77);    // init the sensor chip.
  temp.setName("air temperature", "T_air");
  hum.setPercent();
  pres.setHecto();
}

void loop() {
   // blocking read of temperature!
   // This actually calls read() on the bme device,
   // that reads all three parameters.
  float T = temp.read();
  // So we can simply read out the values of the other two parameters:
  float RH = hum.value(); 
  float p = pres.value(); 
  // ... do something with T, RH, and p ...
}
```

## Derived sensor readings

Some environmental parameters can be computed from basic sensor
readings. For example the dew point can be computed from humidity and
temperature. These computed parameters are also provided as
[ESensor](classes.md#esensor)s via the [DerivedESensor
class](classes.md#derivedesensor). [ESensor](classes.md#esnsor)s
providing the required parameters are passed to their
constructors. This way, derived measures can be used as any other
[ESensor](classes.md#esensor) with a porper name and unit.

For example:

```cpp
#include <SenseBME280.h>
#include <DewPoint.h>

SenseBME280 bme;
TemperatureBME280 temp(&bme);
HumidityBME280 hum(&bme);
DewPoint dp(&hum, &temp);    // provide ESensors to dew point computation.

// ...

void loop() {
  float dp = dp.read();   // just read dew point
  // ...
}
```


## Managing multiple sensors

The [ESensors class](classes.md#esensors) manages a single or multiple
[ESensor](classes.md#esensor)s. It provides infrastructure to read them in
parallel, to write readings to the Serial port or into csv files.

For this, an instance of the [ESensors class](classes.md#esensors) needs
to be passed to the individual sensors. Alternatively, they can be
manually added via the `addSensor()` method.

Then our example looks like this:

```cpp
#include <ESensors.h>
#include <SenseBME280.h>

ESensors sensors;

SenseBME280 bme;
TemperatureBME280 temp(&bme, &sensors);  // add to sensors!
HumidityBME280 hum(&bme, &sensors);
PressureBME280 pres(&bme, &sensors);

void setup() {
  Wire.begin();             // init the I2C bus.
  bme.beginI2C(Wire, 0x77); // init the sensor chip.
  sensors.report();         // write infos to all avaliable sensors to Serial.
  sensors.start();          // get ready
}

void loop() {
  sensors.read();           // read them all in parallel!
  float T = temp.value(); 
  float RH = hum.value(); 
  float p = pres.value(); 
  // ... do something with T, RH, and p ...
  // or,  for example,
  sensors.print();          // print sensor readings with name and unit to Serial.
}
```


## Non-blocking reads

Many sensor devices need quite some time to generate a single reading:

1. The reading has to be initiated (via the `request()` member
   function of either a single [ESensor](classes.md#esensor) or many
   [ESensors](classes.md#esensors)).

2. Then we need to wait for the conversion
   to finish. How long is known by the `delayTime()` member function.

3. After waiting long enough, the sensor reading can be retrieved via the
   `get()` member function.

4. And finally the sensor readings can be obtained
   from the `value()` member function.

Steps 1 - 3 are combined in the `read()` member function, that blocks
for the time given by `delayTime()`.

Alternatively, one can repetitively call the `update()` member
function of the [ESensors class](classes.md#esensorss) in the
`loop()`. This function calls `request()` and `get()` at appropriate
times without blocking. Whenever new sensor values are available,
`update()` returns `true` and the values can be read out as usual via
`value()`. This way, other things can be controlled, while the sensors
work on getting their data:

```cpp
void loop() {
  if (sensors.update()) {     // does not block!
    // ... do something with sensor readings, for example:
    sensors.print();          // print sensor readings with name and unit to Serial.
  }
  // do something else!
}
```

By default, the sensor readings are done as quickly as possible,
i.e. `update()` returns `true` after the maximum delay required by the
managed sensors.

Alternatively, the sensor readings can be scheduled at a given
interval, via `setInterval()` that takes a floating point number
specifying a time in seconds:

```cpp
void setup() {
  // ...
  sensors.setInterval(10.0); // read sensors every 10.0s. Call this before start().
  sensors.report();          // write infos to all avaliable sensors to Serial.
  sensors.start();
}
```

## Writing CSV files

The [ESensors class](classes.md#esensors) also provides a simple
interface to write the sensor readings into a CSV file on an SD
card. This is a text file with "comma separated values" arranged in a
table. A header specifies the names and units of the sensors, and then
each line contains a time stamp and the sensor readings. CSV files can
be openend in spreadsheet programs or easily processed in a script.

A minimum example looks like this (see also [logger
example](../examples/logger/)):

```cpp
#include <TimeLib.h>      // needed for time stamps
#include <SdFat.h>        // accessing the SD card
#include <ESensors.h>
#include <SenseBME280.h>

ESensors sensors;

SenseBME280 bme;
TemperatureBME280 temp(&bme, &sensors);
HumidityBME280 hum(&bme, &sensors);

SdFat sdcard;             // Interface to the SD card

time_t getTeensyTime() {
  return Teensy3Clock.get();
}

void setup() {
  setSyncProvider(getTeensyTime);  // get time from Teensy internal real time clock
  Wire.begin();
  bme.beginI2C(Wire, 0x77);
  hum.setPercent();
  pres.setHecto();   // hPa
  sensors.setInterval(2.0);
  sdcard.begin(BUILTIN_SDCARD);              // initialize SD card
  sensors.setPrintTime(Sensors::ISO_TIME);   // Report time stamps in ISO format
  // Open "sensors.csv" on SD card and write header:
  if (! sensors.openCSV(sdcard, "sensors") )
    while (1) {};                            // SD card failed, do nothing.
  sensors.start();                           // get ready.
}


void loop() {
  sensors.update();          // Read the sensors every 10 seconds
  if (sensors.pending())     // If CSV file buffer is full ...
    sensors.writeCSV();      // ... write it.
}
```

You need to initialize the SD card, and then open a new CSV file on
the SD card (`sensors.openCSV()`). In the loop sensors are
periodically read as managed by `sensors.update()`. This function
writes the sensor readings into an internal buffer. If enough data
accumulated (to write at least one 512 byte block), as checked by
`sensors.pending()`, the buffer is written to the CSV file via
`sensors.writeCSV()`. If you need to close this file, simply call
`sensors.closeCSV()`.

`setPrintTime()` specifies whether and how to report time stamps.

The sketch produces a file `sensors.csv` on the SD card that looks
like this:

```txt
time/s,temperature/ºC,humidity/%,pressure/hPa
2022-05-12T23:13:46,24.53,58.1,967.09
2022-05-12T23:13:48,24.54,58.0,967.19
2022-05-12T23:13:50,24.71,72.6,967.12
2022-05-12T23:13:52,24.63,76.0,967.12
2022-05-12T23:13:54,24.64,70.8,967.11
2022-05-12T23:13:56,24.66,69.5,967.11
2022-05-12T23:13:58,24.68,71.1,967.14
2022-05-12T23:14:00,24.70,72.4,967.13
2022-05-12T23:14:02,24.71,74.8,967.14
```


## Reporting on Serial

The [ESensors class](classes.md#esensors) also provides some convenience
functions to report sensor properties and values on the Serial
port. Use the Serial monitr or plotter of the Arduino IDE to see them.


### report()

`report()` prints out some properties of the sensors, their names and
units:

```cpp
#include <ESensors.h>

ESensors sensors;
// ...

void setup() {
  Serial.begin(9600);
  while (!Serial && millis() < 2000) {};  // establish Serial connection
  // ...
  sensors.report();          // write infos to all avaliable sensors to Serial.
}
```

Output:

```txt
5 of 6 environmental sensors available, read every 2s:
  temperature T (ºC):	 on BME280 device at a resolution of 0.01ºC.
  humidity RH (%):	 on BME280 device at a resolution of 3.0%.
  dew point Tdp (ºC):	 on BME280 & BME280 device at a resolution of 0.3ºC.
  pressure P (hPa):	 on BME280 device at a resolution of 0.03hPa.
  illuminance E (lx):	 on TSL2591 device (ID: 50) at a resolution of 1lx.
```

### print()

`print()` prints out the current sensor readings with name and unit:

```cpp
void loop() {
  sensors.read();
  sensors.print();
}
```

Output:

```txt
temperature = 20.05ºC
humidity = 51.0%
pressure = 970.12hPa
illuminance = 4.85lx
```

Passing `true` to `print()` prints the symbols instead of the names:

```cpp
void loop() {
  sensors.read();
  sensors.print(true);
}
```

Output:

```txt
T = 20.17ºC
RH = 50.4%
P = 970.11hPa
E = 4.83lx
```


### printHeader() and printValues()

`printHeader()` and `printValues()` can be used to print sensor
readings in tabular from with tab separated columns. This is great for
looking at the data via the Serial plotter of the Arduino IDE.

```cpp
void setup() {
  // ...
  sensors.printHeader();
}

void loop() {
  sensors.read();
  sensors.printValues();
}
```

Output:

```txt
temperature/ºC	humidity/%	pressure/hPa	illuminance/lx
20.94	68.1	970.05	    6.15
20.91	68.0	970.12	    6.13
20.90	67.8	970.08	    6.12
```

Passing `true` to `printHeader()` prints header with symbols instead of names:

Output:

```txt
T/ºC	RH/%	P/hPa	E/lx
20.82	60.0	970.07	    6.14
20.79	59.9	970.09	    6.13
20.79	59.8	970.03	    0.94
20.84	59.3	970.05	    2.84
20.85	59.3	970.05	    1.09
```

## Time stamps

`setPrintTime()` controls how time stamps are reported both for
writing CSV files and for `printHeader()` and `printValues()`.

No time stamp is written by default or when calling
`sensors.printValues(ESensors::NO_TIME)` (as in the examples above).

For writing time stamps you first need to enable the real time clock. For example, when using the internal clock of the Teensy, you do:

```cpp
#include <TimeLib.h>

time_t getTeensyTime() {
  return Teensy3Clock.get();
}

void setup() {
  setSyncProvider(getTeensyTime);  // enable real time clock
  sensors.setPrintTime(ESensors::ISO_TIME);
  // ...
}
```

and you request time to be printed in ISO format. Then the output with
`printHeader()` and `printValues()` is:

```txt
t/s	T/ºC	RH/%	P/hPa	E/lx
2022-05-06T23:17:17	20.73	56.5	970.04	    6.13
2022-05-06T23:17:19	20.71	56.5	970.08	    6.14
2022-05-06T23:17:21	20.70	56.5	970.05	    6.05
2022-05-06T23:17:23	20.73	56.6	970.09	    1.25
2022-05-06T23:17:25	20.76	56.7	970.14	    0.94
```

For `sensors.setPrintTime(ESensors::SEC_TIME)` you get

```txt
t/s	T/ºC	RH/%	P/hPa	E/lx
1651879116	20.76	56.2	970.09	    6.16
1651879118	20.74	56.2	970.05	    6.13
1651879120	20.74	56.2	970.06	    6.18
1651879122	20.76	56.1	970.09	    0.72
1651879124	20.78	56.1	970.07	    0.71
```

the time since 1970 in seconds.