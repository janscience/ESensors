#include <Sensors.h>
#include <SensorDerived.h>


SensorDerived::SensorDerived(Sensor *sensor1, Sensor *sensor2,
			     const char *name, const char *symbol,
			     const char *unit, const char *format,
			     float resolution) :
  Sensor(name, symbol, unit, format, resolution),
  NSnsr(2) {
  Snsr[0] = sensor1;
  Snsr[1] = sensor2;
  memset(DChip, 0, sizeof(DChip));
  memset(DIdentifier, 0, sizeof(DIdentifier));
}


SensorDerived::SensorDerived(Sensor *sensor1, Sensor *sensor2, Sensor *sensor3,
			     const char *name, const char *symbol,
			     const char *unit, const char *format,
			     float resolution) :
  Sensor(name, symbol, unit, format, resolution),
  NSnsr(3) {
  Snsr[0] = sensor1;
  Snsr[1] = sensor2;
  Snsr[2] = sensor3;
  memset(DChip, 0, sizeof(DChip));
  memset(DIdentifier, 0, sizeof(DIdentifier));
}


SensorDerived::SensorDerived(Sensor *sensor1, Sensor *sensor2,
			     Sensors *sensors, const char *name,
			     const char *symbol, const char *unit,
			     const char *format, float resolution) :
  Sensor(sensors, name, symbol, unit, format, resolution),
  NSnsr(2) {
  Snsr[0] = sensor1;
  Snsr[1] = sensor2;
  memset(DChip, 0, sizeof(DChip));
  memset(DIdentifier, 0, sizeof(DIdentifier));
}


SensorDerived::SensorDerived(Sensor *sensor1, Sensor *sensor2, Sensor *sensor3,
			     Sensors *sensors, const char *name,
			     const char *symbol, const char *unit,
			     const char *format, float resolution) :
  Sensor(sensors, name, symbol, unit, format, resolution),
  NSnsr(3) {
  Snsr[0] = sensor1;
  Snsr[1] = sensor2;
  Snsr[2] = sensor3;
  memset(DChip, 0, sizeof(DChip));
  memset(DIdentifier, 0, sizeof(DIdentifier));
}


const char* SensorDerived::chip() const {
  char *sp = DChip;
  for (size_t k=0; k<NSnsr; k++) {
    if (k > 0) {
      if (k + 1 < NSnsr)
	*(sp++) = ',';
      else {
	*(sp++) = ' ';
	*(sp++) = '&';
      }
      *(sp++) = ' ';
    }
    strcpy(sp, Snsr[k]->chip());
    sp += strlen(Snsr[k]->chip());
  }
  return DChip;
}


const char* SensorDerived::identifier() const {
  char *sp = DIdentifier;
  for (size_t k=0; k<NSnsr; k++) {
    if (k > 0) {
      if (k + 1 < NSnsr)
	*(sp++) = ',';
      else {
	*(sp++) = ' ';
	*(sp++) = '&';
      }
      *(sp++) = ' ';
    }
    strcpy(sp, Snsr[k]->identifier());
    sp += strlen(Snsr[k]->identifier());
  }
  return DIdentifier;
}

  
bool SensorDerived::available() {
  for (size_t k=0; k<NSnsr; k++) {
    if (! Snsr[k]->available())
      return false;
  }
  return true;
}


unsigned long SensorDerived::delayTime() const {
  unsigned long dtime = 0;
  for (size_t k=0; k<NSnsr; k++) {
    if (Snsr[k]->delayTime() > dtime)
      dtime = Snsr[k]->delayTime();
  }
  return dtime;
}


void SensorDerived::requestData() {
  for (size_t k=0; k<NSnsr; k++)
    Snsr[k]->request();
}


void SensorDerived::getData() {
  for (size_t k=0; k<NSnsr; k++)
    Snsr[k]->get();
}


float SensorDerived::reading() const {
  if (NSnsr == 3)
    return compute(Snsr[0]->reading(), Snsr[1]->reading(), Snsr[2]->reading());
  else
    return compute(Snsr[0]->reading(), Snsr[1]->reading());
}
