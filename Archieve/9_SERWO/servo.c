#include <LPC21xx.H>
#include "servo.h"
#include "led.h"
#include "timer_interrupts.h"

#define DETECTOR_bm (1 << 10)

enum DetectorState{ACTIVE, INACTIVE};
enum ServoState {CALLIB, IDLE, IN_PROGRESS};

struct Servo {
	enum ServoState eState; 
	unsigned int uiCurrentPosition; 
	unsigned int uiDesiredPosition;
}; 

struct Servo sServo;


void DetectorInit(void) {

	IO0DIR &= ~DETECTOR_bm;
}

enum DetectorState eReadDetector() {

	if(0 == (IO0PIN & DETECTOR_bm)) {
		return ACTIVE;
	}

	return INACTIVE;
}

void Automat() {

	switch (sServo.eState) {
			case CALLIB:
				if(ACTIVE == eReadDetector()) {
					sServo.uiCurrentPosition = 0;
					sServo.uiDesiredPosition = 0;
					sServo.eState = IDLE;
				} else {
					LedStepRight();
					sServo.eState = CALLIB;
				}

				break;
			
			case IDLE:
				if(sServo.uiCurrentPosition == sServo.uiDesiredPosition) {
					sServo.eState = IDLE;
				} else {
					sServo.eState = IN_PROGRESS;
				}

				break;

			case IN_PROGRESS:
				if(sServo.uiCurrentPosition == sServo.uiDesiredPosition) {
					sServo.eState = IDLE;
				} else {
					if(sServo.uiCurrentPosition > sServo.uiDesiredPosition) {
						LedStepRight();
						sServo.uiCurrentPosition = sServo.uiCurrentPosition - 1;
					} else {
						LedStepLeft();
						sServo.uiCurrentPosition = sServo.uiCurrentPosition + 1;
					}

					sServo.eState = IN_PROGRESS;
				}

				break;
		}
}

void ServoCallib(void) {
	
	sServo.eState = CALLIB;
}

void ServoInit(unsigned int uiServoFrequency) {

	LedInit();
	ServoCallib();
	Timer0Interrupts_Init((1000000 / uiServoFrequency), &Automat);
}

void ServoGoTo(unsigned int uiPosition) {

	sServo.uiDesiredPosition = uiPosition;
}
