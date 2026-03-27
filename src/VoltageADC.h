/*
  VoltageADC - read voltage from internal ADC.
  Created by Jan Benda, March 27rd, 2025.
*/

#ifndef VoltageADC_h
#define VoltageADC_h


#include <Arduino.h>
#include <ESensor.h>


class VoltageADC : public ESensor {

 public:
  
  // Read voltages from pin.
  VoltageADC(ESensors *sensors=0, uint8_t pin=-1, float maxvolt=3.3);
  
  // Read voltages from pin.
  void begin(uint8_t pin, float maxvolt=3.3);

  // Return true if device is available.
  virtual bool available() const;

  // Recommended delay between a request() and read() in milliseconds.
  virtual unsigned long delayTime() const { return 0; };

  // The voltage in Volt.
  virtual float reading() const;
  
  
 private:

  // Retrieve a voltage reading.
  virtual void getData();

  int8_t Pin;
  uint8_t Bits;
  unsigned int MaxInt;
  float MaxVoltage;
  float Voltage;
};


#endif
