#include "keyboard.h"
#include "servo.h"
#include "uart.h"

#define TERMINATOR '\0'

int main () {
	
	KeyboardInit();
	ServoInit(50);
	UART_InitWithInt(9600);

	while(1) {
	 	Reciever_PutCharacterToBuffer ('k');
		Reciever_PutCharacterToBuffer ('o');
		Reciever_PutCharacterToBuffer ('d');
		Reciever_PutCharacterToBuffer (TERMINATOR);
	}
}
