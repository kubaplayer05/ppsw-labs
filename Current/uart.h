#ifndef UART
#define UART

enum eRecieverStatus {EMPTY, READY, OVERFLOW};
enum eTransmiterStatus {FREE, BUSY};

extern char cOdebranyZnak;

void UART_InitWithInt(unsigned int uiBaudRate);

void Reciever_PutCharacterToBuffer(char cCharacter);

enum eRecieverStatus eReciever_GetStatus(void);

void Reciever_GetStringCopy(char *ucDestination);

char Transmiter_GetCharacterFromBuffer(void);

void Transmiter_SendString(char cString[]);

enum eTransmiterStatus Transmiter_GetStatus(void);

#endif
