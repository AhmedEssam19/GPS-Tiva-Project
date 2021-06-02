#include "TM4C123.h" // Device header
#include "timer.h"

void delay_init(void){
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_RELOAD_R = 0x00FFFFFF;
	NVIC_ST_CURRENT_R = 0;
	NVIC_ST_CTRL_R |= 0x00000005;
		
}
void delay(int n){
	NVIC_ST_RELOAD_R = n-1;
	NVIC_ST_CURRENT_R = 0;
	while((NVIC_ST_CTRL_R&0x00010000)==0){};
}
void delay_milli(int n){
	unsigned long i; 
	for(i=0; i<n; i++){
		delay(80000);
	}
}
void delay_micro(int n){
	unsigned long i; 
	for(i=0; i<n; i++){
		delay(80);
	}
}
