/*
 * File name: main.c
 * Date:      2022/06/30
 * Author:    Tomas Dudacek
 * 
 * License:   MIT License
 * Copyright (c) 2022 Tomas Dudacek
*/

/*
   Connections on Raspberry Pi Pico board - 

   GPIO PICO_DEFAULT_I2C_SDA_PIN (On Pico this is GP4 (e.g. pin 6)) -> SDA 
   GPIO PICO_DEFAULT_I2C_SCL_PIN (On Pico this is GP5 (e.g. pin 7)) -> SCL 
   3.3v (e.g. pin 36) -> VCC 
   GND (e.g. pin 38)  -> GND 

   Note: After you've wired your LSM303DLH breakout board run the example 
   i2c bus scan to get the two I2C interface adressess
   (The IC has two interfaces - one for the accelerometr and second for 
   the magnetometr) and update the inteface adresses in lsm303dlh.h
   Or alternatively you can run my altered version of the scan (TODO)
   to display the result via USB and use a terminal tool such as gtkterm or putty.

*/


#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"
#include "lsm303dlh.h"

#define I2C_BAUD 400 // 400 or 100 (kHz)
#define REFRESH_PERIOD 100 // ms

// functional declaration
void init_i2c_default();

// main ------------------------------------------------------------------
int main() {
   // check for default GPIO setup
   
   #if !defined(i2c_default) || !defined(PICO_DEFAULT_I2C_SDA_PIN) || !defined(PICO_DEFAULT_I2C_SCL_PIN)
      #warning Default I2C pins were not defined
      puts("Default I2C pins were not defined");
   #else
   
   // default i2c, output setup
   init_i2c_default();
   stdio_init_all();

   // device setup (wakeup)
   lsm303dlh_acc_setup();
   lsm303dlh_mag_setup();

   accel_t acc;
   mag_t mag;

   // read
   while (true) {
      lsm303dlh_read_acc(&acc);
      lsm303dlh_read_mag(&mag);
      //int32_t angle = get_angle(&mag); // TODO Work in progress
      printf("Acc. X = %5d Y = %5d, Z = %5d \t Mag. X = %4d Y = %4d, Z = %4d \r",
               acc.x,acc.y,acc.z,mag.x,mag.y,mag.z);
      sleep_ms(REFRESH_PERIOD);
   }

   #endif
   return 0;
}

// function --------------------------------------------------------------
void init_i2c_default() {
   i2c_init(i2c_default, I2C_BAUD * 1000);
   gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
   gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
   gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
   gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
}

/* end of main.c */
