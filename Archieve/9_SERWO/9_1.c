#include <LPC21xx.H>
#include "led.h"
#include "keyboard.h"
#include "timer_interrupts.h"

#define DETECTOR_bm (1 << 10)

enum LedState{LED_STOP, LED_STEP_LEFT, LED_STEP_RIGHT, CALLIB};
enum DetectorState{ACTIVE, INACTIVE};

void DetectorInit() {

	IO0DIR &= ~DETECTOR_bm;
}

enum DetectorState eReadDetector() {

	if(0 == (IO0PIN & DETECTOR_bm)) {
		return ACTIVE;
	}

	return INACTIVE;
}

void Automat() {
	static enum LedState eLedState = CALLIB;

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
			case CALLIB:
				if(ACTIVE == eReadDetector()) {
					eLedState = LED_STOP;
				} else {
					LedStepRight();
					eLedState = CALLIB;
				}
		}
}

int main (){
	unsigned int iMainLoopCtr;
	
	LedInit();
	KeyboardInit();
	DetectorInit();
	Timer0Interrupts_Init(20000, &Automat);

	while(1){
	 	iMainLoopCtr++;
	}
}
