# User guide

The Sensors library is a high level interface to various sensor chips
that (i) provides a common interface to the sensors, (ii) manages
multiple sensors, and (iii) provides a non-blocking interface to read
out sensor values.


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

## Chips with multiple sensors

Some chips provide multiple types of sensor readings, for example
temperature and humidity. They then need to be passed to specific
[Sensor class](../src/Sensor.h)es, each providing access to
one type of sensor reading. These chips are interfaced via a
[SensorDevice class](../src/SensorDevice.h) and the accessing classes
are derived from the [SensorValue template class](../src/SensorValue.h)
and own a pointer to the sensor device.

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
manually added via the addSensor() method.

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
  sensors.start();
}

void loop() {
  sensors.read();           // read them all in parallel!
  float T = temp.value(); 
  float RH = hum.value(); 
  float p = pres.value(); 
  // ... do something with T, RH, and p ...
  // or,  for example,
  sensors.print();          // print sensor readings with unit to Serial.
}
```


## Non-blocking reads

Many sensor devices need quite some time to generate a single reading:

1. The reading has to be initiated (via the `request()` member
   function of either a single [Sensor](../src/Sensor.h) or many
   [Sensors](../src/Sensors.h).

2. Then we need to wait for the conversion
   to finish. How long is known by the `delayTime()` member function.

3. After waiting long enough, the sensor reading can be retrieved via the
   `get()` member function.

4. And finally the sensor readings can be obtained
   from the `value()` member function.

These steps are combined in the `read()` member function, that blocks
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
    sensors.print();          // print sensor readings with unit to Serial.
  }
  // do something else!
}
```

By default, the sensor readings are done as quickly as possible,
i.e. `update()` return `true` after the maximum delay required by the
managed sensors.

The sensor readings can be scheduled at a given interval, via
`setInterval()` that takes a floating point number specifying a time
in seconds:

```cpp
void setup() {
  // ...
  sensors.setInterval(5.7); // read sensors every 5.7s. Call this before start().
  sensors.report();         // write infos to all avaliable sensors to Serial.
  sensors.start();
}
```
