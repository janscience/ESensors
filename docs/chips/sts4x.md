# Sensirion STS4x

Senses

- [temperature](../parameters/temperature.md)

These chips are controlled via I2C bus.


## Resources

- [Sensirion STS40](https://sensirion.com/de/produkte/katalog/STS40)
- [datasheet](datasheets/sts4x.pdf)


## ESensors Software

The [TemperatureSTS4x.h](../../src/TemperatureSTS4x.h) header declares classes
supporting the STS4x chips within the [ESensors](../classes.md) framework.

```cpp
#include<TemperatureSTS4x.h>
```

It provides the following classes:

### ESensor device

- `TemperatureSTS4x`: temperature in degree celsius.

```cpp
TemperatureSTS4x tmp;

void setup() {
  Wire.begin();
  tmp.begin(Wire, STS4x_ADDR1);
  tmp.setPrecision(STS4x_HIGH);
}
```


## Connection

Connect the chip to [Teensy](https://www.pjrc.com/teensy/pinout.html)
as follows:

| STS4x         |  Teensy   |
| ------------- |  -------- |
| VCC           |  3.3V     |
| GND           |  GND      |
| SDA           |  SDA      |
| SCL           |  SCL      |


## Library survey

- [Sensirion I2C STS4X Arduino Library](https://github.com/Sensirion/arduino-i2c-sts4x): blocks for 10ms.
