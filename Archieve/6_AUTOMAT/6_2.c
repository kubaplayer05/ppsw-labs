#include "led.h"
#include "keyboard.h"

void Delay(unsigned int uiMiliseconds) {
	
	unsigned int uiDelayCounter;
	unsigned int uiLoopIterations = 12000 * uiMiliseconds;
	
	for(uiDelayCounter = 0; uiDelayCounter < uiLoopIterations; uiDelayCounter++) {};  
}

enum LedState{LED_LEFT_1, LED_LEFT_2, LED_LEFT_3, LED_RIGHT_1, LED_RIGHT_2, LED_RIGHT_3};
enum LedState eLedState = LED_LEFT_1;

int main() {
	
	LedInit();
	KeyboardInit();

	while(1) {
		Delay(250);
		switch (eLedState) {
			case LED_LEFT_1:
				LedStepLeft();
				eLedState = LED_LEFT_2;
				break;
			case LED_LEFT_2:
				LedStepLeft();
				eLedState = LED_LEFT_3;
				break;
			case LED_LEFT_3:
				LedStepLeft();
				eLedState = LED_RIGHT_1;
				break;
			case LED_RIGHT_1:
				LedStepRight();
				eLedState = LED_RIGHT_2;
				break;
			case LED_RIGHT_2:
				LedStepRight();
				eLedState = LED_RIGHT_3;
				break;
			case LED_RIGHT_3:
				LedStepRight();
				eLedState = LED_LEFT_1;
				break;
		}
	}

	return 0;
}
