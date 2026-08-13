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
  VoltageADC(ESensors *sensors=0, int pin=-1, float maxvolt=3.3);
  
  // Read voltages from pin.
  void begin(int pin, float maxvolt=3.3);

  // Return true if device is available.
  virtual bool available() const;

  // The maximum voltage that can be measured.
  float maxVoltage() const { return MaxVoltage; };

  // Set the maximum voltage that can be measured to maxvolt.
  void setMaxVoltage(float maxvolt);

  // Recommended delay between a request() and read() in milliseconds.
  virtual unsigned long delayTime() const { return 0; };

  // The voltage in Volt.
  virtual float reading() const;

  // Number of averages used when reading the voltage.
  uint8_t averaging() const { return Averaging; };

  // Set the number of averages used when reading the voltage.
  // Valid values are 1, 4, 8, 16, or 32.
  void setAveraging(uint8_t avrg);

  // Calibrate such that the last reading that was not zero was exactly voltage.
  void calibrate(float voltage);

  
 protected:

  // Retrieve a voltage reading.
  virtual void getData();

  uint8_t Bits;
  unsigned int MaxInt;
  uint8_t Averaging;
  float MaxVoltage;
  int RawInteger;
  float Voltage;

  char BitStr[4];
  char AvrgStr[4];
};


#endif
