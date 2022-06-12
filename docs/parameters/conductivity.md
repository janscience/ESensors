# Water conductivity

Quantified via electrical conductivity (EC) between two electrodes. 

- Resistance *R* (&#8486;) measured between two electrodes in the water.

- Cell constant *K* (1/cm)

  ![cellconstant](images/cellconstant.svg)

  as distance *d* between electrodes (cm) divided by effective area
  *A* of the electrodes (cm<sup>2</sup>). Should be less than 1
  cm<sup>-1</sup> for low conductivity measurements - see chart below.

- Conductivity

  ![conductivity](images/conductivity.svg)

  is the inverse of the resistance *R* scaled by the geometry of the
  electrodes as captured by the cell konstant *K*. Conductivity is
  usually measured in mS/cm.

![cell constants](https://andyjconnelly.files.wordpress.com/2017/07/electrical-conductivity-of-common-solutions3.png?w=1140&h=921)

Use AC current to measure resistance between electrodes with amplitude
below 1.1V to avoid electrolysis. Lower frequency for low
conductivities (300Hz up to less than 100kHz?).


## Temperature correction

Conductivity depends on temperature. It is usually temperature
corrected to 20&#8451; or 25&#8451;.

- Linear temperature correction for moderate and high conductivities:

  ![tempcorrection](images/conductivity-tempcorr.svg)
  
  &alpha; is about 2 to 5 %/K for drinking water or pure water, respectively.

- Non-linear correction by polynomial of 4th order acording to
  "Natural Water temperature correction (ISO/DIN 7888)".


## Voltage divider for measuring conductivity

We measure the resistance *R* of the water between two electrodes by
means of a voltage devider. A voltage *U* is applied to a resistance
*R<sub>0</sub>* in series with the resistance *R* of the water. We
measure the voltage drop *V* over *R* against ground. *R<sub>0</sub>*
is needed to limit the maximum current for high water conductivities.

With Ohm's law we get for the voltage divider the two equations

![voltagedivider](images/conductivity-voltagedivider.svg)

that result in

![waterresistance](images/conductivity-resistance.svg)

Solving for the water conductivity yields

![conductivity](images/conductivity-conductivity.svg)

This is a function with a single unknown: *&alpha;=K/R<sub>0</sub>*,
that relates the measured voltage with water conductivity. *U/V* is the
maximum integer value of `analogRead()` divided by the returned value
of `analogRead()`. `analogRead()` measures *V* relative to *U*!

This is implemented in the [conductivity
example](../../examples/conductivity).


### Choosing the voltage divider resistance

How to choose *R<sub>0</sub>*? It definitely should be large enough to
limit the current to the maximum current of *I<sub>max</sub>* = 10mA
the Teensy supplies at ts digital pins with *U =* 3.3V. This is
ensured by a minimum overall resistance of *U/I<sub>max</sub>* =
3.3V/10mA = 330&#8486;. So with *R<sub>0</sub>* = 330&#8486; or larger
we definitely do not harm the Teensy.

However, we would like to choose *R<sub>0</sub>* such that we make use
of as much of the voltage range we can measure. On the other hand, we
also do not want to use the full voltage range, because at the extreme
values we might get into some trouble because of clipping. Rearranging
the voltage-divider equation we get

![R0](images/conductivity-r0.svg)

For the water resistance *R* we expect for a large conductivity of
&kappa; = 5mS cm<sup>-1</sup> and a cell constant of *K* =
0.1cm<sup>-1</sup> a minimal resistance *R<sub>min</sub>* =
0.1cm<sup>-1</sup>/5mS cm<sup>-1</sup> = 20&#8486;. For the smallest
conductivity of &kappa; = 0.001mS cm<sup>-1</sup> we get a maximum
resistance of *R<sub>max</sub>* = 0.1cm<sup>-1</sup>/0.001mS
cm<sup>-1</sup> = 100k&#8486;. With a cell constant of *K* =
1cm<sup>-1</sup> these values are ten-fold larger.

Using the equation for *R<sub>0</sub>* we then get for
*R<sub>max</sub>* and for various values of the maximum voltage ratio
*V/U*:

| *V/U*  | *U/V-1* | *R<sub>0</sub>* |
| -----: | ------: | --------------: |
|   0.98 |    0.02 |       2k&#8486; |
|   0.95 |    0.05 |       5k&#8486; |
|   0.90 |    0.11 |      11k&#8486; |

and for *R<sub>min</sub>* and some minimum voltage ratios:

| *V/U*  | *U/V-1* | *R<sub>0</sub>* |
| -----: | ------: | --------------: |
|   0.02 |      49 |       1k&#8486; |
|   0.05 |      19 |      380&#8486; |
|   0.10 |       9 |      180&#8486; |

If we want to be precise for small conductivities, then we should set
*R<sub>0</sub>* to more than 1k&#8486;. A resistance of *R<sub>0</sub>* =
5k&#8486; might be a good choice.

If, on the other hand, we want to be precise for large conductivities,
then a smaller resistance is to be prefered. But *R<sub>0</sub>*
should never be smaller than 330&#8486; to ensure that no more than
10mA are drawn from the Teensy.


### Calibration

How to calibrate the resistance measurements to the right
conductivities? We have just a single free parameter
*&alpha;=K/R<sub>0</sub>*. So ideally we only need a single
measurement of the relative voltage drop *V<sub>0</sub>/U* and a
corresponding reading &kappa;<sub>0</sub> from a calibrated
conductivity meter or from a standard solution. Then we calculate
*&alpha;* according to

![alpha](images/conductivity-alpha.svg)

*&alpha;* has the same units as the conductivity.


### Corrosion

If we apply the voltage *U* continuously, then the electrodes quickly
start to corrode. Following approach taken for the [Three Dollar EC -
PPM
Meter](https://hackaday.io/project/7008-hacking-the-way-to-growing-food/log/24646-three-dollar-ec-ppm-meter-arduino)
it is sufficient to apply the voltage for only a brief period of time,
i.e. one millisecond or so. And we might be happy if we measure
conductivity only every 10 seconds or even less often. By minimizing
polarization time in this way, we might get away with applying a
unipolar voltage. This needs to be testet!


## Resources

- [Cave pearl
  project](https://thecavepearlproject.org/2017/08/12/measuring-electrical-conductivity-with-an-arduino-part1-overview/):
  nice overview to many intersting resources on EC measurements.

- [Conductivity- Theory and
  Practice](https://pdf4pro.com/fullscreen/conductivity-theory-and-practice-analytical-chemistry-uoc-gr-5b91b7.html):
  all the equations and a calibration table for KCl solutions at the
  end.

- [FAQ
  conductivity](https://www.snowpure.com/docs/FAQ_Conductivity_Thornton.pdf):
  the equations and calibration explained.

- [Conductivity, salinity, and
  TDS](https://www.fondriest.com/environmental-measurements/parameters/water-quality/conductivity-salinity-tds/).

- [TDS (Total disolved
  solids)](https://en.wikipedia.org/wiki/Total_dissolved_solids).

- Conversion from EC to ppm by different companies:
  [stackexchange](https://arduino.stackexchange.com/questions/49895/how-to-measure-electrical-conductivity-using-arduino)
  ![conversion](https://i.stack.imgur.com/VpcM3.png)
  
- do not use DC current, because of corrosion of the electrodes! See
  https://hackaday.io/project/7008-hacking-the-way-to-growing-food/log/24646-three-dollar-ec-ppm-meter-arduino

- Long list of more background: [Public
  lab](https://publiclab.org/wiki/conductivity_sensing?raw=true)


## Probe design

- [Public lab: conductivity and temperature
  meter](https://publiclab.org/notes/bhickman/05-09-2016/conductivity-and-temperature-meter):
  graphit electrodes!

- Probe design and many links: [Public
  lab](https://publiclab.org/wiki/conductivity_sensing?raw=true).


## Hardware

- [Aqualab inductive conductivity digital
  sensor](https://en.aqualabo.fr/ctzn-digital-sensor-bare-wires-7-m-cable-plastic-connection-immersio-b3996.html).

- [Aqualab conductivity digital
  sensor](https://en.aqualabo.fr/-b49802.html).

- [Atlas Scientific
  EZO](https://atlas-scientific.com/embedded-solutions/ezo-conductivity-circuit/):
  professional but pricy.

- [CN0349 fully isolated conductivity measurement data acquisition
  system](https://www.analog.com/en/design-center/reference-designs/circuits-from-the-lab/cn0349.htm)
  with code
  [CN0349_ConductivitySensor](https://github.com/joshagirgis/CN0349-Arduino-Based-Library).

- [Gravity: Analog Electrical Conductivity
  Sensor](https://www.dfrobot.com/product-1123.html): analog voltage
  as output.

- [Sparky's
  widgets](https://www.sparkyswidgets.com/product/miniec-ec-interface/)
  open source: [github](https://github.com/SparkysWidgets/MinieCHW).

- [seeed Grove -
  TDS-Sensor](https://www.berrybase.de/sensoren-module/feuchtigkeit/seeed-grove-tds-sensor-f-252-r-wasserqualit-228-t-40-gesamt-gel-246-ste-feststoffe-41?sPartner=g_shopping&gclid=Cj0KCQjw0umSBhDrARIsAH7FCofDsb8Z6-ynEMNAZwE0Gre-t0X1yo29wt90GJA0Gb-0whBz4ktg6K8aArFzEALw_wcB#):
  TDS encoded in analog voltage, nice electrode pair.

- [How To Interface TDS Water Conductivity Sensor Module with
  Arduino](https://tutorials.probots.co.in/using-analog-tds-water-conductivity-sensor-water-proof-module-for-arduino/):
  applies AC and converts resistance into DC voltage.


## Arduino projects

- [Three Dollar EC - PPM
  Meter](https://hackaday.io/project/7008-hacking-the-way-to-growing-food/log/24646-three-dollar-ec-ppm-meter-arduino):
  nice and simple, and well explained.

- [Arduino Electrical Conductivity (EC - PPM - TDS)
  Meter](https://create.arduino.cc/projecthub/mircemk/arduino-electrical-conductivity-ec-ppm-tds-meter-c48201).

- [Water Probe with Arduino
  Uno](https://create.arduino.cc/projecthub/EDUcentrum/water-probe-with-arduino-uno-423483):
  very simple conversions from Ohm, to Siemens and to ppm.

- [Build and Test a Conductivity Probe with
  Arduino](https://www.teachengineering.org/activities/view/nyu_probe_activity1):
  very detailed and didactic. Instructions for assembling a probe.
