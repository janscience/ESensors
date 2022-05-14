/*
  ESensor - Virtual base class for reading a value from an environmental sensor.
  Created by Jan Benda, November 27th, 2021.
*/

#ifndef ESensor_h
#define ESensor_h


#include <Arduino.h>
#include <TimeLib.h>
#include <ESensorDevice.h>


class ESensors;


class ESensor : public ESensorDevice {

 public:

  // Initialize the sensor.
  ESensor();

  // Initialize the sensor and set name, mathematical symbol, basic unit,
  // format, and resolution of sensor readings.
  // The derived unit is also set to unit, the conversion factor
  // is set to one, the offset to zero.
  ESensor(const char *name, const char *symbol, const char *unit,
	  const char *format, float resolution=1.0);

  // Initialize the sensor, add it to sensors, and set name,
  // mathematical symbol, basic unit, format and resolution of sensor
  // readings.
  // The derived unit is also set to unit, the conversion factor
  // is set to one, the offset to zero.
  ESensor(ESensors *sensors, const char *name, const char *symbol,
	  const char *unit, const char *format, float resolution=1.0);

  // Return name of environmental sensor reading as character array.
  const char* name() const;

  // Set name of environmental sensor reading to name.
  void setName(const char *name);

  // Set name and mathematical symbol of environmental sensor reading.
  void setName(const char *name, const char *symbol);

  // Return mathematical symbol of environmental sensor reading as
  // character array.
  const char* symbol() const;

  // Set mathematical symbol of environmental sensor reading to name.
  void setSymbol(const char *symbol);

  // Return unit of sensor readings as character array.
  const char* basicUnit() const;

  // Return unit of derived sensor values as character array.
  const char* unit() const;

  // Set unit of environmental sensor reading to unit.
  // Optionally, the sensor reading can be mutliplied by factor and
  // offsetted by offset to result in the desired unit.
  void setUnit(const char *unit, float factor=1.0, float offset=0.0);

  // Set unit, conversion factor, offset, and format string of environmental
  // sensor reading.
  void setUnit(const char *unit, float factor, float offset,
	       const char *format);

  // Set unit, conversion factor, and format string of environmental
  // sensor reading. The offset is set to zero.
  void setUnit(const char *unit, float factor, const char *format);

  // Return format string for sensor readings as character array.
  const char* format() const;

  // Return format string for sensor readings without width as character array.
  const char* compactFormat() const;

  // Set format string for environmental sensor reading to format.
  void setFormat(const char *format);

  // Return resolution of the sensor readings in the current unit.
  // In case this function is reimplemented, it should multiply the
  // resolution with Factor before returning the value.
  virtual float resolution() const;
  
  // Print the resolution into string s.
  // If compact then use the compact format that has the width removed.
  // Return the number of printed characters.
  int resolutionStr(char *s, bool compact=false) const;
  
  // Report properties of sensor on serial monitor.
  virtual void report();

  // The sensor reading in the basic unit.
  // On error, return -INFINITY.
  // Before you can retrieve a sensor reading,
  // you need to call request(), wait for at least delayTime() milliseconds,
  // and then call read().
  virtual float reading() const = 0;

  // The sensor reading in the current unit.
  // This default implementation multiplies the sensor reading() with Factor
  // and adds Offset.
  virtual float value() const;
  
  // Print the sensor reading using format string into string s.
  // If compact then use the compact format that has the width removed.
  // Return the number of printed characters.
  int valueStr(char *s, bool compact=false) const;

  // Initiate measurement (request()), wait for delayTime(), retrieve the
  // data (get()) and return the result (value()).
  // This function may block considerably!
  float read();

  // Special unit conversions for SI prefixes:

  // Set SI prefix for unit that scales the unit by `factor` and
  // shifts the number of decimals in the format by `decimals`.
  void setSIPrefix(const char *prefix, float factor, int decimals);

  // Set unit to micro (factor to 1e6 and prepend unit with an 'µ').
  void setMicro() { setSIPrefix("µ", 1e6, -6); };

  // Set unit to milli (factor to 1e3 and prepend unit with an 'm').
  void setMilli() { setSIPrefix("m", 1e3, -3); };

  // Set unit to centi (factor to 1e2 and prepend unit with an 'c').
  void setCenti() { setSIPrefix("c", 1e2, -2); };

  // Set unit to hecto (factor to 1e-2 and prepend unit with an 'h').
  void setHecto() { setSIPrefix("h", 1e-2, 2); };

  // Set unit to kilo (factor to 1e-3 and prepend unit with an 'k').
  void setKilo() { setSIPrefix("K", 1e-3, 3); };

  // Set unit to Mega (factor to 1e-6 and prepend unit with an 'M').
  void setMega() { setSIPrefix("M", 1e-6, 6); };
  
  // Special unit conversions for unit-less ratios or fractions:

  // Set unit to percent:
  void setPercent();
  
  // Special unit conversions for temperatures measured in degrees celsius:

  // Set unit to Kelvin.
  void setKelvin();

  // Set unit to Fahrenheit.
  void setFahrenheit();
  
  // Special unit conversions for pressures measured in Pascal:
  // https://www.beamex.com/resources/pressure-unit-converter/

  // Set unit to bar.
  void setBar();

  // Set unit to mbar.
  void setMilliBar();

  // Set unit to at.
  void setAt();

  // Set unit to atm.
  void setAtm();

  // Set unit to mm Hg.
  void setMMHg();

  // Set unit to psi.
  void setPSI();

  // Set unit to torr.
  void setTorr();

  
protected:

  // Set resolution of the sensor in its basic unit.
  void setResolution(float resolution);

  // Parse the format string.
  void parseFormat(char *prefix, int *width,
		   int *decimals, char *ftype) const;
  
  // Adapt format string to accomodate more or less decimals.
  void adaptFormat(int decimals);

  char Name[50];
  char Symbol[20];
  char BasicUnit[20];
  char Unit[20];
  char Format[10];
  char CompactFormat[10];
  float Factor;
  float Offset;
  float Resolution;
  
};


#endif
