#include <LPC21xx.H>
#include "uart.h"

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

char cOdebranyZnak;

__irq void UART0_Interrupt (void) {
   
   unsigned int uiCopyOfU0IIR = U0IIR;

   if ((uiCopyOfU0IIR & mINTERRUPT_PENDING_IDETIFICATION_BITFIELD) == mRX_DATA_AVALIABLE_INTERRUPT_PENDING) {
      cOdebranyZnak = U0RBR;
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
