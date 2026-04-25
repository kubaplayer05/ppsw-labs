#include "keyboard.h"
#include "servo.h"
#include "uart.h"

int main () {
    
	unsigned int iMainLoopCtr;
	
	KeyboardInit();
	ServoInit(50);
	UART_InitWithInt(9600);

	while(1) {
	 	iMainLoopCtr++;

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

		switch (cOdebranyZnak) {
			case 'c':
				ServoCallib();
				break;
			case '1':
				ServoGoTo(12);
				break;
			case '2':
				ServoGoTo(24);
				break;
			case '3':
				ServoGoTo(36);
				break;
		}
	}
}
