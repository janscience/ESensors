# Water level

Apparently, measuring water level by means of a laser or ultrasound is difficult (why exactly?).

Better to measure hydrostatic pressure *pw* against atmospheric pressure *p0* right above the water: *pw - p0 = rho g h*. Then the water level is *h= (pw-p0)/(rho g)* above the pressure sensor.

Note, that *pw* is measured in non-flowing water!

Note, that the temperature dependence of the water density matters!

E.g.
- [Integrated Silicon Pressure Sensor](https://www.nxp.com/docs/en/data-sheet/MPX5050.pdf)
- [Gravity Water Pressure Sensor](https://wiki.dfrobot.com/Gravity__Water_Pressure_Sensor_SKU__SEN0257)
- Search Conrad for "Drucksensor"
