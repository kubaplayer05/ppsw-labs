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

void LedInit(void) {

	IO1DIR = LED0_bm | LED1_bm | LED2_bm | LED3_bm;
	IO1SET = LED0_bm;
}

int main() {
	
	unsigned int auiLeds[] = {LED0_bm, LED1_bm, LED2_bm, LED3_bm};
	unsigned char ucLedCounter = 0;
	
	LedInit();

	while(1) {
		
		Delay(250);
		IO1CLR = auiLeds[ucLedCounter];
		
		ucLedCounter = (ucLedCounter + 1) % 4;

		IO1SET = auiLeds[ucLedCounter];		
	}

	return 0;
}
