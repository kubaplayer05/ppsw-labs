#ifndef SERVO
#define SERVO

void DetectorInit(void);

void ServoCallib(void);

void ServoInit(unsigned int uiServoFrequency);

void ServoGoTo(unsigned int uiPosition);

#endif
