/*
 * File name: lsm303dlh.c
 * Date:      2022/01/07
 * Author:    Tomas Dudacek
 * 
 * License:   MIT License
 * Copyright (c) 2022 Tomas Dudacek
 */

#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "lsm303dlh.h"

// function --------------------------------------------------------------
void lsm303dlh_acc_setup() {
   uint8_t buffer[2] = {CTRL_REG_4, 0x00};
   
   i2c_write_blocking(
      i2c_default,
      INTERFACE_A,
      buffer,
      2,
      true
   );

   buffer[0] = CTRL_REG_1;
   buffer[1] = 0x27;
   
   i2c_write_blocking(
      i2c_default,
      INTERFACE_A,
      buffer,
      2,
      false
   );

}

// function --------------------------------------------------------------
void lsm303dlh_mag_setup() {
   uint8_t buffer[2] = {MAG_CRA, 0x10}; // 15 Hz refreshrate
   
   i2c_write_blocking(
      i2c_default,
      INTERFACE_B,
      buffer,
      2,
      true
   );

   buffer[0] = MAG_CRB;
   buffer[1] = 0xE0; // Gain - range +-8.1 Gauss, Gain X/Y and Z [LSB/Gauss] 230, GainZ [LSB/Gauss] 205
   
   i2c_write_blocking(
      i2c_default,
      INTERFACE_B,
      buffer,
      2,
      true
   );

   buffer[0] = MAG_MR;
   buffer[1] = 0x00; // Continuous-conversion mode
   
   i2c_write_blocking(
      i2c_default,
      INTERFACE_B,
      buffer,
      2,
      false
   );

}

// function --------------------------------------------------------------
void lsm303dlh_read_acc(accel_t *acc) {
   uint8_t buffer[6];
   int16_t accel[3];
   uint8_t reg = ACC_REG;

   i2c_write_blocking(
      i2c_default,
      INTERFACE_A,
      &reg,
      1,
      true
   );

   i2c_read_blocking(
      i2c_default,
      INTERFACE_A,
      buffer,
      6,
      false
   );

   // merge uint8_t to int16_t
   for (int i = 0; i < 3; i++) {
      accel[i] = ((buffer[i * 2] | buffer[(i * 2) + 1]  << 8));
   }

   acc->x = accel[0];
   acc->y = accel[1];
   acc->z = accel[2];
}

// function --------------------------------------------------------------
void lsm303dlh_read_mag(mag_t *mag) {
   uint8_t buffer[6];
   int16_t magnet[3];
   uint8_t reg = MAG_REG;

   i2c_write_blocking(
      i2c_default,
      INTERFACE_B,
      &reg,
      1,
      true
   );

   i2c_read_blocking(
      i2c_default,
      INTERFACE_B,
      buffer,
      6,
      false
   );

   // merge uint8_t to int16_t
   for (int i = 0; i < 3; i++) {
      magnet[i] = ((buffer[i * 2] << 8 | buffer[(i * 2) + 1] ));
   }

   mag->x = magnet[0];
   mag->y = magnet[1];
   mag->z = magnet[2];
}

// function --------------------------------------------------------------
int32_t get_angle(mag_t *mag) {
   int32_t angle = 0; // ((atan2(mag->x, mag->y) * 180)/PI)+180;
   //TODO
   return angle;
}

/* end of lsm303dlh.c */
