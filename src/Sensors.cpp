#include <TimeLib.h>
#include <Sensors.h>


Sensors::Sensors() :
  NSensors(0),
  MaxDelay(0),
  Interval(10000),
  Time(0),
  TimeStamp(0),
  State(0),
  PrintTime(ISO_TIME),
  DF(),
  MData(0) {
  UseInterval = Interval;
  Header[0] = '\0';
  Data[0] = '\0';
}


void Sensors::addSensor(Sensor &sensor) {
  if (NSensors >= MaxSensors) {
    Serial.println("Maximum number of supported sensors exceeded!");
    return;
  }
  Snsrs[NSensors++] = &sensor;
}


uint8_t Sensors::sensors() const {
  uint8_t n = 0;
  for (uint8_t k=0; k<NSensors; k++) {
    if (Snsrs[k]->available())
      n++;
  }
  return n;
}


float Sensors::interval() const {
  return 0.001*Interval;
}


void Sensors::setInterval(float interval) {
  Interval = (unsigned long)(1000.0*interval);
}


void Sensors::report() {
  char ds[2] = {'\0', '\0'};
  if (NSensors > 1)
    ds[0] = 's';
  Serial.printf("%d of %d sensor%s available, read every %gs:\n",
		sensors(), NSensors, ds, 0.001*Interval);
  int n = 0;
  for (uint8_t k=0; k<NSensors; k++) {
    if (Snsrs[k]->available()) {
      Serial.printf("  ");
      Snsrs[k]->report();
      n++;
    }
  }
  if (n == 0)
    Serial.println("  no sensors avilable!");
}


void Sensors::start() {
  MaxDelay = 0;
  for (uint8_t k=0; k<NSensors; k++) {
    if (Snsrs[k]->available() && Snsrs[k]->delay() > MaxDelay)
      MaxDelay = Snsrs[k]->delay();
  }
  UseInterval = Interval;
  if (UseInterval < 2*MaxDelay)
    UseInterval = 2*MaxDelay;
  Time = UseInterval - MaxDelay;
  TimeStamp = 0;
  State = 0;
  Data[0] = '\0';
}


void Sensors::request() {
  for (uint8_t k=0; k<NSensors; k++)
    Snsrs[k]->request();
  State = 1;
}


void Sensors::get() {
  TimeStamp = now();
  for (uint8_t k=0; k<NSensors; k++)
    Snsrs[k]->get();
  makeCSVData();
  State = 0;
  Time -= UseInterval;
}


bool Sensors::update() {
  switch (State) {
  case 0: if (Time > UseInterval - MaxDelay)
      request();
    break;
  case 1: if (Time > UseInterval) {
      get();
      return true;
    }
    break;
  }
  return false;
}


void Sensors::read() {
  request();
  delay(delayTime());
  get();
}


bool Sensors::pending() {
  if (DF)
    return (strlen(Data) > NData/2 && !DF.isBusy());
  return false;
}


void Sensors::setPrintTime(print_time_t pt) {
  PrintTime = pt;
}


void Sensors::print(bool symbols) {
  if (PrintTime == ISO_TIME)
    Serial.printf("Timestamp = %04d-%02d-%02dT%02d:%02d:%02d\n",
		  year(TimeStamp), month(TimeStamp), day(TimeStamp),
		  hour(TimeStamp), minute(TimeStamp), second(TimeStamp));
  else if (PrintTime == SEC_TIME)
    Serial.printf("Timestamp = %lds\n", TimeStamp);
  char s[20];
  for (uint8_t k=0; k<NSensors; k++) {
    if (Snsrs[k]->available()) {
      Snsrs[k]->valueStr(s);
      if (symbols)
	Serial.printf("%s = %s%s\n", Snsrs[k]->symbol(), s, Snsrs[k]->unit());
      else
	Serial.printf("%s = %s%s\n", Snsrs[k]->name(), s, Snsrs[k]->unit());
    }
    else {
      if (symbols)
	Serial.printf("%s not available\n", Snsrs[k]->symbol());
      else
	Serial.printf("%s not available\n", Snsrs[k]->name());
    }
  }
}


void Sensors::printHeader(bool symbols) {
  int n = 0;
  if (PrintTime != NO_TIME) {
    if (symbols)
      Serial.print("t/s");
    else
      Serial.print("time/s");
    n++;
  }
  for (uint8_t k=0; k<NSensors; k++) {
    if (Snsrs[k]->available()) {
      if (n > 0)
	Serial.print('\t');
      n++;
      if (symbols)
	Serial.print(Snsrs[k]->symbol());
      else
	Serial.print(Snsrs[k]->name());
      if (strlen(Snsrs[k]->unit()) > 0)
	Serial.printf("/%s", Snsrs[k]->unit());
    }
  }
  Serial.println();
}


