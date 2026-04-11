#include "led.h"
#include "keyboard.h"

void Delay(unsigned int uiMiliseconds) {
	
	unsigned int uiDelayCounter;
	unsigned int uiLoopIterations = 12000 * uiMiliseconds;
	
	for(uiDelayCounter = 0; uiDelayCounter < uiLoopIterations; uiDelayCounter++) {};  
}

enum LedState{LED_STOP, LED_STEP_RIGHT};
enum LedState eLedState = LED_STOP;

int main() {

	unsigned char ucStepCount = 0;
	
	LedInit();
	KeyboardInit();

	while(1) {
		Delay(100);
		switch (eLedState) {
			case LED_STOP:
				if (BUTTON_0 == eKeyboardRead()) {
					eLedState = LED_STEP_RIGHT;
				} else {
					eLedState = LED_STOP;
				}

				break;
			case LED_STEP_RIGHT:
				if (2 > ucStepCount) {
					LedStepRight();
					ucStepCount = ucStepCount + 1;
					eLedState = LED_STEP_RIGHT;
				} else {
					LedStepRight();
					ucStepCount = 0;
					eLedState = LED_STOP;
				}
				
				break;
		}
	}

	return 0;
}
