# Senors V1

Temperature and light sensor with status LEDs.

Based on

- [BH1750](../../docs/chips/bh1750.md)  ambient light sensor
- [Sensirion STS40](../../docs/chips/sts4x.md) temperature sensor
- [PCA9536](pca9536.pdf) 4-bit I2C-bus I/O port

by [jlm Innovation](https://www.jlm-innovation.de/) and [Jan
Benda](https://github.com/janscience).

![Sensors-V1](Sensors-V1.jpg)


## Circuit

- [EAGLE schematics file](Sensors-V1.sch)
- [EAGLE circuit board](Sensors-V1.brd)


## LEDs

- [LITE-ON 639nm](LTST_C190KRKT-1141828.pdf): SMD, orange
- [LITE-ON 468nm](LTST_C193TBKT_5A-1175300.pdf): SMD, blue
- [OSRAM 850nm](sfh4555.pdf): through-hole, infrared


## Code

- [ESensors/LightBH1750.h](../../src/LightBH1750.py)
- [ESensors/TemperatureSTS4x.h](../../src/TemperatureSTS4x.h)
- [TeeRec/DigitalIOPCA9536.h](https://github.com/janscience/TeeRec/blob/main/src/DigitalIOPCA9536.h)

```cpp
#include <Wire.h>
#include <SDCard.h>
#include <Blink.h>
#include <ESensors.h>
#include <TemperatureSTS4x.h>
#include <LightBH1750.h>
#include <DigitalIOPCA9536.h>

#define STS4x_ADDR  STS4x_ADDR2   // I2C address of STS4x temperature sensor

ESensors sensors;
TemperatureSTS4x tempsts(&sensors);
LightBH1750 light1(&sensors);
LightBH1750 light2(&sensors);

DigitalIOPCA9536 gpio;
Blink blink("status", LED_BUILTIN);
Blink errorblink("error");
Blink syncblink("sync");

SDCard sdcard;


void setup() {
  sdcard.begin();
  Wire2.begin();
  gpio.begin(Wire2);
  blink.setPin(gpio, 0);
  errorblink.setPin(gpio, 1);
  syncblink.setPin(gpio, 3);
  blink.switchOff();
  errorblink.switchOff();
  syncblink.switchOff();
  gpio.setMode(2, INPUT);
  light1.begin(Wire2, BH1750_TO_GROUND);
  light1.setQuality(BH1750_QUALITY_HIGH2);
  light1.setName("illuminance1");
  light1.setSymbol("I1");
  light2.begin(Wire2, BH1750_TO_VCC);
  light2.setQuality(BH1750_QUALITY_HIGH2);
  light2.setName("illuminance2");
  light2.setSymbol("I2");
  tempsts.begin(Wire2, STS4x_ADDR);
  tempsts.setPrecision(STS4x_HIGH);
  sensors.setPrintTime(ESensors::NO_TIME);
  sensors.start();
  sensors.setInterval(10.0);
  sensors.setPrintTime(ESensors::ISO_TIME);
  sensors.reportDevices();
  sensors.report();
  sensors.start();
  sensors.read();
  sensors.start();
  sensors.read();
  sensors.openCSV(sdcard, "sensors.csv");
}


void loop() {
  if (sensors.update(blink.isOn() || syncblink.isOn())) {
    sensors.writeCSV();
    sensors.print(true, true);
  }
}
```

## Applications

- [R4-sensors-logger](https://github.com/janscience/TeeGrid/tree/main/examples/R4-sensors-logger) 
