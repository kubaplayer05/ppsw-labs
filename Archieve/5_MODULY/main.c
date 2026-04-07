#include <LPC21xx.H>
#include "led.h"
#include "keyboard.h"

void Delay(unsigned int uiMiliseconds) {
	
	unsigned int uiDelayCounter;
	unsigned int uiLoopIterations = 12000 * uiMiliseconds;
	
	for(uiDelayCounter = 0; uiDelayCounter < uiLoopIterations; uiDelayCounter++) {};  
}

int main() {
	
	LedInit();
	KeyboardInit();

	while(1) {
		switch (eKeyboardRead()) {
			case BUTTON_1:
				Delay(250);
				LedStepRight();
				break;
			case BUTTON_2:
				Delay(250);
				LedStepLeft();
				break;
			default:
				break;
		}
	}

	return 0;
}
