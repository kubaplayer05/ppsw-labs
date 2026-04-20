#include "led.h"
#include "keyboard.h"
#include "timer_interrupts.h"

enum LedState{LED_STOP, LED_STEP_LEFT, LED_STEP_RIGHT};

void Automat() {
	static enum LedState eLedState = LED_STOP;

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

int main (){
	unsigned int iMainLoopCtr;
	
	LedInit();
	KeyboardInit();
	Timer0Interrupts_Init(100000, &Automat);

	while(1){
	 	iMainLoopCtr++;
	}
}
