// DS1722.c
// Lindsey Sands
// lsands@g.hmc.edu
// 10/11/2026
// This is the c file for the DS1772 Digital Temperature Sensor

#include "DS1722.h"

void setResolution(int numBits) {
  // Send address to write to
  digitalWrite(SDI_PIN, WRITE_ADDRESS);
  // Send resolution 
  switch (numBits) {
    case RES8:
      digitalWrite(SDI_PIN, 0b000); // TODO: Fix this
      break;
    case RES9:
      digitalWrite(SDI_PIN, 0b001);
      break;
    case RES10:
      digitalWrite(SDI_PIN, 0b010);
      break;
    case RES11:
      digitalWrite(SDI_PIN, 0b011);
      break;
    case RES12:
      digitalWrite(SDI_PIN, 0b100);
      break;
  }
}

void initDS1772(void) {

  // Set pins
  pinMode(SDO_PIN, GPIO_OUTPUT);
  pinMode(SDI_PIN, GPIO_INPUT);
  pinMode(SCLK_PIN, GPIO_ALT);
  pinMode(CE_PIN, GPIO_INPUT);
  pinMode(SERMODE_PIN, GPIO_INPUT);

  // Set CE to enable SCLK
  digitalWrite(CE_PIN, PIO_HIGH);

}