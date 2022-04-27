#include <LightTSL2591.h>

LightTSL2591 tsl(&Wire);
Channel0TSL2591 chn0(&tsl);
Channel1TSL2591 chn1(&tsl);

const int ntimes = 6;
const int ngains = 4;
const char *times[ntimes] = {"100ms", "200ms", "300ms", "400ms", "500ms", "600ms"};
const char *gains[ngains] = {"LOW", "MED", "HIGH", "MAX"};

double mean_chn0 = 0.0;
double mean_chn1 = 0.0;


void measure(int n=100) {
  mean_chn0 = 0.0;
  mean_chn1 = 0.0;
  for (int k=0; k<n; k++) {
    tsl.read();
    mean_chn0 += chn0.value()/n;
    mean_chn1 += chn1.value()/n;
  }
  Serial.printf("%7.1f\t%7.1f", mean_chn0, mean_chn1);
}


void measure_gains() {
  for (int i=0; i<ntimes; i++) {
    Serial.println();
    double r0[ngains];
    double r1[ngains];
    for (int j=0; j<ngains; j++) {
      tsl.setIntegrationTime(i);
      tsl.setGain(j);
      Serial.printf("%-5s\t%-4s\t", times[i], gains[j]);
      measure();
      r0[j] = mean_chn0;
      r1[j] = mean_chn1;
      Serial.printf("\t%7.2f\t%7.2f\n", r0[j]/r0[0], r1[j]/r1[0]);
    }
  }
}


void measure_times() {
  for (int j=0; j<ngains; j++) {
    Serial.println();
    double r0[ntimes];
    double r1[ntimes];
    for (int i=0; i<ntimes; i++) {
      tsl.setIntegrationTime(i);
      tsl.setGain(j);
      Serial.printf("%-5s\t%-4s\t", times[i], gains[j]);
      measure();
      r0[i] = mean_chn0;
      r1[i] = mean_chn1;
      Serial.printf("\t%7.2f\t%7.2f\n", r0[i]/r0[0], r1[i]/r1[0]);
    }
  }
}


void setup(void) {
  Serial.begin(9600);
  while (!Serial && millis() < 2000) {};
  Wire.begin();
  tsl.begin();
  Serial.println("stand by ...");
  Serial.println();
  Serial.printf("%-5s\t%-4s\t%-7s\t%-7s\t%-7s\t%-7s\n", "time", "gain", "chn0", "chn1", "scale0", "scale1");
  measure_gains();
  measure_times();
  Serial.println();
  Serial.println("DONE!");
}

void loop(void) {
}
