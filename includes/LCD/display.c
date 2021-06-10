#include "tm4c123gh6pm.h"
#include "man_string.h"
#include "config_LCD.h"
#include "display.h"
#include "timer.h"
#include "stdint.h"


void display_on_LCD(int n){
	char str_num[24];
	itoa(n, str_num);
	display_string_on_LCD(str_num);
}
void display_string_on_LCD(char* str){
	int count = 0;
	while (str[count] != '\0'){
		if (count >= 15){
			LCD_Cmd(0xC0);
		}
		LCD_Data(str[count]);
		count += 1;
	}
	if (count >12)
		LCD_Cmd(0xC0);
}


