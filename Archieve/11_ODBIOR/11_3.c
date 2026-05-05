#include "keyboard.h"
#include "servo.h"
#include "uart.h"
#include "command_decoder.h"

#define RECIEVER_SIZE 12

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
			DecodeMsg(cRecievedString);

			if((0 < ucTokenNr) && (KEYWORD == asToken[0].eType)) {

				switch (asToken[0].uValue.eKeyword) {
					case CLB:
						ServoCallib();
						break;
					
					case GT:
						ServoGoTo(asToken[1].uValue.uiNumber);
						break;
				}
			}
		}
	}
}
