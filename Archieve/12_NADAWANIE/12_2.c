#include "uart.h"

int main () {

	UART_InitWithInt(9600);
	Transmiter_SendString("test123");

	while(1) {

	}
}
