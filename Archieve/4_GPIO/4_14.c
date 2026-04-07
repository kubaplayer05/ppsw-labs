#include <LPC21xx.H>

#define LED0_bm (1 << 16)
#define LED1_bm (1 << 17)
#define LED2_bm (1 << 18)
#define LED3_bm (1 << 19)

unsigned int auiLeds[] = {LED0_bm, LED1_bm, LED2_bm, LED3_bm};

void Delay(unsigned int uiMiliseconds) {
	
	unsigned int uiDelayCounter;
	unsigned int uiLoopIterations = 12000 * uiMiliseconds;
	
	for(uiDelayCounter = 0; uiDelayCounter < uiLoopIterations; uiDelayCounter++) {};  
}

void LedInit(void) {

	IO1DIR = LED0_bm | LED1_bm | LED2_bm | LED3_bm;
	IO1SET = LED0_bm;
}

void LedOn(unsigned char ucLedIndeks) {

	IO1CLR = LED0_bm | LED1_bm | LED2_bm | LED3_bm;
	IO1SET = auiLeds[ucLedIndeks];
}

int main() {
	
	unsigned char ucLedIndeks = 0;
	
	LedInit();

	while(1) {
		
		Delay(250);
		ucLedIndeks = (ucLedIndeks + 1) % 4;
		LedOn(ucLedIndeks);
	}

	return 0;
}
