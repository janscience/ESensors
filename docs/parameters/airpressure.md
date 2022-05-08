# Air pressure

Measured in Pascal (Pa).


## Units

For various other units see this
[converter](https://www.beamex.com/resources/pressure-unit-converter/).

The [ESensor class](../classes.md#esensor) provides conversions to
some of the many pressure units. For example, for an output in hPa:

```cpp
#include <SenseBME280.h>

SenseBME280 bme;
PressureBME280 pressure(&bme);

void setup() {
  while (!Serial && millis() < 2000) {};
  Wire.begin();
  bme.beginI2C(Wire, 0x77);
  pressure.setHecto();
  float p = pressure.read();
  Serial.printf("p=%.0f%s\n", p, pressure.unit());
}
```

Other available units are

```cpp
  pressure.setBar();
  pressure.setMilliBar();
  pressure.setAt();
  pressure.setAtm();
  pressure.setMMHg();
  pressure.setPSI();
  pressure.setTorr();
```


## Hardware

- [Bosch Sensortec BME280](../chips/bme280.md)

- [BMP388](https://www.bluedot.space/products/bmp388/)



## Sea level pressure

If the altitude of the pressure measurement is known, then
the pressure at sea level can be estimated.

See [keisan online
calculator](https://keisan.casio.com/exec/system/1224575267) and
[derivation of
equation](https://keisan.casio.com/keisan/image/Convertpressure.pdf).

Implemented in [class SeaLevelPressure](../../src/SeaLevelPressure.h).

