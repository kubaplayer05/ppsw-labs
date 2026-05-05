#include "uart.h"

int main () {

	UART_InitWithInt(9600);

	while(1) {
		
		if(FREE == Transmiter_GetStatus()) {
			Transmiter_SendString("test123");
		}
	}
}
