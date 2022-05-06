# User guide

The [Sensors](https://github.com/janscience/Sensors) library is a high
level interface to various sensor chips. It

1. provides a common interface to various sensors,

2. reports sensor values with flexible units,

3. manages multiple sensors, and

4. provides a non-blocking interface to read out sensor values in parallel.


## Using a single sensor

Any class derived from the [Sensor class](../src/Sensor.h) can read a
specific environmental parameter from a sensor chip/device.

For example, the DS18x20 only reads temperature. Include the header
file, [TemperatureDS18x20.h](../src/TemperatureDS18x20.h), initialize the temperature sensor, and retrieve the sensor readings:

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

Each sensor has a name, a mathematical symbol, and a unit specifying
what exactly is returned by the sensor.  It also provides a format
string that can be used to format the returned value.

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
this unit. The sensor class provides a number of functions that you
can use to change the SI unit prefix (e.g. `setMilli()`, `setKilo()`,
etc., to change a fraction to percent (`setPercent()`), or to change
degree Celsius to Kelvin (`setKelvin()`), for example. These functions
also modify the format string in a smart way. Or adapt the format
string directly via `setFormat()`.

Change names and units according to your needs in the setup function.

```cpp
void setup() {
  temp.setName("air temperature");
  temp.setSymbol("T_air");
  temp.setKelvin();
}
```

The sensor reading can always be retrieved in its original unit
(`basicUnit()`) via the `reading()` function instead of `value()`.


## Chips with multiple sensors

Some chips provide multiple types of sensor readings, for example
temperature and humidity. They then need to be passed to specific
[Sensor class](../src/Sensor.h)es, each providing access to
one type of sensor reading. These chips are interfaced via a
[SensorDevice class](../src/SensorDevice.h) and the accessing classes
are derived from the [SensorValue template class](../src/SensorValue.h)
that own a pointer to the sensor device.

An example is the [Bosch BME280](chips/bme280.md) chip. It measures
temperature, humidity, and pressure. You can use it like this:

```cpp
#include <SenseBME280.h>

SenseBME280 bme;
TemperatureBME280 temp(&bme);
HumidityBME280 hum(&bme);
PressureBME280 pres(&bme);

void setup() {
  Wire.begin();             // init the I2C bus.
  bme.beginI2C(Wire, 0x77); // init the sensor chip.
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


## Managing multiple sensors

The [Sensors class](../src/Sensors.h) manages a single or multiple
[Sensor](../src/Sensor.h)s. It provides infrastructure to read them in
parallel, to write readings to the Serial port or into csv files.

For this, an instance of the [Sensors class](../src/Sensors.h) needs
to be passed to the individual sensors. Alternatively, they can be
manually added via the `addSensor()` method.

Then our example looks like this:

```cpp
#include <Sensors.h>
#include <SenseBME280.h>

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
   function of either a single [Sensor](../src/Sensor.h) or many
   [Sensors](../src/Sensors.h)).

2. Then we need to wait for the conversion
   to finish. How long is known by the `delayTime()` member function.

3. After waiting long enough, the sensor reading can be retrieved via the
   `get()` member function.

4. And finally the sensor readings can be obtained
   from the `value()` member function.

Steps 1 - 3 are combined in the `read()` member function, that blocks
for the time given by `delayTime()`.

Alternatively, one can repetitively call the `update()` member
function of the [Sensors class](../src/Sensors.h) in the
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

The [Sensors class](../src/Sensors.h) also provides a simple interface
to write the sensor readings into a CSV file on an SD card. This is a
text file with "comma separated values" arranged in a table. A header
specifies the names and units of the sensors, and then each line
contains a time stamp and the sensor readings. CSV files can be
openend in spreadsheet programs or easily processed in a script.

A minimum example looks like this (see also [logger
example](../examples/logger/)):

```cpp
#include <TimeLib.h>      // needed for time stamps
#include <SdFat.h>        // accessing the SD card
#include <Sensors.h>
#include <SenseBME280.h>

Sensors sensors;

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
  pres.setHecto();   // hPa
  sensors.setInterval(10.0);
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
