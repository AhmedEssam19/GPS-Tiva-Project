#include "TM4C123.h" // Device header
#include "timer.h"
#include "config_LCD.h"

void LCD_init(void){
	SYSCTL_RCGCGPIO_R |= 0x01; //PORTA clock
	SYSCTL_RCGCGPIO_R |= 0x02;
	
	GPIO_PORTA_DIR_R |=0xE0; //PORTA controls RS, E and R/W pins: 5, 6, 7
	GPIO_PORTA_DEN_R |=0xE0;
	
	GPIO_PORTB_DIR_R |=0xFF; //PORTB D0-D7
	GPIO_PORTB_DEN_R |=0xFF; //PORTB D0-D7
	
	LCD_Cmd(0x38); //8-bits,2 display lines, 5x7 font
	LCD_Cmd(0x06); //increments automatically
	LCD_Cmd(0x0F); //Turn on display
	LCD_Cmd(0x01); //clear display
}
void LCD_Cmd(unsigned char command){
	GPIO_PORTA_DATA_R = 0x00; //RS =0, E=0, RW=0
	GPIO_PORTB_DATA_R =command;
	
	GPIO_PORTA_DATA_R =0x80; //E=1 to secure command pin 7
	delay_micro(0);
	GPIO_PORTA_DATA_R =0x00;
	if(command <4) delay_milli(2); else delay_micro(37);
}
void LCD_Data(unsigned char data){
	GPIO_PORTA_DATA_R =0x20; //RS=1, E=0,RW=0
	GPIO_PORTB_DATA_R =data;
	GPIO_PORTA_DATA_R |= 0x80;
	GPIO_PORTA_DATA_R =0x00;
	delay_micro(0);
}
