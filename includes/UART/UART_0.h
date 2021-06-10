#ifndef __UART_H_
#define __UART_H_

void UART0_Init(void);
unsigned int UART0_Available(void);
void UART0_WRITE(unsigned int data);
unsigned int UART0_READ(void);
void printstring(char *data);
void SystemInit();

#endif
