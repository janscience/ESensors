#include <TimeLib.h>
#include <ESensors.h>


ESensors::ESensors() :
  NSensors(0),
  DelayTime(0),
  Interval(0),
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


void ESensors::addSensor(ESensor &sensor) {
  if (NSensors >= MaxSensors) {
    Serial.println("ERROR: Maximum number of supported sensors exceeded!");
    return;
  }
  Snsrs[NSensors++] = &sensor;
}


uint8_t ESensors::sensors() const {
  uint8_t n = 0;
  for (uint8_t k=0; k<NSensors; k++) {
    if (Snsrs[k]->available())
      n++;
  }
  return n;
}


float ESensors::interval() const {
  return 0.001*Interval;
}


void ESensors::setInterval(float interval) {
  Interval = (unsigned long)(1000.0*interval);
}


void ESensors::report(Stream &stream) {
  char ds[2] = {'\0', '\0'};
  if (NSensors > 1)
    ds[0] = 's';
  stream.printf("%d of %d environmental sensor%s available, read every %gs:\n",
		sensors(), NSensors, ds, 0.001*Interval);
  int n = 0;
  for (uint8_t k=0; k<NSensors; k++) {
    if (Snsrs[k]->available()) {
      stream.printf("  ");
      Snsrs[k]->report(stream);
      n++;
    }
  }
  if (n == 0 && NSensors > 0)
    stream.println("  no sensors available!");
  stream.println();
}


void ESensors::reportDevices(Stream &stream) {
  // compile list of uniques devices:
  ESensorDevice *devices[NSensors];
  uint8_t ndevices = 0;
  uint8_t adevices = 0;
  for (uint8_t k=0; k<NSensors; k++) {
    if (Snsrs[k]->device()) {
      bool found = false;
      for (uint8_t j=0; j<ndevices; j++) {
	if (devices[j] == Snsrs[k]->device()) {
	  found = true;
	  break;
	}
      }
      if (!found) {
	devices[ndevices++] = Snsrs[k]->device();
	if (Snsrs[k]->device()->available())
	  adevices++;
      }
    }
  }
  // report:
  char ds[2] = {'\0', '\0'};
  if (ndevices > 1)
    ds[0] = 's';
  stream.printf("%d of %d environmental sensor device%s available:\n",
		adevices, ndevices, ds);
  int n = 0;
  for (uint8_t k=0; k<ndevices; k++) {
    if (devices[k]->available()) {
      stream.printf("  ");
      devices[k]->ESensorDevice::report(stream);
      n++;
    }
  }
  if (n == 0 && ndevices > 0)
    stream.println("  no sensor device available!");
  stream.println();
}


void ESensors::setDelayTime() {
  // find maximum delay:
  DelayTime = 0;
  for (uint8_t k=0; k<NSensors; k++) {
    if (Snsrs[k]->available()) {
      unsigned long delay_time = Snsrs[k]->delayTime();
      if (delay_time > DelayTime)
	DelayTime = delay_time;
    }
  }
  // adjust interval between readings:
  UseInterval = Interval;
  if (UseInterval < DelayTime + 10)
    UseInterval = DelayTime + 10;
}


void ESensors::start() {
  setDelayTime();
  Time = UseInterval - delayTime();
  TimeStamp = 0;
  State = 0;
  Data[0] = '\0';
}


void ESensors::request() {
  if (State > 0)
    return;
  for (uint8_t k=0; k<NSensors; k++) {
    Snsrs[k]->request();
    Retrieving[k] = true;
  }
  RequestTime = Time;
  State = 1;
}


bool ESensors::retrieve(unsigned long time) {
  if (State != 1)
    return false;
  bool done = true;
  for (uint8_t k=0; k<NSensors; k++) {
    if (Retrieving[k]) {
      bool r = Snsrs[k]->retrieve(time);
      if (r)
	Retrieving[k] = false;
      else
	done = false;
    }
  }
  return done;
}


void ESensors::get() {
  if (State != 1)
    return;
  TimeStamp = now();
  for (uint8_t k=0; k<NSensors; k++)
    Snsrs[k]->get();
  makeCSVData();
  State = 0;
  Time -= UseInterval;
}


bool ESensors::update() {
  switch (State) {
  case 0: if (Time + delayTime() > UseInterval)
      request();
    break;
  case 1: if (Time > UseInterval) {
      get();
      setDelayTime();
      return true;
    }
    else
      retrieve(Time - RequestTime);
    break;
  }
  return false;
}


