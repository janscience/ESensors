# Light

Ambient light sensors (ALS)


## Units

- Radiometric: total light energy
- Photometric: takes human photopic response into account (sensitive between about 450 and 650nm, see below).

| | Radiometric | | Photometric | |
| --- | --- | --- | --- | --- |
| Energy | Radiant energy, Q | Joule (J) | Luminous energy, Q<sub>v</sub> | Lumen-second (lm-s) |
| Power | Radiant flux, &Phi; | Watt (W) | Luminous flux, F | Lumen (lm) |
| Power/Area | [Irradiance](https://en.wikipedia.org/wiki/Irradiance), E | W/m<sup>2</sup> | [Illuminance](https://en.wikipedia.org/wiki/Illuminance), E<sub>v</sub> | Lux (lx) |

(from [TAOS, Ambient Light Sensing Notebook](https://ams.com/documents/20143/36005/AmbientLightSensors_AN000172_2-00.pdf)).


## CIE photopic luminosity function

![photopic luminosity function](https://upload.wikimedia.org/wikipedia/commons/thumb/7/72/CIE_1931_Luminosity.png/450px-CIE_1931_Luminosity.png)


## Chips

- [AMS TSL2591 light-to-digital converter](../chips/tsl2591.md): very sensitive
- [BH1750](../chips/bh1750.md): easy to use
