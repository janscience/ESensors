#include <TimeLib.h>
#include <Sensors.h>
#include <LightTSL2591.h>


Sensors sensors;
LightTSL2591 tsl(&Wire);
Channel0TSL2591 chn0(&tsl, &sensors);
Channel1TSL2591 chn1(&tsl, &sensors);

time_t getTeensyTime() {
  return rtc_get();
}

void setup(void) {
  Serial.begin(9600);
  while (!Serial && millis() < 2000) {};
  setSyncProvider(getTeensyTime);  // enable real time clock
  sensors.setInterval(0.2);
  Wire.begin();
  tsl.begin();
  tsl.setIntegrationTime(1);
  tsl.setGain(1);
  Serial.println();
  sensors.report();
  Serial.println();
  delay(500);
  sensors.start();
  sensors.printHeader();
}

void loop(void) {
  if (sensors.update())
    sensors.printValues();
}
