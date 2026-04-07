#include <LPC21xx.H>

#define LED0_bm (1 << 16)
#define LED1_bm (1 << 17)
#define LED2_bm (1 << 18)
#define LED3_bm (1 << 19)

#define BTN1_bm (1 << 4)

unsigned int auiLeds[] = {LED0_bm, LED1_bm, LED2_bm, LED3_bm};

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

unsigned char ReadButton1(void) {

	unsigned char ucBtn1State = IO0PIN & BTN1_bm;
	
	if (0 == ucBtn1State) {
		return 1;
	}

	return 0;
}

int main() {
	
	LedInit();

	while(1) {
		if (1 == ReadButton1()) {
			LedOn(1);
		} else {
			LedOn(0);
		}
	}

	return 0;
}
