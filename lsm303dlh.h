/*
 * File name: lsm303dlh.h
 * Date:      2022/06/30
 * Author:    Tomas Dudacek
 * 
 * License:   MIT License
 * Copyright (c) 2022 Tomas Dudacek
 */

#ifndef __LSM303DLH__
#define __LSM303DLH__

#include <stdint.h>

// TODO update after scan - see READ ME / main.c
#define INTERFACE_A 0x18 // Accelerometr slave address
#define INTERFACE_B 0x1E // Magnetometr slave address
// end of TODO

#define CTRL_REG_1 0x20
#define CTRL_REG_4 0x23
#define ACC_REG 0xA8 // data starts on 0x28 - MSb set to 1 (autoincrease on read) -> 0xA8
#define MAG_REG 0x03 // data starts on 0x03 - MSb set to 1 (autoincrease on read) -> 0xA8
#define MAG_CRA 0x00
#define MAG_CRB 0x01
#define MAG_MR 0x02
#define PI 3.141592653


typedef struct {
   int16_t x;
   int16_t y;
   int16_t z;
} accel_t;

typedef struct { // TODO
   int16_t x;
   int16_t y;
   int16_t z;
} mag_t;

/*
 * Wake up and set the device (see IC documentation for more info)
 * (Documentation: https://cz.mouser.com/datasheet/2/389/stmicroelectronics_cd00260288-1206307.pdf)
 */
void lsm303dlh_acc_setup();

/*
 * Wake up and set the device (see IC documentation for more info)
 * (Documentation: https://cz.mouser.com/datasheet/2/389/stmicroelectronics_cd00260288-1206307.pdf)
 */
void lsm303dlh_mag_setup();

/*
 * Performs a sequention of i2c communication with INTERFACE_A address 
 * and writes in given pointer to acc_t struct
 */
void lsm303dlh_read_acc(accel_t *acc);

/*
 * Performs a sequention of i2c communication with INTERFACE_A address 
 * and writes in given pointer to mag_t struct
 */
void lsm303dlh_read_mag(mag_t *mag);

/*
 * WORK IN PROGRESS - WILL RETURN a heading angle of the IC
 * currently returns 0
 */
int32_t get_angle(mag_t *mag);

#endif
/* end of lsm303dlh.h */
