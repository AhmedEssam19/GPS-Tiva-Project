#include "tm4c123gh6pm.h"
#include "timer.h"
#include "config_LCD.h"
#include "stdint.h"

void LCD_Cmd(unsigned char command){
	GPIO_PORTB_DATA_R = command;
	GPIO_PORTA_DATA_R |= 0x80; // E = 1 
	delay_milli(2);
	GPIO_PORTA_DATA_R &=~(0x20);// RS = 0
	GPIO_PORTA_DATA_R &=~(0x40);// RW = 0
	delay_milli(2);
	GPIO_PORTA_DATA_R &=~(0x80); // E = 0 end pulse
}
void LCD_init(void){
	SYSCTL_RCGCGPIO_R |= 0x03; //PORTA and PORTB
	while((SYSCTL_PRGPIO_R&0x0000003) == 0){};
	
	GPIO_PORTA_LOCK_R |= 0x4C4F434B;
	GPIO_PORTA_CR_R |=0xE0;
	GPIO_PORTA_DIR_R |=0xE0; //PORTA controls RS, E and R/W pins: 5, 6, 7
	GPIO_PORTA_DEN_R |=0xE0;
		
	GPIO_PORTB_LOCK_R |= 0x4C4F434B;
	GPIO_PORTB_CR_R |=0xFF; //PORTB D0-D7
	GPIO_PORTB_DIR_R |=0xFF; 
	GPIO_PORTB_DEN_R |=0xFF; 
	
	LCD_Cmd(0x30); // wake up LCD
	delay_milli(1);
	LCD_Cmd(0x38); //8-bits,2 display lines, 5x7 font
	delay_milli(1);
	LCD_Cmd(0x0E); //diplay on
	delay_milli(1);
	LCD_Cmd(0x01); //clear display
	delay_milli(2);
	LCD_Cmd(0x0F); //Turn on display and cursor
	delay_milli(2);
	LCD_Cmd(0x02); // Return Home
	delay_milli(1);

}
void LCD_Data(unsigned char data){
	GPIO_PORTB_DATA_R = data;
	GPIO_PORTA_DATA_R |= 0x80; //set E = 1
	delay_milli(2);
	GPIO_PORTA_DATA_R |= 0x20;//rs = 1
	GPIO_PORTA_DATA_R &= ~(0x40);//rw = 0
	delay_milli(2);
	
	GPIO_PORTA_DATA_R &=~(0x80);
}
