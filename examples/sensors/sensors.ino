#include <TimeLib.h>
#include <Sensors.h>
#include <TemperatureDS18x20.h>
#include <SenseBME280.h>
#include <LightTSL2591.h>
#include <DewPoint.h>
#include <AbsoluteHumidity.h>


Sensors sensors;

TemperatureDS18x20 temp(&sensors, 10);  // DATA on pin 10
SenseBME280 bme;
TemperatureBME280 tempbme(&bme, &sensors);
HumidityBME280 hum(&bme, &sensors);
AbsoluteHumidity abshum(&tempbme, &hum, &sensors);
DewPoint dp(&tempbme, &hum, &sensors);
PressureBME280 pres(&bme, &sensors);
//SeaLevelPressureBME280 slpres(&bme, &sensors, 460.0);
LightTSL2591 tsl(&Wire);
//Channel0TSL2591 chn0(&tsl, &sensors);
//Channel1TSL2591 chn1(&tsl, &sensors);
//GainTSL2591 gain(&tsl, &sensors);
//IRRatioTSL2591 irratio(&tsl, &sensors);
//IrradianceFullTSL2591 irrfull(&tsl, &sensors);
//IrradianceIRTSL2591 irrIR(&tsl, &sensors);
IlluminanceTSL2591 illum(&tsl, &sensors);

time_t getTeensyTime() {
  return Teensy3Clock.get();
}

void setup(void) {
  Serial.begin(9600);
  while (!Serial && millis() < 2000) {};
  setSyncProvider(getTeensyTime);  // enable real time clock
  // sensors.setPrintTime(Sensors::ISO_TIME);
  sensors.setPrintTime(Sensors::NO_TIME);  // no time column for the serial plotter
  sensors.setInterval(0.2);
  Wire.begin();
  bme.beginI2C(Wire, 0x77);
  pres.setHecto();
  //slpres.setMilliBar();
  tsl.begin();
  tsl.setGain(LightTSL2591::AUTO_GAIN);
  //irratio.setPercent();
  Serial.println();
  //sensors.report();  // nice, but confuses the serial plotter
  //Serial.println();
  delay(500);
  // discard first read:
  sensors.start();
  sensors.read();
  // go:
  sensors.start();
  sensors.printHeader();
}

void loop(void) {
  if (sensors.update())
    sensors.printValues();
    tsl.setTemperature(bme.temperature());
}
