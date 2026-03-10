#include <LPC21xx.H>

void Delay() {
	
	unsigned int uiDelayCounter;
	
	for(uiDelayCounter = 0; uiDelayCounter < 7500750; uiDelayCounter++) {};  
}

int main() {
	
	IO1DIR = 0x00010000;
	
	while(1) {
			IO1SET = 0x00010000;
			Delay();
			IO1CLR = 0x00010000;
	}
	
	return 0;
}
