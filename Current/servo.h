#ifndef SERVO
#define SERVO

void ServoCallib(void);

void ServoInit(unsigned int uiServoFrequency);

void ServoGoTo(unsigned int uiPosition);

unsigned int uiServoGetCurrentPosition(void);

#endif
