#include "led.h"
#include "keyboard.h"

void Delay(unsigned int uiMiliseconds) {
	
	unsigned int uiDelayCounter;
	unsigned int uiLoopIterations = 12000 * uiMiliseconds;
	
	for(uiDelayCounter = 0; uiDelayCounter < uiLoopIterations; uiDelayCounter++) {};  
}

enum LedState{LED_STOP, LED_STEP_LEFT, LED_STEP_RIGHT};
enum LedState eLedState = LED_STOP;

int main() {

	LedInit();
	KeyboardInit();

	while(1) {
		Delay(100);
		switch (eLedState) {
			case LED_STOP:
				if (BUTTON_0 == eKeyboardRead()) {
					eLedState = LED_STEP_LEFT;
				} else if (BUTTON_2 == eKeyboardRead()) {
					eLedState = LED_STEP_RIGHT;
				} else {
					eLedState = LED_STOP;
				}

				break;
			case LED_STEP_LEFT:
				if (BUTTON_1 == eKeyboardRead()) {
					eLedState = LED_STOP;
				} else {
					LedStepLeft();
					eLedState = LED_STEP_LEFT;
				}

				break;
			case LED_STEP_RIGHT:
				if (BUTTON_1 == eKeyboardRead()) {
					eLedState = LED_STOP;
				} else {
					LedStepRight();
					eLedState = LED_STEP_RIGHT;
				}
				
				break;
		}
	}

	return 0;
}
