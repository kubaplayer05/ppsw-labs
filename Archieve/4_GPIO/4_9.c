#include <LPC21xx.H>

#define LED0_bm 0x00010000

void Delay(unsigned int uiMiliseconds) {
	
	unsigned int uiDelayCounter;
	unsigned int uiLoopIterations = 12000 * uiMiliseconds;
	
	for(uiDelayCounter = 0; uiDelayCounter < uiLoopIterations; uiDelayCounter++) {};  
}

int main() {
	
	IO1DIR = LED0_bm;
	
	while(1) {
			IO1SET = LED0_bm;
			Delay(50);
			IO1CLR = LED0_bm;
			Delay(50);
	}
	
	return 0;
}
