#include "TM4C123.h" // Device header
#include "timer.h"
#include "config_LCD.h"

void LCD_init(void){
	SYSCTL->RCGCGPIO |= 0x01; //PORTA clock
	SYSCTL->RCGCGPIO |= 0x02;
	
	GPIOA->DIR |=0xE0; //PORTA controls RS, E and R/W pins: 5, 6, 7
	GPIOA->DEN |=0xE0;
	
	GPIOB->DIR |=0xFF; //PORTB D0-D7
	GPIOB->DEN |=0xFF; //PORTB D0-D7
	
	LCD_Cmd(0x38); //8-bits,2 display lines, 5x7 font
	LCD_Cmd(0x06); //increments automatically
	LCD_Cmd(0x0F); //Turn on display
	LCD_Cmd(0x01); //clear display
}
void LCD_Cmd(unsigned char command){
	GPIOA->DATA = 0x00; //RS =0, E=0, RW=0
	GPIOB->DATA =command;
	
	GPIOA->DATA =0x80; //E=1 to secure command pin 7
	delay_micro(0);
	GPIOA ->DATA =0x00;
	if(command <4) delay_milli(2); else delay_micro(37);
}
void LCD_Data(unsigned char data){
	GPIOB->DATA =data;
	GPIOA->DATA |= 0x80;
	GPIOA->DATA =0x00;
	delay_micro(0);
}
