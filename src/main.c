/*
File: Lab_6_JHB.c
Author: Josh Brake
Email: jbrake@hmc.edu
Date: 9/14/19
*/


#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "main.h"

/////////////////////////////////////////////////////////////////
// Provided Constants and Functions
/////////////////////////////////////////////////////////////////

#define CLKPOL 0
#define CLKPHASE 1

//Defining the web page in two chunks: everything before the current time, and everything after the current time
char* webpageStart = "<!DOCTYPE html><html><head><title>E155 Web Server Demo Webpage</title>\
	<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\
	</head>\
	<body><h1>E155 Web Server Demo Webpage</h1>";
char* ledStr = "<p>LED Control:</p>\
                  <form action=\"ledon\">\
                  <input type=\"submit\" value=\"Turn the LED on!\">\
                  </form>\
                  <form action=\"ledoff\">\
                  <input type=\"submit\" value=\"Turn the LED off!\">\
                  </form>";
char* resolutionButton = "<p>Resolution Control:</p>\
                            <form action=\"setRes\">\
                              <label for="resolution">Choose a resolution:</label>\
                              <select name="resolution" id="resolution">\
                                  <option value="8">1</option>\
                                  <option value="9">0.5</option>\
                                  <option value="10">0.25</option>\
                                  <option value="11">0.125</option>\
                                  <option value="12">0.0625</option>\
                              </select>\
                              <br><br>\
                              <input type="submit" value="Submit">\
                            </form>";
char* webpageEnd   = "</body></html>";

//determines whether a given character sequence is in a char array request, returning 1 if present, -1 if not present
int inString(char request[], char des[]) {
	if (strstr(request, des) != NULL) {return 1;}
	return -1;
}

int updateLEDStatus(char request[])
{
	int led_status = 0;
	// The request has been received. now process to determine whether to turn the LED on or off
	if (inString(request, "ledoff")==1) {
		digitalWrite(LED_PIN, PIO_LOW);
		led_status = 0;
	}
	else if (inString(request, "ledon")==1) {
		digitalWrite(LED_PIN, PIO_HIGH);
		led_status = 1;
	}

	return led_status;
}

void updateResolution(char request[])
{
	// The request has been received. now process to determine what resolution value is being input
	if (inString(request, "setRes")==1) {
                // TODO: How do I get the resolution value out now?
		// setResolution(resolution);
	}
}


/////////////////////////////////////////////////////////////////
// Solution Functions
/////////////////////////////////////////////////////////////////

int main(void) {
  configureFlash();
  configureClock();

  gpioEnable(GPIO_PORT_A);
  gpioEnable(GPIO_PORT_B);
  gpioEnable(GPIO_PORT_C);

  pinMode(PB3, GPIO_OUTPUT);
  
  RCC->APB2ENR |= (RCC_APB2ENR_TIM15EN);
  initTIM(TIM15);
  
  USART_TypeDef * USART = initUSART(USART1_ID, 125000);

  initSPI(7, CLKPOL, CLKPHASE);
  initDS1772();

  while(1) {
    /* Wait for ESP8266 to send a request.
    Requests take the form of '/REQ:<tag>\n', with TAG begin <= 10 characters.
    Therefore the request[] array must be able to contain 18 characters.
    */

    // Receive web request from the ESP
    char request[BUFF_LEN] = "                  "; // initialize to known value
    int charIndex = 0;
  
    // Keep going until you get end of line character
    while(inString(request, "\n") == -1) {
      // Wait for a complete request to be transmitted before processing
      while(!(USART->ISR & USART_ISR_RXNE));
      request[charIndex++] = readChar(USART);
    }

    // TODO: Add SPI code here for reading temperature
    int temperature = spiSendReceive(0b00000000);
    // TODO: convert in to char array
    char* tempArr = ;

    // Update string with current LED state
  
    int led_status = updateLEDStatus(request);

    char ledStatusStr[20];
    if (led_status == 1)
      sprintf(ledStatusStr,"LED is on!");
    else if (led_status == 0)
      sprintf(ledStatusStr,"LED is off!");

    // finally, transmit the webpage over UART
    sendString(USART, webpageStart); // webpage header code
    sendString(USART, tempArr); // temperature value output
    sendString(USART, ledStr); // button for controlling LED
    sendString(USART, resolutionButton); // button for resolution selection

    sendString(USART, "<h2>LED Status</h2>");


    sendString(USART, "<p>");
    sendString(USART, ledStatusStr);
    sendString(USART, "</p>");

  
    sendString(USART, webpageEnd);
  }
}
