# Water conductivity

Qunatified via electrical conductivity (EC) between two electrodes. 

- *R*: Resistance measured between two electrodes in the water.
- *K=d/a*: cell constant (1/cm) as distance between electrodes (cm) divided by effective area of the electrodes (cm squared). Should be less than 1/cm for low conductivity measurements.
- *g=K/R*: conductivity, usually in mS/cm.

![cell constants](https://andyjconnelly.files.wordpress.com/2017/07/electrical-conductivity-of-common-solutions3.png?w=1140&h=921)

Use AC current to measure resistance between electrodes with amplitude below 1.1V to avoid electrolysis. Lower frequency for low conductivities (300Hz up to less than 100kHz?).


## Temperature correction

Conductivity depends on temperature. It is usually temperature corrected to 20 or 25 degrees celsisus.

- Linear temperature correction for moderate and high conductivities: *gref = g /(1+c(T-Tref))*,
  c is about 2 to 5 %/Kelvin for drinking water or pure water, respectively.
- Non-linear correction by polynomial of 4th order acording to "Natural Water temperature correction  (ISO/DIN  7888)".


## Resources

- [Cave pearl project](https://thecavepearlproject.org/2017/08/12/measuring-electrical-conductivity-with-an-arduino-part1-overview/): nice overview to many intersting resources on EC measurements
- [Conductivity-  Theory and Practice](https://pdf4pro.com/fullscreen/conductivity-theory-and-practice-analytical-chemistry-uoc-gr-5b91b7.html): all the equations and a calibration table for KCl solutions at the end.
- [Conductivity, salinity, and TDS](https://www.fondriest.com/environmental-measurements/parameters/water-quality/conductivity-salinity-tds/)
- [TDS (Total disolved solids)](https://en.wikipedia.org/wiki/Total_dissolved_solids)
- Conversion from EC to ppm by different companies: [stackexchange](https://arduino.stackexchange.com/questions/49895/how-to-measure-electrical-conductivity-using-arduino)
  ![conversion](https://i.stack.imgur.com/VpcM3.png)
- do not use DC current, because of corrosion of the electrodes! See https://hackaday.io/project/7008-hacking-the-way-to-growing-food/log/24646-three-dollar-ec-ppm-meter-arduino
- Long list of more background: [Public lab](https://publiclab.org/wiki/conductivity_sensing?raw=true)


## Hardware

- Probe design and many links: [Public lab](https://publiclab.org/wiki/conductivity_sensing?raw=true)
- [Atlas Scientific EZO](https://atlas-scientific.com/embedded-solutions/ezo-conductivity-circuit/): professional but pricy.
- [CN0349 fully isolated conductivity measurement data acquisition system](https://www.analog.com/en/design-center/reference-designs/circuits-from-the-lab/cn0349.htm) with code [CN0349_ConductivitySensor](https://github.com/joshagirgis/CN0349-Arduino-Based-Library)
- [Gravity: Analog Electrical Conductivity Sensor](https://www.dfrobot.com/product-1123.html): analog voltage as output
- [Sparky's widgets](https://www.sparkyswidgets.com/product/miniec-ec-interface/) open source: [github](https://github.com/SparkysWidgets/MinieCHW)
- [seeed Grove - TDS-Sensor](https://www.berrybase.de/sensoren-module/feuchtigkeit/seeed-grove-tds-sensor-f-252-r-wasserqualit-228-t-40-gesamt-gel-246-ste-feststoffe-41?sPartner=g_shopping&gclid=Cj0KCQjw0umSBhDrARIsAH7FCofDsb8Z6-ynEMNAZwE0Gre-t0X1yo29wt90GJA0Gb-0whBz4ktg6K8aArFzEALw_wcB#): TDS encode in analog voltage, nice electrode pair.
- [How To Interface TDS Water Conductivity Sensor Module with Arduino](https://tutorials.probots.co.in/using-analog-tds-water-conductivity-sensor-water-proof-module-for-arduino/): applies AC and conversts resistance into DC voltage.


## Arduino projects

- [Three Dollar EC - PPM Meter](https://hackaday.io/project/7008-hacking-the-way-to-growing-food/log/24646-three-dollar-ec-ppm-meter-arduino): nice and simple, but with quite some of theoretical background.
- [Arduino Electrical Conductivity (EC - PPM - TDS) Meter](https://create.arduino.cc/projecthub/mircemk/arduino-electrical-conductivity-ec-ppm-tds-meter-c48201)
- [Water Probe with Arduino Uno](https://create.arduino.cc/projecthub/EDUcentrum/water-probe-with-arduino-uno-423483): very simple conversions from Ohm, to Siemens and to ppm.
- [Build and Test a Conductivity Probe with Arduino](https://www.teachengineering.org/activities/view/nyu_probe_activity1): very detailed and didactic. Instructions for assembling a probe.
