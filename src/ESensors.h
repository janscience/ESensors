/*
  ESensors - Manage environmental sensors.
  Created by Jan Benda, November 27th, 2021.
*/

#ifndef ESensors_h
#define ESensors_h


#include <Arduino.h>
#include <SdFat.h>
#include <ESensor.h>


class ESensors {

 public:
  
  enum print_time_t { NO_TIME, SEC_TIME, ISO_TIME };

  ESensors();

  // Add a sensor if available.
  void addSensor(ESensor &sensor);

  // Number of currently managed sensors.
  uint8_t size() const { return NSensors; };

  // Number of available sensors.
  uint8_t sensors() const;

  // The index-th sensor.
  ESensor &operator[](uint8_t index) { return *Snsrs[index]; };

  // Update interval for reading sensor values in seconds.
  float interval() const;

  // Set update interval for reading sensor values to interval seconds.
  void setInterval(float interval);

  // Report properties of all sensor devices on serial monitor.
  void report();

  // Start acquisition of sensor values, set delayTime(), and clear
  // data buffers.
  void start();

  // Request sensor readings from all sensors.
  void request();

  // The delay needed between request() and get().
  // Only available after calling start().
  unsigned long delayTime() const { return DelayTime; };

  // Get sensor readings from all sensors.
  void get();

  // Update sensor readings by calling request() and get() according to
  // interval() and the sensors' delayTime().
  // Call as often as possible in loop().
  // This function does not block.
  // You need to start the acquisition before by calling start().
  // Returns true if the sensor readings have been updated.
  bool update();

  // Initiate measurement (request()) of all sensors, wait for
  // delayTime(), and retrieve the data (get()).
  // This function may block considerably!
  // Before using read() for the first time you need to call start().
  void read();

  // Time stamp of last reading of sensor values.
  time_t timeStamp() const;

  // Whether and how print*() and write*() functions should output timestamps.
  void setPrintTime(print_time_t pt);

  // Report sensor readings with name (or symbol) and unit on serial monitor.
  void print(bool symbols=false);

  // Report sensor names (or symbol) and units separated by tabs on
  // serial monitor.
  void printHeader(bool symbols=false);

  // Report sensor readings separated by tabs on serial monitor.
  // If compact then use the compact format that has the width removed.
  // Use printHeader() to annotate the printed columns.
  void printValues(bool compact=false);
  
  // Create header line for CSV file.
  // Usually, this is automatically called by openCSV().
  // Returns true if header line was created.
  // Returns false if no sensors are available or header line is too long.
  bool makeCSVHeader(bool symbols=false);

  // Open csv file for sensor readings at path on SD card sd
  // and write header line.
  // If no header line was ever created, makeCSVHeader() is called.
  // path is without extension. 'csv' is added.
  // If symbols, use mathematical symbols instead of names for the header.
  // If append and path already exists, then keep the file
  // and do not write the header.
  // Return true on success, false on failure or no available sensors.
  bool openCSV(SdFat &sd, const char *path,
	       bool symbols=false, bool append=false);

  // Return true if sensor readings prepared for csv files are pending
  // and the csv file is not busy.
  bool pendingCSV();

  // Write current time and sensor readings to csv file.
  // Return true on success, false on failure or if file is not open
  // for writing.
  bool writeCSV();

  // Close csv file.
  // Return true on success.
  bool closeCSV();

  
 private:

  // Compute the maximum delay time from all available sensors.
  // Adjust interval between readings if necessary.
  void setDelayTime();
  
  // Create data line for CSV file.
  // Return false on overflow of data buffer.
  bool makeCSVData();

  static const uint8_t MaxSensors = 20; 
  uint8_t NSensors; 
  ESensor *Snsrs[MaxSensors];
  unsigned long DelayTime;
  unsigned long Interval;
  unsigned long UseInterval;
  elapsedMillis Time;
  time_t TimeStamp;
  int State;
  print_time_t PrintTime;
  FsFile DF;
  static const size_t NHeader = 256; // size of Header string
  char Header[NHeader];              // header string for CSV file
  static const size_t NData = 2048;  // 2kB size of Data string
  char Data[NData];                  // data lines for CSV file
  size_t MData;                      // approximate size of single data line
};


#endif
