#include <LPC21xx.H>
#include "timer.h"

#define COUNTER_ENABLE_bm (1 << 0)
#define COUNTER_RESET_bm (1 << 1)
#define MATCH_RESET_bm (1 << 1)
#define MATCH_INTERRUPT_bm (1 << 0)
#define PCLK_FREQ_MHZ 15

void InitTimer0(void) {

    T0TCR |= COUNTER_ENABLE_bm;
}

void WaitOnTimer0(unsigned int uiTime) {

	unsigned int uiClockCycles = uiTime * PCLK_FREQ_MHZ;

    T0TCR |= COUNTER_RESET_bm;
    T0TCR &= ~COUNTER_RESET_bm;

    while (uiClockCycles > T0TC) {};
}

void InitTimer0Match0(unsigned int uiDelayTime) {

    T0MR0 = uiDelayTime * PCLK_FREQ_MHZ;
    T0MCR |= MATCH_RESET_bm | MATCH_INTERRUPT_bm;
    T0TCR |= COUNTER_RESET_bm;
    T0TCR &= ~COUNTER_RESET_bm;
    T0TCR |= COUNTER_ENABLE_bm;
}


void WaitOnTimer0Match0() {

    while(0 == (T0IR & MATCH_INTERRUPT_bm)) {};
    T0IR = MATCH_INTERRUPT_bm;
}
