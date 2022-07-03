# LSM303DLH_pico
LSM303DLH example in C for Raspberry Pi pico

## Connections on Raspberry Pi Pico board - 

GPIO PICO_DEFAULT_I2C_SDA_PIN (On Pico this is GP4 (e.g. pin 6)) -> SDA <br />
GPIO PICO_DEFAULT_I2C_SCL_PIN (On Pico this is GP5 (e.g. pin 7)) -> SCL <br />
3.3v (e.g. pin 36) -> VCC <br />
GND (e.g. pin 38)  -> GND <br />

## Getting started -

After you've wired your LSM303DLH breakout board run the example 
I2C bus scan to get the two I2C interface adressess
(The IC has two interfaces - one for the accelerometr and second for 
the magnetometr, but you can address both tools from the same interface)
and update the inteface adresses in lsm303dlh.h

Or alternatively you can run [my altered version of the scan](https://github.com/Dudycodes/i2c_bus_scan_usb_pico)
to display the result via USB and use a terminal tool such as [GTKTerm](https://sourceforge.net/projects/gtkterm/) or [PuTTY](https://www.putty.org/).

## Building - 

As stated in [Getting started with Raspberry Pi pico](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf#%5B%7B%22num%22%3A33%2C%22gen%22%3A0%7D%2C%7B%22name%22%3A%22XYZ%22%7D%2C115%2C841.89%2Cnull%5D)
chapter 8 - 

```
$ mkdir build
$ cd build
$ export PICO_SDK_PATH=../../pico-sdk
$ cmake ..
$ make
```
some previous steps are necessary - please refer to [chapter 2](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf#%5B%7B%22num%22%3A9%2C%22gen%22%3A0%7D%2C%7B%22name%22%3A%22XYZ%22%7D%2C115%2C841.89%2Cnull%5D)
of the material stated higher.

## License
Code is published under the MIT License <br />
Copyright (c) 2022 Tomas Dudacek

