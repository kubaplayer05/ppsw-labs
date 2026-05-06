#include "timer_interrupts.h"
#include "servo.h"
#include "adc.h"

int main () {
	
	unsigned int uiAdcValue;

	ServoInit(200);
	ADC_Init();
	
	while(1) {
			
			uiAdcValue = ADC_Read();
			uiAdcValue = (uiAdcValue * 48) / 1023;
			ServoGoTo(uiAdcValue);
	}
}
// git test