#include <LPC21xx.H>

#define LED0_bm (1 << 16)
#define LED1_bm (1 << 17)
#define LED2_bm (1 << 18)
#define LED3_bm (1 << 19)

#define BTN0_bm (1 << 4)
#define BTN1_bm (1 << 6)
#define BTN2_bm (1 << 5)
#define BTN3_bm (1 << 7)

unsigned int auiLeds[] = {LED0_bm, LED1_bm, LED2_bm, LED3_bm};
enum KeyboardState {RELEASED, BUTTON_0, BUTTON_1, BUTTON_2, BUTTON_3};
unsigned int uiLedIndeks = 0;

void Delay(unsigned int uiMiliseconds) {
	
	unsigned int uiDelayCounter;
	unsigned int uiLoopIterations = 12000 * uiMiliseconds;
	
	for(uiDelayCounter = 0; uiDelayCounter < uiLoopIterations; uiDelayCounter++) {};  
}

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

enum KeyboardState eKeyboardRead(void) {
	
	if (0 == (IO0PIN & BTN0_bm)) {
		return BUTTON_0;
	} else if (0 == (IO0PIN & BTN1_bm)) {
		return BUTTON_1;
	} else if (0 == (IO0PIN & BTN2_bm)) {
		return BUTTON_2;
	} else if (0 == (IO0PIN & BTN3_bm)) {
		return BUTTON_3;
	}

	return RELEASED;
}

void KeyboardInit(void) {
	
	IO0DIR &= ~(BTN0_bm | BTN1_bm | BTN2_bm | BTN3_bm); 
}

void StepLeft(void) {
	
    uiLedIndeks = (uiLedIndeks + 1) % 4;
    LedOn(uiLedIndeks);
}

void StepRight(void) {

	uiLedIndeks = (uiLedIndeks + 3) % 4;
	LedOn(uiLedIndeks);
}

int main() {
	
	LedInit();
	KeyboardInit();

	while(1) {
		Delay(250);
		StepRight();
	}

	return 0;
}
