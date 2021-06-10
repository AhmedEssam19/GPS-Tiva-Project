#include "tm4c123gh6pm.h"
#include "stdint.h"

#define RED_LED 0x02
#define Blue_LED 0x04
#define Green_LED 0x08

void PortF_LEDs_Init(void)
{
    uint32_t delay;
	SYSCTL_RCGCGPIO_R  |= 0x20;
	delay = 1;
	GPIO_PORTF_CR_R = 0x0E;
	GPIO_PORTF_AFSEL_R = 0;
	GPIO_PORTF_PCTL_R = 0;
	GPIO_PORTF_AMSEL_R = 0;
	GPIO_PORTF_DIR_R = 0x0E;
	GPIO_PORTF_DEN_R = 0x0E;
}

void Red_ON(void) { GPIO_PORTF_DATA_R |= RED_LED; }
void Red_OFF(void) { GPIO_PORTF_DATA_R &= ~RED_LED; }

void Blue_ON(void) { GPIO_PORTF_DATA_R |= Blue_LED; }
void Blue_OFF(void) { GPIO_PORTF_DATA_R &= ~Blue_LED; }

void Green_ON(void) { GPIO_PORTF_DATA_R |= Green_LED; }
void Green_OFF(void) { GPIO_PORTF_DATA_R &= ~Green_LED; }
