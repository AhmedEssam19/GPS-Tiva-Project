#include "C:/Keil/ti/TivaWare_C_Series-2.2.0.295/inc/tm4c1233h6pm.h"
#include "man_string.h"
#include "config_LCD.h"
#include "display.h"
#include "timer.h"
#include "stdint.h"

void SystemInit(){}

int main(){
	char *write = "ALLAH AKBAR";

	delay_init();
	LCD_init();
 while(1){
LCD_Cmd(0x02);
				delay_milli(2);
	 display_string_on_LCD(write);
		//display_on_LCD(100);
	  //display_string_on_LCD("m");
	
 }
}
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

