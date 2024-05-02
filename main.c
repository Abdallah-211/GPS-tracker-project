#include "io.h"
#include "distance.h"
#include "GPIO.h"
#include "UART.h"
#include "Systick.h"
#include <stdint.h>
#include <math.h>
#include "GPS.h"
#include "string.h"
#include <stdio.h>

extern double lat[100];
extern double lon[100];
extern char j;
unsigned char button_in1;
unsigned char button_in2;
unsigned char check;
double Total_distance =0;
double Dis =0;
//char ary[20] = {0}; 							//for testing

int main(){
	
		RGB_INIT();
		UART0_Init();
		UART1_Init();
		SW_INITI();
	
while(1){
	
		//printStr("Enter:\n");					//for testing

		button_in1 = SW1_Input();
		button_in2 = SW2_Input();
		GPS_format();
	
		if(j!=0)																												//don't calculate distance at first point
			{
			Dis = calcdistance(lon[j],lat[j],lon[j-1],lat[j-1]);
			Total_distance += Dis;
			//printStr0("Made sure of calcultaing distance \n"); 
			}
			j++ ; 

			//printStr0("Made sure of increment \n");
			//sprintf(ary,"Total Distance = %f \n",Total_distance);				//for testing
			//printStr0(ary); 
 

		if ((button_in1 != 0x10 || Total_distance >= 100)){ //if sw1 is pressed then turn on red light and stop taking inputs from gps
			LEDs_output(RED);
			//stop taking new coordinates
			//array into eeprom
			}
		if ((button_in2 != 0x01 )){ //if sw2 is pressed then clear
			LEDs_Clear();
			}
			}
			}
