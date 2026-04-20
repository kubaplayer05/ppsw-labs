#include <LPC21xx.H>
#include "timer_interrupts.h"

#define COUNTER_ENABLE_bm (1 << 0)
#define COUNTER_RESET_bm (1 << 1)
#define MATCH_RESET_bm (1 << 1)
#define MATCH_INTERRUPT_bm (1 << 0)

#define VIC_TIMER0_CHANNEL_NR 4
#define mIRQ_SLOT_ENABLE 0x00000020

void (*ptrTimer0InterruptFunction)(void);

__irq void Timer0IRQHandler() {

	T0IR = MATCH_INTERRUPT_bm; 
	ptrTimer0InterruptFunction();		
	VICVectAddr = 0x00; 
}

void Timer0Interrupts_Init(unsigned int uiPeriod, void (*ptrInterruptFunction)(void)) { 

	ptrTimer0InterruptFunction = ptrInterruptFunction;
	VICIntEnable |= (0x1 << VIC_TIMER0_CHANNEL_NR);            
	VICVectCntl0  = mIRQ_SLOT_ENABLE | VIC_TIMER0_CHANNEL_NR; 
	VICVectAddr0  = (unsigned long)Timer0IRQHandler; 	  

	T0MR0 = 15 * uiPeriod;                 	      
	T0MCR |= (MATCH_INTERRUPT_bm | MATCH_RESET_bm); 
	T0TCR |=  COUNTER_ENABLE_bm;

}
