#include <LPC21xx.H>

#define LED0_bm (1 << 16)
#define LED1_bm (1 << 17)
#define LED2_bm (1 << 18)
#define LED3_bm (1 << 19)

#define BTN1_bm (1 << 4)
#define BTN2_bm (1 << 6)
#define BTN3_bm (1 << 5)
#define BTN4_bm (1 << 7)

unsigned int auiLeds[] = {LED0_bm, LED1_bm, LED2_bm, LED3_bm};
enum ButtonState {RELEASED, PRESSED};

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
	IO1SET = auiLeds[ucLedIndeks];
}

enum ButtonState ReadButton1(void) {

	unsigned char ucBtn1State = IO0PIN & BTN1_bm;
	
	if (0 == ucBtn1State) {
		return PRESSED;
	}

	return RELEASED;
}

void KeyboardInit(void) {
	
	IO0DIR &= ~(BTN1_bm | BTN2_bm | BTN3_bm | BTN4_bm); 
}

int main() {
	
	LedInit();
	KeyboardInit();

	while(1) {
		switch (ReadButton1()) {
			case PRESSED:
				LedOn(1);
				break;
		
			default:
				LedOn(0);
				break;
		}
	}

	return 0;
}
