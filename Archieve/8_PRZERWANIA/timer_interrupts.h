#ifndef TIMER_INTERRUPTS
#define TIMER_INTERRUPTS

void Timer0Interrupts_Init(unsigned int uiPeriod, void (*ptrInterruptFunction)(void));

#endif
