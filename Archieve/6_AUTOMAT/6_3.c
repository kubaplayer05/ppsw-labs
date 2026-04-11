#include "led.h"
#include "keyboard.h"

void Delay(unsigned int uiMiliseconds) {

    unsigned int uiDelayCounter;
    unsigned int uiLoopIterations = 12000 * uiMiliseconds;

    for(uiDelayCounter = 0; uiDelayCounter < uiLoopIterations; uiDelayCounter++) {};  
}

enum LedState{LED_STEP_LEFT, LED_STEP_RIGHT};
enum LedState eLedState = LED_STEP_LEFT;

int main() {

    unsigned char ucStepCount = 0;

    LedInit();
    KeyboardInit();

    while(1) {

        Delay(250);
        switch (eLedState) {
            case LED_STEP_LEFT: 
                LedStepLeft();
                ucStepCount = ucStepCount + 1;

                if (3 == ucStepCount) {
                    eLedState = LED_STEP_RIGHT;
                    ucStepCount = 0;
                }

                break;

            case LED_STEP_RIGHT:
                LedStepRight();
                ucStepCount = ucStepCount + 1;

                if (3 == ucStepCount) {
                    eLedState = LED_STEP_LEFT;
                    ucStepCount = 0;
                }

                break;
        }
    }

    return 0;
}
