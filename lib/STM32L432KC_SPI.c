// STM32L432KC_SPI.c
// Lindsey Sands
// lsands@g.hmc.edu
// 10/10/2026
// This is the C file for SPI interactions

/* Enables the SPI peripheral and intializes its clock speed (baud rate), polarity, and phase.
 *    -- br: (0b000 - 0b111). The SPI clk will be the master clock / 2^(BR+1).
 *    -- cpol: clock polarity (0: inactive state is logical 0, 1: inactive state is logical 1).
 *    -- cpha: clock phase (0: data captured on leading edge of clk and changed on next edge, 
 *          1: data changed on leading edge of clk and captured on next edge)
 * Refer to the datasheet for more low-level details. */ 
#include "stm32l432xx.h"

void initSPI(int br, int cpol, int cpha) {

  // Disable SPI
  //  1. Wait until FTLVL[1:0] = 00 (no more data to transmit).
  while (!((SPI1->SR >> 11) & 1) & !((SPI1->SR >> 12) & 1));
  //  2. Wait until BSY=0 (the last data frame is processed).
  while (!(SPI1->SR >> 7) & 1);
  //  3. Disable the SPI (SPE=0).
  SPI1->CR1 &= ~(1 << 6);
  //  4. Read data until FRLVL[1:0] = 00 (read all the received data).
  // TODO: How do I do this?
  while (!((SPI1->SR >> 10) & 1) & !((SPI1->SR >> 9) & 1));

  // TODO: Do I need to activate NSS?

  // Set SPI characteristics
  SPI1->CR1 &= ~(0b111 << 3);
  // TODO: case statement for br

  SPI1->CR1 &= ~(1 << 1);
  if (cpol == 1) {
    SPI1->CR1 |= (1 << 1);
  }

  SPI1->CR1 &= ~(1 << 0);
  if (cpha == 1) {
    SPI1->CR1 |= (1 << 0);
  }

  // Enable hardware CRC calculation and set CRC length
  SPI1->CR1 |= (1 << 13);
  SPI1->CR1 &= ~(1 << 11);

  // Choose 8-bit data length
  SPI1->CR2 &= ~(0b1111 << 8);
  SPI1->CR2 |= (0b0111 << 8);

  // Enable SPI
  SPI1->CR1 |= (1 << 6);

}

/* Transmits a character (1 byte) over SPI and returns the received character.
 *    -- send: the character to send over SPI
 *    -- return: the character received over SPI */
char spiSendReceive(char send) {

  // TODO: Complete this
  // Check if data is ready to be written

  // Write data

  // Check if data is ready to be received

  // Receive data
    char received = (SPI1->DR >> 0);
  return received;
}