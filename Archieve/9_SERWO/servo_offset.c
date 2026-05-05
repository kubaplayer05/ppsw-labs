#include <LPC21xx.H>
#include "servo.h"
#include "led.h"
#include "timer_interrupts.h"

#define DETECTOR_bm (1 << 10)
#define OFFSET 12

enum DetectorState{ACTIVE, INACTIVE};
enum ServoState {CALLIB, SET_OFFSET ,IDLE, IN_PROGRESS};

struct Servo {
	enum ServoState eState; 
	unsigned int uiCurrentPosition; 
	unsigned int uiDesiredPosition;
	unsigned int uiOffsetCounter;
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
					sServo.uiOffsetCounter = 0;
					sServo.eState = SET_OFFSET;
				} else {
					LedStepRight();
					sServo.eState = CALLIB;
				}

				break;
			
			case SET_OFFSET:
				if(OFFSET == sServo.uiOffsetCounter) {
					sServo.eState = IDLE;
				} else {
					LedStepLeft();
					sServo.uiOffsetCounter = sServo.uiOffsetCounter + 1;
					sServo.eState = SET_OFFSET;
				}

				break;

			case IDLE:
				if(sServo.uiCurrentPosition != sServo.uiDesiredPosition) {
					sServo.eState = IN_PROGRESS;
				} else {
					sServo.eState = IDLE;
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
    DetectorInit();
	ServoCallib();
	Timer0Interrupts_Init((1000000 / uiServoFrequency), &Automat);
}

void ServoGoTo(unsigned int uiPosition) {

	sServo.uiDesiredPosition = uiPosition;
}

unsigned int uiServoGetCurrentPosition(void) {
    return sServo.uiCurrentPosition;
}
