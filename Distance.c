#include <stdio.h>
#include <math.h>
#include <stdio.h>
#include "distance.h"
#include <stdint.h>
float dis;
float todegree(float angle) {
    int degree = angle / 100;                    // Extracting the degree part
    float minutes = angle - (float)degree * 100; // Extracting the minutes part
    return (degree + minutes / 60);              // Converting minutes to degrees;
}
float torad(float angle) {
    return angle * M_PI / 180.0;
}
float calcdistance (float long1 ,float lat1 ,float long2 ,float lat2){
float long_diff;
float lat_diff;
float a;
float F;
long1 = (torad( long1));
long2 = (torad( long2));
lat2  = (torad( lat2 ));
lat1  = (torad( lat1 ));
long_diff=long1-long2;
lat_diff= lat1-lat2;
a= pow(sin(lat_diff/2),2) + cos(lat1) * cos(lat2) * pow(sin(long_diff/2),2);
F = 2*atan2(sqrt(a), sqrt(1.0 - a));
dis = 6378100*F;
return (dis);
}
