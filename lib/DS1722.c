// DS1722.c
// Lindsey Sands
// lsands@g.hmc.edu
// 10/11/2026
// This is the c file for the DS1772 Digital Temperature Sensor

#include "DS1722.h"

void setResolution(int numBits) {
  // Send address to write to
  digitalWrite(CE_PIN, PIO_HIGH);
  spiSendReceive(WRITE_ADDRESS);
  // Send resolution 
  switch (numBits) {
    case RES8:
      spiSendReceive(0b11100000);
      break;
    case RES9:
      spiSendReceive(0b11100010);
      break;
    case RES10:
      spiSendReceive(0b11100100);
      break;
    case RES11:
      spiSendReceive(0b11100110);
      break;
    case RES12:
      spiSendReceive(0b11101000);
      break;
  }
  digitalWrite(CE_PIN, PIO_LOW);
  delay_millis(TIM15, 10);
}

void initDS1772(void) {

  // Set pins
  pinMode(SDO_PIN, GPIO_ALT);
  pinMode(SDI_PIN, GPIO_ALT);
  pinMode(CE_PIN, GPIO_OUTPUT);
  pinMode(SERMODE_PIN, GPIO_INPUT);
  pinMode(SCLK_PIN, GPIO_ALT);

  // Set alternate functions

  // SCK on PA5
  GPIOA->AFR[0] &= ~(0b1111 << 20);
  GPIOA->AFR[0] |= (0b0101 << 20);

  // MISO on PA6
  GPIOA->AFR[0] &= ~(0b1111 << 24);
  GPIOA->AFR[0] |= (0b0101 << 24);

  // MOSI on PA12
  GPIOA->AFR[1] &= ~(0b1111 << 16);
  GPIOA->AFR[1] |= (0b0101 << 16);

}