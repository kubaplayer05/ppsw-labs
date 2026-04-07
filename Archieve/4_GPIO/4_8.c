#include <LPC21xx.H>

void Delay(unsigned int uiMiliseconds) {
	
	unsigned int uiDelayCounter;
	unsigned int uiLoopIterations = 12000 * uiMiliseconds;
	
	for(uiDelayCounter = 0; uiDelayCounter < uiLoopIterations; uiDelayCounter++) {};  
}

int main() {
	
	IO1DIR = 0x00010000;
	
	while(1) {
			IO1SET = 0x00010000;
			Delay(50);
			IO1CLR = 0x00010000;
			Delay(50);
	}
	
	return 0;
}
