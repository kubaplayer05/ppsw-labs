#include <LPC21xx.H>
#include "led.h"

#define LED0_bm (1 << 16)
#define LED1_bm (1 << 17)
#define LED2_bm (1 << 18)
#define LED3_bm (1 << 19)

unsigned int auiLeds[] = {LED0_bm, LED1_bm, LED2_bm, LED3_bm};
enum Step {Left, Right};

void LedInit(void) {

	IO1DIR |= LED0_bm | LED1_bm | LED2_bm | LED3_bm;
	IO1SET = LED0_bm;
}

void LedOn(unsigned char ucLedIndeks) {

	IO1CLR = LED0_bm | LED1_bm | LED2_bm | LED3_bm;

	if (ucLedIndeks < 4) {
		IO1SET = auiLeds[ucLedIndeks];
	}
}

void LedStep(enum Step eStep) {

	static unsigned int uiLedIndeks = 0;

	if (Left == eStep) {
		uiLedIndeks = (uiLedIndeks + 1) % 4;
	}

	if (Right == eStep) {
		uiLedIndeks = (uiLedIndeks + 3) % 4;
	}

	LedOn(uiLedIndeks);
}

void LedStepLeft(void) {
	LedStep(Left);
}

void LedStepRight(void) {
	LedStep(Right);
}