void Sensors::printValues() {
  int n = 1;
  // print time:
  if (PrintTime == ISO_TIME)
    Serial.printf("%04d-%02d-%02dT%02d:%02d:%02d",
		  year(TimeStamp), month(TimeStamp), day(TimeStamp),
		  hour(TimeStamp), minute(TimeStamp), second(TimeStamp));
  else if (PrintTime == SEC_TIME)
    Serial.printf("%ld", TimeStamp);
  else
    n = 0;
  char s[20];
  for (uint8_t k=0; k<NSensors; k++) {
    if (Snsrs[k]->available()) {
      if (n > 0)
	Serial.print('\t');
      n++;
      Snsrs[k]->valueStr(s);
      Serial.print(s);
    }
  }
  Serial.println();
}


bool Sensors::makeCSVHeader(bool symbols) {
  Header[0] = '\0';
  Data[0] = '\0';
  MData = 0;
  // size of header and data line:
  size_t m = 0;
  size_t n = symbols ? 3 : 8;
  if (PrintTime == NO_TIME)
    n = 0;
  for (uint8_t k=0; k<NSensors; k++) {
    if (Snsrs[k]->available()) {
      if (symbols)
	n += strlen(Snsrs[k]->symbol());
      else
	n += strlen(Snsrs[k]->name());
      n += strlen(Snsrs[k]->unit()) + 2;
      m++;
    }
  }
  if (m == 0) // no sensors
    return false;
  if (n > NHeader) // header too long
    return false;
  MData = m*10;
  if (PrintTime != NO_TIME)
    MData += 20;
  // compose header line:
  n = 0;
  char *hp = Header;
  if (PrintTime != NO_TIME) {
    if (symbols)
      hp += sprintf(hp, "t/s");
    else
      hp += sprintf(hp, "time/s");
    n++;
  }
  for (uint8_t k=0; k<NSensors; k++) {
    if (Snsrs[k]->available()) {
      if (n > 0)
	*(hp++) = ',';
      n++;
      if (symbols)
	hp += sprintf(hp, Snsrs[k]->symbol());
      else
	hp += sprintf(hp, Snsrs[k]->name());
      if (strlen(Snsrs[k]->unit()) > 0)
	hp += sprintf(hp, "/%s", Snsrs[k]->unit());
    }
  }
  *hp = '\n';
  return true;
}


bool Sensors::makeCSVData() {
  if (MData == 0)
    return false;
  if (strlen(Data) > NData - MData) {
    Serial.println("WARNING: overflow of sensors data!");
    return false;
  }
  // compose data line:
  char *sp = Data + strlen(Data);
  int n = 1;
  // print time:
  if (PrintTime == ISO_TIME)
    sp += sprintf(sp, "%04d-%02d-%02dT%02d:%02d:%02d",
		  year(TimeStamp), month(TimeStamp), day(TimeStamp),
		  hour(TimeStamp), minute(TimeStamp), second(TimeStamp));
  else if (PrintTime == SEC_TIME)
    sp += sprintf(sp, "%ld", TimeStamp);
  else
    n = 0;
  for (uint8_t k=0; k<NSensors; k++) {
    if (Snsrs[k]->available()) {
      if (n > 0)
	*(sp++) = ',';
      n++;
      sp += Snsrs[k]->valueStr(sp);
    }
  }
  *(sp++) = '\n';
  *(sp++) = '\0';
  return true;
}


bool Sensors::openCSV(SdFat &sd, const char *path,
		      bool symbols, bool append) {
  if (DF)
    closeCSV();
  if (Header[0] == '\0')
    makeCSVHeader(symbols);
  if (Header[0] == '\0') // no sensors
    return false;
  // create file and write header:
  char fpath[strlen(path)+10];
  strcpy(fpath, path);
  strcat(fpath, ".csv");
  if (append && sd.exists(fpath))
    DF = sd.open(fpath, O_RDWR | O_APPEND);
  else
    DF = sd.open(fpath, O_RDWR | O_CREAT);
  if (DF) {
    DF.write(Header, strlen(Header));
    DF.flush();
    return true;
  }
  else
    return false;
}


bool Sensors::writeCSV() {
  if (Data[0] == '\0' || !DF)
    return false;
  // write data:
  bool success = true;
  size_t n = DF.write(Data, strlen(Data));
  if (n < strlen(Data))
    success = false;
  DF.flush();
  Data[0] = '\0';        // clear buffer
  if (!DF)
    success = false;
  return success;
}


bool Sensors::closeCSV() {
  if (!DF)
    return false;
  writeCSV();
  Data[0] = '\0';        // clear buffer
  return (!DF.close());
}

