#include <LPC21xx.H>

#define LED0_bm (1 << 16)
#define LED1_bm (1 << 17)
#define LED2_bm (1 << 18)
#define LED3_bm (1 << 19)

void Delay(unsigned int uiMiliseconds) {
	
	unsigned int uiDelayCounter;
	unsigned int uiLoopIterations = 12000 * uiMiliseconds;
	
	for(uiDelayCounter = 0; uiDelayCounter < uiLoopIterations; uiDelayCounter++) {};  
}

int main() {
	
	unsigned int piLeds[] = {LED0_bm, LED1_bm, LED2_bm, LED3_bm};
	unsigned char ucLedCounter;

	IO1DIR = LED0_bm | LED1_bm | LED2_bm | LED3_bm;
	
	while(1) {
		for(ucLedCounter = 0; ucLedCounter < 4; ucLedCounter++) {
			IO1SET = piLeds[ucLedCounter];
			Delay(250);
			IO1CLR = piLeds[ucLedCounter];
		}
	}

	return 0;
}