void ESensors::read() {
  request();
  elapsedMillis time = 0;
  while (time < delayTime()) {
    if (retrieve(time))
      break;
  }
  if (time < delayTime())
    delay(delayTime() - time);
  get();
}


time_t ESensors::timeStamp() const {
  return TimeStamp;
}


void ESensors::setPrintTime(print_time_t pt) {
  PrintTime = pt;
}


void ESensors::print(bool symbols, bool oneline, Stream &stream) {
  if (PrintTime != NO_TIME) {
    char tsep[3] = "\n";
    if (oneline)
      strcpy(tsep, ": ");
    else
      stream.print("Timestamp = ");
    if (PrintTime == ISO_TIME)
      stream.printf("%04d-%02d-%02dT%02d:%02d:%02d%s",
		    year(TimeStamp), month(TimeStamp), day(TimeStamp),
		    hour(TimeStamp), minute(TimeStamp), second(TimeStamp),
		    tsep);
    else if (PrintTime == SEC_TIME)
      stream.printf("%llds%s", TimeStamp, tsep);
  }
  char s[20];
  for (uint8_t k=0; k<NSensors; k++) {
    if (oneline && k > 0)
      stream.printf(", ");
    if (Snsrs[k]->available()) {
      Snsrs[k]->valueStr(s, true);
      if (symbols)
	stream.printf("%s = %s%s", Snsrs[k]->symbol(), s, Snsrs[k]->unit());
      else
	stream.printf("%s = %s%s", Snsrs[k]->name(), s, Snsrs[k]->unit());
    }
    else {
      if (oneline) {
	if (symbols)
	  stream.printf("%s = -", Snsrs[k]->symbol());
	else
	  stream.printf("%s = -", Snsrs[k]->name());
      }
      else {
	if (symbols)
	  stream.printf("%s not available\n", Snsrs[k]->symbol());
	else
	  stream.printf("%s not available\n", Snsrs[k]->name());
      }
    }
    if (!oneline)
      stream.printf("\n");
  }
  if (oneline)
    stream.printf("\n");
}


void ESensors::printHeader(bool symbols, Stream &stream) {
  int n = 0;
  if (PrintTime != NO_TIME) {
    if (symbols)
      stream.print("t/s");
    else
      stream.print("time/s");
    n++;
  }
  for (uint8_t k=0; k<NSensors; k++) {
    if (Snsrs[k]->available()) {
      if (n > 0)
	stream.print('\t');
      n++;
      if (symbols)
	stream.print(Snsrs[k]->symbol());
      else
	stream.print(Snsrs[k]->name());
      if (strlen(Snsrs[k]->unit()) > 0)
	stream.printf("/%s", Snsrs[k]->unit());
    }
  }
  stream.println();
}


void ESensors::printValues(bool compact, Stream &stream) {
  if (sensors() == 0)
    return;
  int n = 1;
  // print time:
  if (PrintTime == ISO_TIME)
    stream.printf("%04d-%02d-%02dT%02d:%02d:%02d",
		  year(TimeStamp), month(TimeStamp), day(TimeStamp),
		  hour(TimeStamp), minute(TimeStamp), second(TimeStamp));
  else if (PrintTime == SEC_TIME)
    stream.printf("%lld", TimeStamp);
  else
    n = 0;
  char s[20];
  for (uint8_t k=0; k<NSensors; k++) {
    if (Snsrs[k]->available()) {
      if (n > 0)
	stream.print('\t');
      n++;
      Snsrs[k]->valueStr(s, compact);
      stream.print(s);
    }
  }
  stream.println();
}


bool ESensors::makeCSVHeader(bool symbols) {
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


bool ESensors::makeCSVData() {
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
    sp += sprintf(sp, "%lld", TimeStamp);
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


bool ESensors::openCSV(SdFat &sd, const char *path,
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


bool ESensors::pendingCSV() {
  if (DF)
    return (strlen(Data) > NData/2 && !DF.isBusy());
  return false;
}


bool ESensors::writeCSV() {
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


bool ESensors::closeCSV() {
  if (!DF)
    return false;
  writeCSV();
  Data[0] = '\0';        // clear buffer
  return (!DF.close());
}

