// requires Snooze library
#include <TimeLib.h>
#include <Snooze.h>
#include <SdFat.h>
#include <Sensors.h>
#include <TemperatureDS18x20.h>
#include <SenseBME280.h>
#include <LightTSL2591.h>


// Default settings: -----------------------------------------------------------------------

uint8_t tempPin = 10;        // pin for DATA line of thermometer
float sensorsInterval = 5.0; // interval between sensors readings in seconds

// ------------------------------------------------------------------------------------------


SnoozeAlarm alarm;
SnoozeSPI snoozesdcard;
SnoozeBlock snooze(alarm, snoozesdcard);
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
  temp.begin(tempPin);
  Wire.begin();
  bme.beginI2C(Wire, 0x77);
  pres.setHectoPascal();
  tsl.begin();
  tsl.setGain(LightTSL2591::AUTO_GAIN);
  irratio.setPercent();
  alarm.setRtcTimer(0, 0, sensorsInterval);
  snoozesdcard.setClockPin(BUILTIN_SDCARD);
  sdcard.begin(BUILTIN_SDCARD);
  sensors.setPrintTime(Sensors::ISO_TIME);
  sensors.report();
  bool success = sensors.openCSV(sdcard, "sensors", symbols);
  digitalWrite(led_pin, LOW);
  if (success) {
    // init sensors:
    sensors.start();
    sensors.read();
    tsl.setTemperature(bme.temperature());
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
  digitalWrite(led_pin, HIGH);
  setSyncProvider(getTeensyTime);
  sensors.read();
  if (sensors.pending())
    sensors.writeCSV();
  tsl.setTemperature(bme.temperature());
  digitalWrite(led_pin, LOW);
  // choose low power level:
  //Snooze.sleep(snooze);
  //Snooze.deepSleep(snooze);
  Snooze.hibernate(snooze);   // same as deepSleep() but also put USB regulator in low power mode (limited current supply!)
}
