#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>
#include "../UART/UART_0.h"
#include "../UART/UART_5.h"
#include "../double_to_string/DoubleToString.h"
#include "../Point/Point.h"

#define pi 3.14159265358979323846

//Add -dLaunchPadDLL for simulator




struct Point read_from_GPS(void){
    
    char c0 , GPSValues[100]  , parseValue[12][20] , *token;
    double  seconds = 0.0, minutes = 0.0, current_time = 0.0;
    const char comma[2] = ",";
    int index = 0, degrees;
    
    struct Point p_result;
    
    while(1){
									//"$GPRMC,200751.00,A,4047.32510,N,02929.63031,E,9.879,105.80,301117,,,A*6C"
      //printstring("YEESSS\n");  
			c0 = UART5_READ();
				UART0_WRITE(c0);
        //Is the incoming data $GPRMC?
        if(c0 == '$'){
            c0 = UART5_READ();
						UART0_WRITE(c0);
					if(c0 == 'G'){
                c0 = UART5_READ();
								UART0_WRITE(c0);
                if(c0 == 'P'){
                    c0 = UART5_READ();
									UART0_WRITE(c0);
                    if(c0 == 'R'){
                        c0 = UART5_READ();
											UART0_WRITE(c0);
                        if(c0 == 'M'){
                            c0 = UART5_READ();
													UART0_WRITE(c0);
                            if(c0 == 'C'){
                                c0 = UART5_READ();
															UART0_WRITE(c0);
                                if(c0 == ','){
                                    c0 = UART5_READ();
																	UART0_WRITE(c0);
                                    //Assign data to the GPSValues array.Read up to the last data checksum (such as checksum: A * 60) 
                                    while(c0 != '*'){
                                        GPSValues[index] = c0;
                                        c0 = UART5_READ();
																			UART0_WRITE(c0);
                                        index++;
																		}
    
                                    //Separating data in the GPS Values array by commas 
                                    index = 0;
                                    token = strtok(GPSValues, comma);
                                    while( token != NULL ) {
                                        strcpy(parseValue[index], token);
                                        token = strtok(NULL, comma);
                                        index++;
																		}
    
                                    //Data is valid if parseValue [1] = A - Not valid if V 
                                    if( strcmp(parseValue[1], "A") == 0){
																			//latitude and longitude calculation
																			//printstring("Longggggggggggggggg:		");  	
																			//printstring(parseValue[2]);
																			p_result.latitude = atof(parseValue[2]);
                                      p_result.longitude = atof(parseValue[4]);
																			
																			
																			////////
																			degrees = p_result.latitude /100;
																			minutes = p_result.latitude - (double) (degrees *100);
																			seconds = minutes / 60.00;
																			p_result.latitude = degrees + seconds;
																			
																			
																			degrees = p_result.longitude  /100;
																			minutes = p_result.longitude  - (double) (degrees *100);
																			seconds = minutes / 60.00;
																			p_result.longitude  = degrees + seconds;
																			
																			
																			
      
																			 
                                        //161529.555
                                        // Hours, minutes and seconds calculation
                                        current_time = atof(parseValue[0]);
                                        p_result.arrival_hour = current_time / 10000;
                                        current_time = current_time - (p_result.arrival_hour * 10000);
                                        p_result.arrival_minute = current_time / 100;
                                        current_time = current_time - (p_result.arrival_minute * 100);
                                        p_result.arrival_second = current_time;
                                        
                                        return p_result;
                                        
                                    }
																	}
									}
								}
							}
						}
					}
				}
		}
}


/*::  This function converts decimal degrees to radians             :*/
double deg2rad(double deg) {
  return (deg * pi / 180);
}

/*::  This function converts radians to decimal degrees             :*/
double rad2deg(double rad) {
  return (rad * 180 / pi);
}

double calculate_distance(struct Point p1, struct Point p2) {
  double theta, dist;
	
	char res[20];
			printstring("\nLong1");  
		ftoa(p1.longitude, res, 6);
		printstring("\n"); 
			printstring(res);
			
			printstring("\nLong2");  
		ftoa(p2.longitude, res, 6);
		printstring("\n"); 
			printstring(res);
			
			printstring("\nLat1");  
		ftoa(p1.latitude, res, 6);
		printstring("\n"); 
			printstring(res);
			
			printstring("\nLat2");  
		ftoa(p2.latitude, res, 6);
		printstring("\n"); 
			printstring(res);
		
	
  if ((p1.latitude == p2.latitude) && (p1.longitude == p2.longitude)) {
    return 0;
  }
  else {
    theta = p1.longitude - p2.longitude;
    dist = sin(deg2rad(p1.latitude)) * sin(deg2rad(p2.latitude)) + cos(deg2rad(p1.latitude)) * cos(deg2rad(p2.latitude)) * cos(deg2rad(theta));
    dist = acos(dist);
    dist = rad2deg(dist);
    dist = dist * 60 * 1.1515;
		dist = dist * 1.609344;
		dist *= 1000;
		
		
		
    return (dist);
  }
}

double calculate_distance_accurate(double lon1,double lon2,double lat1,double lat2) {
		double distance;
		lat1 = lat1 * ( pi / 180.0 );  
    lat2 = lat2 * ( pi / 180.0 );  
    lon1 = lon1 * ( pi / 180.0 );  
    lon2 = lon2 * ( pi / 180.0 );  
    distance = 3963 * acos( sin(lat1) * sin(lat2) + cos(lat1) * cos(lat2) * cos(lon2 - lon1) )*1609.344;  
  	return distance;
}


double calculate_speed(struct Point p1,struct Point p2, double distance){
    int total_time_in_seconds = 0;
    total_time_in_seconds = (p2.arrival_hour - p1.arrival_hour) * 3600;
    total_time_in_seconds += (p2.arrival_minute - p1.arrival_minute) * 60;
    total_time_in_seconds += p2.arrival_second - p1.arrival_second;
    if (total_time_in_seconds < 0) total_time_in_seconds *= -1;
	
    return distance / (double) total_time_in_seconds;
}

