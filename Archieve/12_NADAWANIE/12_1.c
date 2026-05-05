#include <LPC21xx.H>
#include "uart.h"

 /* umiescic w uart
 
      static unsigned char ucCharCounter = 1;

      U0THR = ucCharCounter;
      ucCharCounter++;
*/

int main () {

	UART_InitWithInt(9600);
	U0THR = 0;

	while(1) {

	}
}
