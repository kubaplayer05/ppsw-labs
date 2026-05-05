#include <LPC21xx.H>
#include "uart.h"

#define NULL '\0'
#define TERMINATOR '\r'
#define RECIEVER_SIZE 12

// U0LCR Line Control Register
#define mDIVISOR_LATCH_ACCES_BIT                   0x00000080
#define m8BIT_UART_WORD_LENGTH                     0x00000003

// UxIER Interrupt Enable Register
#define mRX_DATA_AVALIABLE_INTERRUPT_ENABLE        0x00000001
#define mTHRE_INTERRUPT_ENABLE                     0x00000002

// UxIIR Pending Interrupt Identification Register
#define mINTERRUPT_PENDING_IDETIFICATION_BITFIELD  0x0000000F
#define mTHRE_INTERRUPT_PENDING                    0x00000002
#define mRX_DATA_AVALIABLE_INTERRUPT_PENDING       0x00000004

// VIC (Vector Interrupt Controller) channels
#define VIC_UART0_CHANNEL_NR  6
#define VIC_UART1_CHANNEL_NR  7

// VICVectCntlx Vector Control Registers
#define mIRQ_SLOT_ENABLE                           0x00000020

struct RecieverBuffer { 
   char cData[RECIEVER_SIZE];
   unsigned char ucCharCtr;
   enum eRecieverStatus eStatus;
};

char cOdebranyZnak;
struct RecieverBuffer sRecieverBuffer;

__irq void UART0_Interrupt (void) {
   
   unsigned int uiCopyOfU0IIR = U0IIR;

   if ((uiCopyOfU0IIR & mINTERRUPT_PENDING_IDETIFICATION_BITFIELD) == mRX_DATA_AVALIABLE_INTERRUPT_PENDING) {
      cOdebranyZnak = U0RBR;
      Reciever_PutCharacterToBuffer(cOdebranyZnak);
   } 
   
   if ((uiCopyOfU0IIR & mINTERRUPT_PENDING_IDETIFICATION_BITFIELD) == mTHRE_INTERRUPT_PENDING) {
      // narazie nic nie wysyłamy
   }

   VICVectAddr = 0;
}

void UART_InitWithInt(unsigned int uiBaudRate) {

   PINSEL0 = PINSEL0 | (1 << 2);                                // ustawic pina na odbiornik uart0
   U0LCR |= m8BIT_UART_WORD_LENGTH | mDIVISOR_LATCH_ACCES_BIT;  // długosc słowa, DLAB = 1
   U0DLL = ((15000000) / 16) / uiBaudRate;                      // predkosc transmisji
   U0LCR &= (~mDIVISOR_LATCH_ACCES_BIT);                        // DLAB = 0
   U0IER |= mRX_DATA_AVALIABLE_INTERRUPT_ENABLE;                // ustawianie przerwania, gdy sa dostpene dane do odczytu

   VICVectAddr1  = (unsigned long) UART0_Interrupt;             // set interrupt service routine address
   VICVectCntl1  = mIRQ_SLOT_ENABLE | VIC_UART0_CHANNEL_NR;     // use it for UART 0 Interrupt
   VICIntEnable |= (0x1 << VIC_UART0_CHANNEL_NR);               // Enable UART 0 Interrupt Channel
}

void Reciever_PutCharacterToBuffer(char cCharacter) {

   if (RECIEVER_SIZE > sRecieverBuffer.ucCharCtr) {
      if (TERMINATOR != cCharacter) {
         sRecieverBuffer.cData[sRecieverBuffer.ucCharCtr] = cCharacter;
      } else {
         sRecieverBuffer.cData[sRecieverBuffer.ucCharCtr] = NULL;
         sRecieverBuffer.eStatus = READY;
      }

      sRecieverBuffer.ucCharCtr = sRecieverBuffer.ucCharCtr + 1;

   } else {
      sRecieverBuffer.eStatus = OVERFLOW;
   }
}

enum eRecieverStatus eReciever_GetStatus(void) {

   return sRecieverBuffer.eStatus;
}

void Reciever_GetStringCopy(char *ucDestination) {

   unsigned char ucStringCounter ;

   for(ucStringCounter = 0; ucStringCounter < sRecieverBuffer.ucCharCtr; ucStringCounter++) {
      ucDestination[ucStringCounter] = sRecieverBuffer.cData[ucStringCounter];
   }

   sRecieverBuffer.eStatus = EMPTY;
   sRecieverBuffer.ucCharCtr = 0;
}
