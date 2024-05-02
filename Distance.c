#include <stdio.h>
#include <math.h>
#include <stdio.h>
#include "distance.h"
#include <stdint.h>
double distance;
double todegree(double angle) {
int    degree = angle / 100;                    // Extracting the degree part
double minutes = angle - (double)degree * 100; // Extracting the minutes part
 return (degree + minutes / 60);              // Converting minutes to degrees;
}
double torad(double angle) {
 return angle * M_PI / 180.0;
}
double calcdistance (double long1 ,double lat1 ,double long2 ,double lat2){
double long_diff;
double lat_diff;
double a;
double c;
long1 = torad (todegree( long1));
long2 = torad (todegree( long2));
lat2  = torad (todegree( lat2 ));
lat1  = torad (todegree( lat1 ));
long_diff=long1-long2;
lat_diff= lat1-lat2;
a= pow(sin(lat_diff/2),2) + cos(lat1) * cos(lat2) * pow(sin(long_diff/2),2);
c = 2*atan2(sqrt(a), sqrt(1.0 - a));
distance = Earth_Radius*c;
return (distance);
}