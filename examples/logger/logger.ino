// requires TeeRec library
#include <SdFat.h>
#include <Sensors.h>
#include <TemperatureDS18x20.h>
#include <SenseBME280.h>
#include <LightTSL2591.h>
#include <RTClock.h>
#include <Blink.h>


// Default settings: -----------------------------------------------------------------------

uint8_t tempPin = 10;        // pin for DATA line of thermometer
float sensorsInterval = 2.0; // interval between sensors readings in seconds

// ------------------------------------------------------------------------------------------

RTClock rtclock;
Sensors sensors;
TemperatureDS18x20 temp(&sensors);
SenseBME280 bme;
TemperatureBME280 tempbme(&bme, &sensors);
HumidityBME280 hum(&bme, &sensors);
DewPointBME280 dp(&bme, &sensors);
PressureBME280 pres(&bme, &sensors);
LightTSL2591 tsl(&Wire, &sensors);
Channel0TSL2591 chn0(&tsl, &sensors);
Channel1TSL2591 chn1(&tsl, &sensors);
GainTSL2591 gain(&tsl, &sensors);
IRRatioTSL2591 irratio(&tsl, &sensors);
//IrradianceFullTSL2591 irrfull(&tsl, &sensors);
//IrradianceIRTSL2591 irrIR(&tsl, &sensors);
SdFat sdcard;
Blink blink(LED_BUILTIN);
bool symbols = false;


// ------------------------------------------------------------------------------------------

void setup() {
  blink.switchOn();
  Serial.begin(9600);
  while (!Serial && millis() < 2000) {};
  rtclock.check();
  rtclock.report();
  temp.begin(tempPin);
  Wire.begin();
  bme.beginI2C(Wire, 0x77);
  pres.setHectoPascal();
  tsl.begin();
  tsl.setGain(LightTSL2591::AUTO_GAIN);
  irratio.setPercent();
  sensors.setInterval(sensorsInterval);
  sdcard.begin(BUILTIN_SDCARD);
  sensors.setPrintTime(Sensors::ISO_TIME);
  sensors.report();
  bool success = sensors.openCSV(sdcard, "sensors", symbols);
  blink.switchOff();
  if (success) {
    sensors.start();
    blink.setSingle();
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
    sensors.print(symbols);
    Serial.println();
  }
  if (sensors.pending())
    sensors.writeCSV();
  blink.update();
}
