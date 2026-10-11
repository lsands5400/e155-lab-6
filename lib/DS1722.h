// DS1722.h
// Lindsey Sands
// lsands@g.hmc.edu
// 10/11/2026
// This is the header file for the DS1772 Digital Temperature Sensor

#ifndef DS1772_H
#define DS1772_H

#include "STM32L432KC_GPIO.h"

// Config register
#define READ_ADDRESS_1 0x00
#define WRITE_ADDRESS 0x80

#define READ_ADDRESS_2 0x01 // LSB
#define READ_ADDRESS_3 0x02 // MSB

//TODO: Choose the actual pins for this
#define SDO_PIN 6
#define SDI_PIN 7
#define CE_PIN 8
#define SCLK_PIN 9
#define SERMODE_PIN 10

#define RES8 8
#define RES9 9
#define RES10 10
#define RES11 11
#define RES12 12


// Sets the resolution of the temperature readings by choosing the number of bits
//    the sensor outputs (8, 9, 10, 11, or 12 bits)
void setResolution(int numBits);

// Initializes temperature sensor
void initDS1772(void);

#endif