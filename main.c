#include "io.h"
#include "distance.h"
#include "GPIO.h"
#include "UART.h"
#include "Systick.h"
#include <stdint.h>
#include <math.h>

float distance;
unsigned char button_in1;
unsigned char button_in2;
float TOTAL_distance=0;
float total_distance =0;
int main(){
RGB_INIT();
SW_INITI();
while(1){	
button_in1 = SW1_Input();
button_in2 = SW2_Input();
//calculating the distance
//passing the values from gps using UART
//call to gps functions and store coordinates in array 
//    where lat2 and long2 are elements A[i] and lat 1 and long 1 are elements A[i-1]
//distance = calcdistance (1,1,11,1);
//total_distance += distance;
if ((button_in1 != 0x10 || total_distance == 100)){ //if sw1 is pressed then turn on red light and stop taking inputs from gps
LEDs_output (RED);
//stop taking new coordinates
//array into eeprom	
}
if ((button_in2 != 0x01 )){ //if sw2 is pressed then clear
LEDs_Clear();
}
}
}
// to calculate the distance you will need to call the function [calcdistance (float long1 , float lat1 , float long2 , float lat2)]
// long1,long2,lat1,lat2 must be written in this way (ex. 4717.112671 --> 47 Degrees, 17.112671 Minutes)