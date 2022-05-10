/*
  TemperatureDS18x20 - read temperature from a DS18x20 1-wire device.
  Created by Jan Benda, November 27th, 2021.
  Based on https://github.com/PaulStoffregen/OneWire/blob/master/examples/DS18x20_Temperature/DS18x20_Temperature.ino

  The temperature sensor needs to be connected to the Teensy in the
  following way:
  - black: GND to Teensy GND
  - black: power to Teensy 3.3V
  - yellow: DATA to a Teensy digital output pin (e.g. pin 10).
    DATA also needs to be connected to Teensy 3.3V via a 4.7K resistor.

  See
  https://create.arduino.cc/projecthub/TheGadgetBoy/ds18b20-digital-temperature-sensor-and-arduino-9cc806
  step 4 for wiring.

  More resources on the OneWire protocol can be found here:
  https://create.arduino.cc/projecthub/TheGadgetBoy/ds18b20-digital-temperature-sensor-and-arduino-9cc806

  The [DS18B20 data
  sheet](https://datasheets.maximintegrated.com/en/ds/DS18B20.pdf).
*/

#ifndef TemperatureDS18x20_h
#define TemperatureDS18x20_h


#include <Arduino.h>
#include <OneWire.h>
#include <ESensor.h>


class TemperatureDS18x20 : public ESensor {

 public:

  // Do not initialize temperature device yet.
  TemperatureDS18x20(ESensors *sensors=0);
  
  // Initialize temperature device with DATA on pin.
  TemperatureDS18x20(uint8_t pin);
  
  // Initialize temperature device with DATA on pin.
  TemperatureDS18x20(ESensors *sensors, uint8_t pin);
  
  // Initialize temperature device with DATA on pin.
  void begin(uint8_t pin);

  // Return true if temperature sensor is available.
  virtual bool available();

  // Recommended delay between a request() and read() in milliseconds.
  virtual unsigned long delayTime() const { return 1000; };

  // The temperature in degrees celsius.
  // On error, return -INFINITY.
  // Before you can retrieve a temperature reading,
  // you need to call request(), wait for at least delay() milliseconds,
  // and then call get().
  virtual float reading() const;
  
  
 private:

  // Request a temperature conversion.
  virtual void requestData();

  // Retrieve a temperature reading from the device.
  virtual void getData();

  OneWire  OW;
  int Type_s;
  byte Addr[8];
  float Celsius;
};


#endif
