#include "timer_interrupts.h"
#include "uart.h"
#include "string.h"

struct Watch { 
	unsigned char ucMinutes, ucSecconds; 
	unsigned char fSeccondsValueChanged, fMinutesValueChanged;
};
 
struct Watch sWatch;

void WatchUpdate() {

	sWatch.ucSecconds = sWatch.ucSecconds + 1;
	sWatch.fSeccondsValueChanged = 1;

	if(60 == sWatch.ucSecconds) {
		sWatch.ucSecconds = 0;
		sWatch.ucMinutes = sWatch.ucMinutes + 1;
		sWatch.fMinutesValueChanged = 1;
	} 
}

int main () {

	char cMessage[11];

	UART_InitWithInt(9600);
	Timer0Interrupts_Init(1000000, &WatchUpdate);

	while(1) {
		if(FREE == Transmiter_GetStatus()) {
			
			if(1 == sWatch.fSeccondsValueChanged) {
				CopyString("sec ", cMessage);
				AppendUIntToString(sWatch.ucSecconds, cMessage);
				Transmiter_SendString(cMessage);
				sWatch.fSeccondsValueChanged = 0;
			} else if(1 == sWatch.fMinutesValueChanged) {
				CopyString("min ", cMessage);
				AppendUIntToString(sWatch.ucMinutes, cMessage);
				Transmiter_SendString(cMessage);
				sWatch.fMinutesValueChanged = 0;
			}
		}		
	}
}
