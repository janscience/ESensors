/* Simple sketch for measuring water conductivity.

The resistance between two electrodes is measured by analog input.
 */


#include <Arduino.h>
#include <ADC.h>
#include <ADC_Module.h>
#include <ESensor.h>
#include <ESensors.h>

int adc = 0;
uint8_t upin = 17;       // pin for output of U
uint8_t vpin = 16;       // analog input pin for V
unsigned int bits = 12;  // resolution of analog input
float alpha = 1.0;       // calibration factor K/R_0


class VoltageSensor : public ESensor {

 public:

  VoltageSensor(ESensors *sensors=0);
  VoltageSensor(ADC_Module *adc, int pin, ESensors *sensors=0);

  void begin(uint8_t bits=12, uint8_t average=4);
  void begin(ADC_Module *adc, int pin, uint8_t bits=12, uint8_t average=4);

  virtual bool available();

  virtual unsigned long delayTime() const;
  
  virtual float reading() const;
  
  float rawReading() const;

  
 protected:

  virtual void requestData();

  virtual void getData();

  ADC_Module *ADConv;
  int Pin;
  uint8_t Bits;
  float VMax;
  float Raw;
};


VoltageSensor::VoltageSensor(ESensors *sensors) :
  ESensor(sensors, "voltage", "V", "V", "%7.5f"),
  ADConv(0),
  Pin(-1),
  Bits(0),
  VMax(0.0),
  Raw(0.0) {
}
			      

VoltageSensor::VoltageSensor(ADC_Module *adc, int pin, ESensors *sensors) :
  ESensor(sensors, "voltage", "V", "V", "%7.5f"),
  ADConv(adc),
  Pin(pin),
  Bits(0),
  VMax(0.0),
  Raw(0.0) {
}
			      

void VoltageSensor::begin(uint8_t bits, uint8_t average) {
  if (ADConv == 0 || Pin < 0)
    return;
  pinMode(Pin, INPUT);   
  //ADConv->setConversionSpeed(ConversionSpeed);  
  //ADConv->setSamplingSpeed(SamplingSpeed);
  ADConv->setAveraging(average);
  ADConv->setResolution(bits);
  Bits = ADConv->getResolution();
  VMax = 3.3;
  setResolution(VMax/(1 << Bits));
  if (Bits <= 10)
    setFormat("%5.3f");
  else if (Bits <= 12)
    setFormat("%6.4f");
  else
    setFormat("%7.5f");
}


void VoltageSensor::begin(ADC_Module *adc, int pin,
			  uint8_t bits, uint8_t average) {
  ADConv = adc;
  Pin = pin;
  begin(bits, average);
}


bool VoltageSensor::available() {
  return (ADConv != 0 && Pin >= 0 && Bits > 0);
}


unsigned long VoltageSensor::delayTime() const {
  return 10;
}


float VoltageSensor::reading() const {
  return Raw*VMax;
}


float VoltageSensor::rawReading() const {
  return Raw;
}


void VoltageSensor::requestData() {
  ADConv->startSingleRead(Pin);
}


void VoltageSensor::getData() {
  Raw = ADConv->readSingle()/float(1 << Bits);
}



class VoltageDrop : public VoltageSensor {

 public:

  VoltageDrop(ESensors *sensors=0);
  VoltageDrop(ADC_Module *adc, int pin, int upin, ESensors *sensors=0);

  void begin(uint8_t bits=12, uint8_t average=4);
  void begin(ADC_Module *adc, int pin, int upin, uint8_t bits=12, uint8_t average=4);
  
  virtual bool available();

  
 protected:

  virtual void requestData();

  virtual void getData();
  
  int UPin;
};


VoltageDrop::VoltageDrop(ESensors *sensors) :
  VoltageSensor(sensors),
  UPin(-1) {
}
			      

VoltageDrop::VoltageDrop(ADC_Module *adc, int pin, int upin,
			 ESensors *sensors) :
  VoltageSensor(adc, pin, sensors),
  UPin(upin) {
}
			      

void VoltageDrop::begin(uint8_t bits, uint8_t average) {
  VoltageSensor::begin(bits, average);
}


void VoltageDrop::begin(ADC_Module *adc, int pin, int upin,
			uint8_t bits, uint8_t average) {
  VoltageSensor::begin(adc, pin, bits, average);
  UPin = upin;
  if (UPin >= 0)
    pinMode(UPin, OUTPUT);
}


bool VoltageDrop::available() {
  return (VoltageSensor::available() && UPin >= 0);
}


void VoltageDrop::requestData() {
  digitalWrite(UPin, HIGH);
  VoltageSensor::requestData();
}


void VoltageDrop::getData() {
  VoltageSensor::getData();
  digitalWrite(UPin, LOW);
}



ADC ADConv;
VoltageDrop VD;


void setup() {
  Serial.begin(9600);
  while (!Serial && millis() < 2000) {};
  VD.begin(ADConv.adc[adc], vpin, upin, 12, 16);
}


void loop() {
  VD.read();
  float vu = VD.rawReading();
  float kappa = alpha*(1.0/vu - 1.0);
  Serial.printf("V/U = %6.4f  conductivity = %6.5g uS/cm\n", vu, kappa);
  delay(1000);
}
