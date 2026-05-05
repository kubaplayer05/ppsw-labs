#include "uart.h"
#include "string.h"

int main () {

	char cMessage[20];
	char cMessageFirstPart[] = "licznik ";
	unsigned int uiCounter = 0;

	UART_InitWithInt(9600);

	while(1) {
		
		if(FREE == Transmiter_GetStatus()) {
			
			CopyString(cMessageFirstPart, cMessage);
			AppendUIntToString(uiCounter, cMessage);
			Transmiter_SendString(cMessage);
			uiCounter++;
		}
	}
}
