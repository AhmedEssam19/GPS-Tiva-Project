#define SYSCTL_RCGCGPIO_R (*(( volatile unsigned long *)0x400FE608 ) )
#define GPIO_PORTF_DATA_R (*(( volatile unsigned long *)0x40025038 ) ) 
#define GPIO_PORTF_DIR_R  (*(( volatile unsigned long *)0x40025400 ) ) 
#define GPIO_PORTF_DEN_R  (*(( volatile unsigned long *)0x4002551C ) )
#define GPIO_PE54_M 0x30
#define GPIO_PA10_M 0x03
#define RED_LED 0x02
#define Blue_LED 0x04
#define Green_LED 0x08
#define pi 3.14159265358979323846

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "includes/LEDs/LEDs.h"
#include "includes/double_to_string/DoubleToString.h"
#include "includes/GPS_Calculations/GPS_Calculations.h"
#include "includes/UART/UART_5.h"
#include "includes/UART/Uart_0.h"
#include "includes/Point/Point.h"
#include "includes/LEDs/LEDs.H"
#include "includes/Delays/Delays.H"
#include "includes/LCD/display.h"
#include "includes/LCD/config_LCD.h"
#include "includes/LCD/timer.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>

void SystemInit(){}
	 

int main ( void ){
	char res[20],LED;
	char *test;
	double speed = 0.0;
	char *write = "finally";
	struct Point current_point,last_point;
	double distance=0,final_distance=0;
	int i;
	delay_init();
	LCD_init();
	UART0_Init();
	UART5_Init();
	PortF_LEDs_Init();
	
		/*
			int i;
	for(i=0;i<60;i++){
		One_Second_Delay();
	}
	*/
	//last_point=read_from_GPS();
	
	for(i=0;i<30;i++){
		delay_milli(1000);
	}
	
	for(LED=0x02;LED<=0x08;LED=LED<<1){
				GPIO_PORTF_DATA_R &= ~0x0E;
				GPIO_PORTF_DATA_R=LED;
				delay_milli(1000);		
			}
	i=0;
	while(1){
				LCD_Cmd(0x01);
		i++;
		//"$GPRMC,200751.00,A,4047.32510,N,02929.63031,E,9.879,105.80,301117,,,A*6C"
		
			//display_string_on_LCD("100 m")
		current_point=read_from_GPS();
		//printstring("Latitude:");
		//sprintf(test,"%f",current_point.latitude);	
		//printstring(test);
		
		//printstring("Longtude:");
		//sprintf(test,"%f",current_point.longitude);	
		//printstring(test);
		
		//distance = calculate_distance(current_point, last_point);
		/*	
		current_point.latitude = current_point.latitude * ( pi / 180.0 );  
    last_point.latitude = last_point.latitude * ( pi / 180.0 );  
    current_point.longitude = current_point.longitude * ( pi / 180.0 );  
    last_point.longitude = last_point.longitude * ( pi / 180.0 );  
  
    distance = 3963 * acos( sin(current_point.latitude) * sin(last_point.latitude) + cos(current_point.latitude) * cos(last_point.latitude) * cos(last_point.longitude - current_point.longitude) )*1609.34;  
  */
		distance = calculate_distance_accurate(current_point.longitude,last_point.longitude,current_point.latitude,last_point.latitude);
  	if(distance<3&&distance>1){
			final_distance += distance;
		}
		while(final_distance>=100){
			GPIO_PORTF_DATA_R &= ~0x0E;
				GPIO_PORTF_DATA_R=LED;
				delay_milli(1000);	
				ftoa(final_distance, res, 6);
				printstring("\nYOU REACED YOUR DESTINATION!!\n");
				delay_milli(2);
			display_string_on_LCD("Reached: ");		
			display_string_on_LCD(res);
			display_string_on_LCD("m");
			
		}	
		printstring("\nDistance");  
		ftoa(distance, res, 6);
		printstring("\n"); 
			printstring(res);
		
		printstring("Final Distance");  
		ftoa(final_distance, res, 6);
		printstring("\n"); 
			printstring(res);
		
				delay_milli(2);
		display_string_on_LCD("F_dist:");		
			display_string_on_LCD(res);
			display_string_on_LCD("m");
		
		
		speed = (final_distance*100)/(1.5*i);
		ftoa(speed, res, 6);
		LCD_Cmd(0xC0);
		delay_milli(2);
			display_string_on_LCD("Avrg speed:");		
			display_string_on_LCD(res);
			display_string_on_LCD("cm/s");
		delay_milli(1500);
				
		/*
			printstring("\nLong1");  
		ftoa(current_point.longitude, res, 6);
		printstring("\n"); 
			printstring(res);
			
			printstring("\nLong2");  
		ftoa(last_point.longitude, res, 6);
		printstring("\n"); 
			printstring(res);
			
			printstring("\nLat1");  
		ftoa(current_point.latitude, res, 6);
		printstring("\n"); 
			printstring(res);
			
			printstring("\nLat2");  
		ftoa(last_point.latitude, res, 6);
		printstring("\n"); 
			printstring(res);
		*/
		
		last_point.longitude=current_point.longitude;
		last_point.latitude=current_point.latitude;
		
		
	}
}
