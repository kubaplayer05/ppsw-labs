#include <LPC21xx.H>

#define LED0_bm (1 << 16)
#define LED3_bm (1 << 19)

void Delay(unsigned int uiMiliseconds) {
	
	unsigned int uiDelayCounter;
	unsigned int uiLoopIterations = 12000 * uiMiliseconds;
	
	for(uiDelayCounter = 0; uiDelayCounter < uiLoopIterations; uiDelayCounter++) {};  
}

int main() {
	
	IO1DIR = LED3_bm;
	
	while(1) {
			IO1SET = LED3_bm;
			Delay(50);
			IO1CLR = LED3_bm;
			Delay(50);
	}
	
	return 0;
}
