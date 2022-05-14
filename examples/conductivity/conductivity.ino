/* Simple sketch for measuring water conductivity.

The resistance between two electrodes is measured by analog input.
 */


#include <Arduino.h>
#include <ADC.h>

int adc = 0;
uint8_t upin = 17;       // pin for output of U
uint8_t vpin = 16;       // analog input pin for V
unsigned int bits = 12;  // resolution of analog input
float alpha = 1.0;       // calibration factor K/R_0


ADC ADConv;


void setup() {
  Serial.begin(9600);
  while (!Serial && millis() < 2000) {};
  
  pinMode(upin, OUTPUT);
  pinMode(vpin, INPUT);   
  
  ADConv.adc[adc]->setResolution(bits);
  ADConv.adc[adc]->setAveraging(32);
  //ADConv.adc[adc]->setConversionSpeed(ConversionSpeed);  
  //ADConv.adc[adc]->setSamplingSpeed(SamplingSpeed);
 }


float getVdrop() {
  int n = 1;
  float raw = 0.0;
  for (int k=0; k<n; k++) {
    digitalWrite(upin, HIGH);
    ADConv.adc[adc]->startSingleRead(vpin);
    delay(10);
    int r = ADConv.adc[adc]->readSingle();
    digitalWrite(upin, LOW);
    raw += r;
    delay(1000);
  }
  raw /= n;
  float vu = raw/float(1 << bits);
  return vu;
}


void loop() {
  float vu = getVdrop();
  float kappa = alpha*(1.0/vu - 1.0);
  Serial.printf("V/U = %6.5g  conductivity = %6.5g uS/cm\n", vu, kappa);
  delay(1000);
}
