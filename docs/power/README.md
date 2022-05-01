# Power supply

## Powerbanks

You can get powerbanks everywhere and with every possible
capacity. However, the powerbank transforms the 3.7V LiPo voltage up
to 5V, and the Teensy transforms it back to 3.3V. This double
conversion is a waste of energy. You can run a Teensy about 30% longer
when driving it directly with the 3.7V output from a LiPo battery.

Furthermore, there can be a problem when you run the Teensy in low
power modes. The current it draws from the power is then so low, that
it might shut off.

There is a number of nice chargers that make using LiPo batteries on
the Teensy very easy.


## LiPo charger

- [Adafruit LiIon/LiPoly Backpack](https://www.adafruit.com/product/2124): 100mA or 500mA charge current.

  [Tutorial](https://learn.adafruit.com/adafruit-pro-trinket-lipoly-slash-liion-backpack/overview)

  The backpack connects a LiPo to the Teensy. When USB is plugged in,
  the LiPo gets charged while the Teensy is running. If unplugged the
  Teensy is run from the LiPo.

  Separate VIN from VUSB on the Teensy and then connect the backpack
  to the Teensy as described in
  [liveelectronics](http://liveelectronics.musinou.net/BackpackWithTeensy.php)
  with details on the cutting on the [PJRC
  Forum](https://forum.pjrc.com/threads/19228-confused-again-Cutting-VIN-from-VUSB-Teensy-3-0?p=44024#post44024).

  - Teensy VUSB to 5V on backpack
  - Teensy Vin to BAT on backpack
  - Teensy GND to G on backpack

  ![pinout](https://cdn-learn.adafruit.com/assets/assets/000/019/688/large1024/adafruit_products_top.jpg?1410887557)

  Operation:
  - red LED: power plugged in, battery is charging.
  - green LED: power plugged in, battery is fully charged.
  - no LED: Teensy runs from battery, no power plugged in.

- [Tindie STBC08 High-Current LiPo Battery Charger](https://www.tindie.com/products/onehorse/stbc08-high-current-lipo-battery-charger/): This one is made directly for Teensy and offers up to 800mA charge current.


## Solar power charger

- [Adafruit USB / DC / Solar Lithium Ion/Polymer charger - v2](https://www.adafruit.com/product/390)

  [Tutorial](https://learn.adafruit.com/usb-dc-and-solar-lipoly-charger/using-the-charger?view=all)

- [Tindie BQ25504 Solar Cell LiPo Charger](https://www.tindie.com/products/onehorse/bq25504-solar-cell-lipo-charger/)


## Soft power switch

- [Pololu](https://www.pololu.com/product/2808)
- [Hackaday](https://hackaday.io/project/27886-soft-power-button-with-sense-output)