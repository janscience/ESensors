# Water level

Apparently, measuring water level by means of a laser or ultrasound is difficult (why exactly?).

Better to measure hydrostatic pressure $p_w$ against atmospheric pressure $p_0$ right above the water:
```math
p_w - p_0 = \rho g h
```
Then the water level is
```math
h= \frac{p_w-p_0}{\rho g}
```
above the pressure sensor.

Note, that $p_w$ is measured in non-flowing water!

Note, that the temperature dependence of the water density matters!

E.g.
- [Integrated Silicon Pressure Sensor](https://www.nxp.com/docs/en/data-sheet/MPX5050.pdf)
- [Gravity Water Pressure Sensor](https://wiki.dfrobot.com/Gravity__Water_Pressure_Sensor_SKU__SEN0257)
- [submersible pressure level sensor](https://wiki.dfrobot.com/Throw-in_Type_Liquid_Level_Transmitter_SKU_KIT0139)
- Search Conrad for "Drucksensor"
- [MS5803 pressure sensor](https://www.sparkfun.com/products/12909) as used in [DiveIno](http://www.diveino.hu/2016/06/03/AssemblyCase/)

