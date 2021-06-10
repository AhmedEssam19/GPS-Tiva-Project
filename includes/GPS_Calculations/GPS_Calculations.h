#ifndef __GPS_Calculations_H_
#define __GPS_Calculations_H_

struct Point read_from_GPS();
double deg2rad(double deg);
double rad2deg(double rad);
double calculate_distance(struct Point p1, struct Point p2);
double calculate_speed(struct Point p1,struct Point p2, double distance);
double calculate_distance_accurate(double lon1,double lon2,double lat1,double lat2);

#endif
