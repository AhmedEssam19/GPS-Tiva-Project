#include "man_string.h"
#include "config_LCD.h"
#include "display.h"
#include "timer.h"
void SystemInit(){}

int main(){
	display_on_LCD(100);
}
void display_on_LCD(int n){
	int i;
	char str_num[24];
	itoa(n, str_num);
	LCD_init();
	LCD_Cmd(0x01); //clear screen
	LCD_Cmd(0x80);
	delay_milli(500);
	for (i = 0; i < str_len(str_num); i++){
		LCD_Data(str_num[i]);
		delay_milli(1);
	}
}
