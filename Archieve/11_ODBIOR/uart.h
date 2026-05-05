#ifndef UART
#define UART

enum eRecieverStatus {EMPTY, READY, OVERFLOW};

extern char cOdebranyZnak;

void UART_InitWithInt(unsigned int uiBaudRate);

void Reciever_PutCharacterToBuffer(char cCharacter);

enum eRecieverStatus eReciever_GetStatus(void);

void Reciever_GetStringCopy(char *ucDestination);

#endif
