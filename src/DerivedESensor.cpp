#include <ESensors.h>
#include <DerivedESensor.h>


DerivedESensor::DerivedESensor(ESensor *sensor1, ESensor *sensor2,
			       const char *name, const char *symbol,
			       const char *unit, const char *format,
			       float resolution) :
  ESensor(name, symbol, unit, format, resolution),
  NSnsr(2) {
  Snsr[0] = sensor1;
  Snsr[1] = sensor2;
  memset(DChip, 0, sizeof(DChip));
  memset(DIdentifier, 0, sizeof(DIdentifier));
}


DerivedESensor::DerivedESensor(ESensor *sensor1, ESensor *sensor2, ESensor *sensor3,
			       const char *name, const char *symbol,
			       const char *unit, const char *format,
			       float resolution) :
  ESensor(name, symbol, unit, format, resolution),
  NSnsr(3) {
  Snsr[0] = sensor1;
  Snsr[1] = sensor2;
  Snsr[2] = sensor3;
  memset(DChip, 0, sizeof(DChip));
  memset(DIdentifier, 0, sizeof(DIdentifier));
}


DerivedESensor::DerivedESensor(ESensor *sensor1, ESensor *sensor2,
			       ESensors *sensors, const char *name,
			       const char *symbol, const char *unit,
			       const char *format, float resolution) :
  ESensor(sensors, name, symbol, unit, format, resolution),
  NSnsr(2) {
  Snsr[0] = sensor1;
  Snsr[1] = sensor2;
  memset(DChip, 0, sizeof(DChip));
  memset(DIdentifier, 0, sizeof(DIdentifier));
}


DerivedESensor::DerivedESensor(ESensor *sensor1, ESensor *sensor2, ESensor *sensor3,
			       ESensors *sensors, const char *name,
			       const char *symbol, const char *unit,
			       const char *format, float resolution) :
  ESensor(sensors, name, symbol, unit, format, resolution),
  NSnsr(3) {
  Snsr[0] = sensor1;
  Snsr[1] = sensor2;
  Snsr[2] = sensor3;
  memset(DChip, 0, sizeof(DChip));
  memset(DIdentifier, 0, sizeof(DIdentifier));
}


const char* DerivedESensor::chip() const {
  char *sp = DChip;
  unsigned int n = 0;
  for (size_t k=0; k<NSnsr; k++) {
    if (strlen(Snsr[k]->chip()) > 0) {
      if (n > 0) {
	if (n + 1 < NSnsr)
	  *(sp++) = ',';
	else {
	  *(sp++) = ' ';
	  *(sp++) = '&';
	}
	*(sp++) = ' ';
      }
      strcpy(sp, Snsr[k]->chip());
      sp += strlen(Snsr[k]->chip());
      n++;
    }
  }
  return DChip;
}


const char* DerivedESensor::identifier() const {
  char *sp = DIdentifier;
  unsigned int n = 0;
  for (size_t k=0; k<NSnsr; k++) {
    if (strlen(Snsr[k]->identifier()) > 0) {
      if (n > 0) {
	if (n + 1 < NSnsr)
	  *(sp++) = ',';
	else {
	  *(sp++) = ' ';
	  *(sp++) = '&';
	}
	*(sp++) = ' ';
      }
      strcpy(sp, Snsr[k]->identifier());
      sp += strlen(Snsr[k]->identifier());
      n++;
    }
  }
  return DIdentifier;
}

  
bool DerivedESensor::available() {
  for (size_t k=0; k<NSnsr; k++) {
    if (! Snsr[k]->available())
      return false;
  }
  return true;
}


unsigned long DerivedESensor::delayTime() const {
  unsigned long dtime = 0;
  for (size_t k=0; k<NSnsr; k++) {
    if (Snsr[k]->delayTime() > dtime)
      dtime = Snsr[k]->delayTime();
  }
  return dtime;
}


void DerivedESensor::requestData() {
  for (size_t k=0; k<NSnsr; k++)
    Snsr[k]->request();
}


void DerivedESensor::getData() {
  for (size_t k=0; k<NSnsr; k++)
    Snsr[k]->get();
}


float DerivedESensor::reading() const {
  if (NSnsr == 3)
    return compute(Snsr[0]->reading(), Snsr[1]->reading(), Snsr[2]->reading());
  else
    return compute(Snsr[0]->reading(), Snsr[1]->reading());
}
