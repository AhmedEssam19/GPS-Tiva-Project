#ifndef __UART_5_H_
#define __UART_5_H_

void UART5_Init(void);

unsigned int UART5_Available(void);

void UART5_WRITE(unsigned int data);

unsigned int UART5_READ(void);

#endif
