#include "keyboard.h"
#include "servo.h"
#include "uart.h"
#include "lancuchy.h"

#define RECIEVER_SIZE 7

int main () {
    
	char cRecievedString[RECIEVER_SIZE];

	KeyboardInit();
	ServoInit(50);
	UART_InitWithInt(9600);

	while(1) {
		switch (eKeyboardRead()) {
			case BUTTON_0:
				ServoCallib();
				break;
			case BUTTON_1:
				ServoGoTo(12);
				break;
			case BUTTON_2:
				ServoGoTo(24);
				break;
			case BUTTON_3:
				ServoGoTo(36);
				break;
		}

		if(READY == eReciever_GetStatus()) {
			Reciever_GetStringCopy(cRecievedString);

			if(EQUAL == eCompareString(cRecievedString, "callib")) {
				ServoCallib();
			} else if(EQUAL == eCompareString(cRecievedString, "left")) {
				ServoGoTo(50);
			} else if(EQUAL == eCompareString(cRecievedString, "right")) {
				ServoGoTo(150);
			}
		}
	}
}
