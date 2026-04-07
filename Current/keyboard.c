#include <LPC21xx.H>
#include "keyboard.h"

#define BTN0_bm (1 << 4)
#define BTN1_bm (1 << 6)
#define BTN2_bm (1 << 5)
#define BTN3_bm (1 << 7)

enum KeyboardState eKeyboardRead(void) {
	
	if (0 == (IO0PIN & BTN0_bm)) {
		return BUTTON_0;
	} else if (0 == (IO0PIN & BTN1_bm)) {
		return BUTTON_1;
	} else if (0 == (IO0PIN & BTN2_bm)) {
		return BUTTON_2;
	} else if (0 == (IO0PIN & BTN3_bm)) {
		return BUTTON_3;
	}

	return RELEASED;
}

void KeyboardInit(void) {
	
	IO0DIR &= ~(BTN0_bm | BTN1_bm | BTN2_bm | BTN3_bm); 
}
