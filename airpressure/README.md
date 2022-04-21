# Air pressure


## Bosch Sensortec BME280

Senses
- temperature
- humidity
- air pressure

Resources:
- [Bosch Sensortec Website](https://www.bosch-sensortec.com/products/environmental-sensors/humidity-sensors-bme280/)
- [Datasheet](https://www.bosch-sensortec.com/media/boschsensortec/downloads/datasheets/bst-bme280-ds002.pdf)
- [Driver](https://github.com/BoschSensortec/BME280_driver)


### Hardware

- [BlueDot BME280+TSL2591 Advanced Weather Station](https://www.bluedot.space/products/bme280-tsl2591/)

  ![pinout](https://image.jimcdn.com/app/cms/image/transf/dimension=697x10000:format=png/path/s9044904ce8b43c5c/image/ic78b28bd0a4d9113/version/1525169534/i2c-wiring-for-bme280-tsl2591-board.png)

- [BlueDot BME280 Weather Station](https://www.bluedot.space/products/bme280/)

  ![pinout](https://image.jimcdn.com/app/cms/image/transf/dimension=697x10000:format=png/path/s9044904ce8b43c5c/image/id0c55c24650bbce2/version/1525168839/i2c-wiring-for-bluedot-bme280-board.png)

- [Adafruit BME280 Humidity + Barometric Pressure + Temperature Sensor Breakout](https://learn.adafruit.com/adafruit-bme280-humidity-barometric-pressure-temperature-sensor-breakout)

  ![pinout](https://cdn-learn.adafruit.com/assets/assets/000/026/680/medium800/sensors_pinout.jpg?1437768166)


### Libraries

A search via the library manager of the Arduino IDE results in (April 2022):

- [BMx280MI](https://bitbucket.org/christandlg/bmx280mi/src/master/): Non-blocking read request, takes pointer to Wire object.
- [Bolder flight systems BME280](https://github.com/bolderflight/bme280): Well documented library, based on driver provided by Bosch and Wire.h, takes pointer to Wire object.
- [SparkFun BME280 Arduino Library](https://github.com/sparkfun/SparkFun_BME280_Arduino_Library): Takes pointer to wire object. Various derived measures. Supports configuration.

as well as:

- [Adafruit BME280 Library](https://github.com/adafruit/Adafruit_BME280_Library): Based on adafruit bus libraries.
- [BlueDot BME280 Library](https://github.com/BlueDot-Arduino/BlueDot_BME280): Fixed Wire or SPI interface, conversion to altitude.
- [BME280 by Tyler Glenn](https://github.com/finitespace/BME280): Calculates derived measures like dew point, sea level pressure, etc., fixed Wire object.
- [Bme280 by Eduard Malokhvill](https://github.com/malokhvii-eduard/arduino-bme280): Different predefined configuration settings, non flexible bus interface.
- [BME280 library by Zanduino](https://github.com/Zanduino/BME280): Non flexible bus interface.
- [Forced-BME280](https://github.com/JVKran/Forced-BME280): Wire.h, some calibration and configuration code via defines.
- [Grove Barometer Sensor BME280](https://github.com/Seeed-Studio/Grove_BME280): Wire.h, very basic interface, sensor not configurable.
- [Gyver BME280](https://github.com/GyverLibs/GyverBME280): Non-english docs
- [JWA BME280_Bosch_Wrapper](https://github.com/janw-cz/JWA_BME280): Based on driver provided by Bosch and Wire.h.
- [Melopero BME280 Arduino Library](https://github.com/melopero/Melopero_BME280_Arduino_Library): Based on driver provided by Bosch and Wire.h.
- [Simple BME280](https://gitlab.com/riva-lab/SimpleBME280): Non-english docs.
