// DS1722.h
// Lindsey Sands
// lsands@g.hmc.edu
// 10/11/2026
// This is the header file for the DS1772 Digital Temperature Sensor

#ifndef DS1772_H
#define DS1772_H

#include  <stm32l432xx.h>
#include "STM32L432KC_GPIO.h"

// Config register
#define READ_ADDRESS_1 0x00
#define WRITE_ADDRESS 0x80

#define READ_ADDRESS_2 0x01 // LSB
#define READ_ADDRESS_3 0x02 // MSB

#define SDO_PIN PA6
#define SDI_PIN PA12
#define CE_PIN PB1
#define SCLK_PIN PA5
#define SERMODE_PIN PA8

#define RES8 8
#define RES9 9
#define RES10 10
#define RES11 11
#define RES12 12

// volatile int resolutionBits = 8;

// Sets the resolution of the temperature readings by choosing the number of bits
//    the sensor outputs (8, 9, 10, 11, or 12 bits)
void setResolution(int numBits);

// Initializes temperature sensor
void initDS1772(void);

#endif