#include <TimeLib.h>
#include <SdFat.h>
#include <ESensors.h>
#include <TemperatureDS18x20.h>
#include <SenseBME280.h>
#include <LightTSL2591.h>
#include <LightBH1750.h>
#include <DewPoint.h>

// uncomment the sensors you want to use:
//#define TEMPDS18x20
//#define SENSEBME280
//#define LIGHTTSL2591
#define LIGHTBH1750


// settings: -----------------------------------------------------------------

uint8_t tempPin = 10;        // pin for DATA line of DS18x20 themperature sensor
float sensorsInterval = 2.0; // interval between sensors readings in seconds

// ----------------------------------------------------------------------------


ESensors sensors;

#ifdef TEMPDS18x20
TemperatureDS18x20 temp(&sensors);
#endif
#ifdef SENSEBME280
SenseBME280 bme;
TemperatureBME280 tempbme(&bme, &sensors);
HumidityBME280 hum(&bme, &sensors);
DewPoint dp(&hum, &tempbme, &sensors);
PressureBME280 pres(&bme, &sensors);
#endif
#ifdef LIGHTTSL2591
LightTSL2591 tsl;
//Channel0TSL2591 chn0(&tsl, &sensors);
//Channel1TSL2591 chn1(&tsl, &sensors);
//GainTSL2591 gain(&tsl, &sensors);
IRRatioTSL2591 irratio(&tsl, &sensors);
//IrradianceFullTSL2591 irrfull(&tsl, &sensors);
//IrradianceIRTSL2591 irrIR(&tsl, &sensors);
IlluminanceTSL2591 illum(&tsl, &sensors);
#endif
#ifdef LIGHTBH1750
LightBH1750 bh(&sensors);
RawBH1750 bhraw(&bh, &sensors);
QualityBH1750 bhqual(&bh, &sensors);
TimeBH1750 bhtime(&bh, &sensors);
#endif

SdFat sdcard;
int led_pin = LED_BUILTIN;
bool symbols = false;

time_t getTeensyTime() {
  return Teensy3Clock.get();
}

void setup() {
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, HIGH);
  Serial.begin(9600);
  while (!Serial && millis() < 2000) {};
  setSyncProvider(getTeensyTime);
  sdcard.begin(BUILTIN_SDCARD);
#ifdef TEMPDS18x20
  temp.begin(tempPin);
#endif
  Wire.begin();
#ifdef SENSEBME280
  bme.beginI2C(Wire, 0x77);
  hum.setPercent();
  pres.setHecto();
#endif
#ifdef LIGHTTSL2591
  tsl.begin(Wire);
  tsl.setGain(LightTSL2591::AUTO_GAIN);
  irratio.setPercent();
#endif
#ifdef LIGHTBH1750
  bh.begin();
  bh.setAutoRanging();
#endif
  sensors.setInterval(sensorsInterval);
  sensors.setPrintTime(ESensors::ISO_TIME);
  sensors.report();
  bool success = sensors.openCSV(sdcard, "sensors", symbols);
  digitalWrite(led_pin, LOW);
  if (success) {
    // init sensors:
    sensors.start();
    sensors.read();
#if defined(SENSEBME280) && defined(LIGHTTSL2591)
    tsl.setTemperature(bme.temperature());
#endif
    sensors.read();
    sensors.start();
    Serial.println();
    Serial.println("Start logging ...");
    Serial.println();
  }
  else {
    Serial.println();
    Serial.println("ERROR: SD card no available -> halt!");
    while (1) {};
  }
}


void loop() {
  if (sensors.update()) {
    digitalWrite(led_pin, HIGH);
#if defined(SENSEBME280) && defined(LIGHTTSL2591)
    tsl.setTemperature(bme.temperature());
#endif
    sensors.print(symbols);
    Serial.println();
    delay(50);
    digitalWrite(led_pin, LOW);
  }
  if (sensors.pendingCSV())
    sensors.writeCSV();
}
