#include "uart.h"

int main () {
	
	unsigned int iMainLoopCtr;

	UART_InitWithInt(38400);

	while(1) {
	 	iMainLoopCtr++;
	}
}
