/* Simple sketch for measuring water conductivity.

The resistance between two electrodes is measured by analog input.
 */


#include <Arduino.h>


uint8_t upin = 15;       // pin for output of U
uint8_t vpin = 14;       // analog input pin for V
unsigned int bits = 12;  // resolution of analog input
float alpha = 1.0;       // calibration factor K/R_0


void setup() {
  Serial.begin(9600);
  while (!Serial && millis() < 2000) {};
  
  pinMode(upin, OUTPUT);
  pinMode(vpin, INPUT);   

  analogReadAveraging(4);
  analogReadRes(bits);
}


float getVdrop() {
  int n = 1;
  float raw = 0.0;
  for (int k=0; k<n; k++) {
    digitalWrite(upin, HIGH);
    analogRead(vpin);  // replace by delay?
    int r = analogRead(vpin);
    digitalWrite(upin, LOW);
    raw += r;
    delay(1000);
  }
  raw /= n;
  float uv1 = float(1 << bits)/raw - 1.0;
  return uv1;
}


void loop() {
  float uv1 = getVdrop();
  float kappa = alpha*uv1;
  Serial.printf("U/V-1 = %6.5g  conductivity = %6.5g uS/cm", uv1, kappa);
  delay(1000);
}
