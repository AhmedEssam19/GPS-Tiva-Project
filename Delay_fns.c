#include "tm4c123gh6pm.h"


void SysTick_Wait(unsigned long delay){ 	
    NVIC_ST_CTRL_R = 0;            /* (1) disable SysTick during setup */
    NVIC_ST_RELOAD_R = delay-1;    /* (2) number of counts to wait */
    NVIC_ST_CURRENT_R = 0;         /* (3) any value written to CURRENT clears */
    NVIC_ST_CTRL_R |= 0x5;         /* (4) enable SysTick with core clock */
 
    while((NVIC_ST_CTRL_R&0x00010000)==0) {
        ;                          /* wait for COUNT flag */
    }
}

void One_Second_Delay(void){
    NVIC_ST_CTRL_R = 0;            /* disable SysTick during setup */
    NVIC_ST_RELOAD_R = 15999999;    /* Reload Value goes here */
    NVIC_ST_CTRL_R |= 0x5;          /* enable SysTick with core clock */
    while( (NVIC_ST_CTRL_R & (1<<16) ) == 0)
        ;                           /* Monitoring bit 16 to be set */
    NVIC_ST_CTRL_R = 0;             /* Disabling SysTick Timer */
}

int main(void){
	
}