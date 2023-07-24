# Aosong DHT11, DHT22

Senses

- [temperature](../parameters/temperature.md)
- [humidity](../parameters/humidity.md)

This chip is controlled via its own type of one wire bus.


## Resources

- [Aosong DHT22 Datasheet](http://www.adafruit.com/datasheets/DHT22.pdf)
- [K&R Smith calibration notes](http://www.kandrsmith.org/RJS/Misc/Hygrometers/calib_many.html)
- [Adafruit DHT11, DHT22 and AM2302 Sensors](https://learn.adafruit.com/dht)


## ESensors Software

The [SenseDHT.h](../../src/SenseDHT.h) header declares classes
supporting the DHT11 and DHT22 within the [ESensors](../classes.md) framework.
It is based on the [DHT-Sensors-Non-Blocking](https://github.com/toannv17/DHT-Sensors-Non-Blocking) library.

```cpp
#include<SenseDHT.h>
```

It provides the following classes:

### ESensor device

- `SenseDHT`

```cpp
SenseDHT dht(10);

void setup() {
}
```

### ESensors

- `TemperatureDHT`: temperature in degree celsius.
- `HumidityDHT`: relative humidity.

```cpp
TemperatureDHT temp(&dht);
HumidityDHT hum(&dht);
```


## Hardware

- [DHT22 temperature-humidity sensor + extras](https://www.adafruit.com/product/385)

  ![dht22](https://cdn-shop.adafruit.com/970x728/385-00.jpg)

- [AM2302 (wired DHT22) Temperature-Humidity Sensor](https://www.exp-tech.de/sensoren/temperatur/4648/am2302-wired-dht22-temperature-humidity-sensor?c=1080)

  ![am2302](https://www.exp-tech.de/media/image/27/d9/f9/am2302-wired-dht22-feuchte-temperatur-sensor_600x600_600x600.jpg)


## Connection

Connect the chip to [Teensy](https://www.pjrc.com/teensy/pinout.html)
as follows:

| DHTxx   | color  | Teensy      |
| ------- | ------ | ----------- |
| VCC     | red    | 3.3V        |
| Data out | yellow/white  | some pin |
| not connected  |   |          |
| GND     | black  | GND         |


## Library survey

For our purposes (acquisition of weather data at low rates and low
power, flexible bus interfaces), the following two libraries seem to
be most appropriate:

- [DHT-Sensors-Non-Blocking](https://github.com/toannv17/DHT-Sensors-Non-Blocking).
