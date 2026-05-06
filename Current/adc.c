#include <LPC21xx.H>
#include "adc.h"

#define SEL_bm (1 << 0)
#define CLKDIV_bm (15 << 8)
#define PDN_bm (1 << 21)
#define START_bm (1 << 24)
#define DONE_bm (1 << 31)

void ADC_Init() {
	
	PINSEL1 |= (1 << 22);
	ADCR = SEL_bm | CLKDIV_bm | PDN_bm;
}

unsigned int ADC_Read() {
	
	unsigned int uiAdcRegisterValue;
	unsigned int uiReadValue;
	
	ADCR |= START_bm;
	uiAdcRegisterValue = ADDR;
	
	while(0 == (uiAdcRegisterValue & DONE_bm)) {
		uiAdcRegisterValue = ADDR;
	}
	
	ADCR &= ~START_bm;
	uiReadValue = (uiAdcRegisterValue >> 6) & 0x03FF;
	
	return uiReadValue;
}
