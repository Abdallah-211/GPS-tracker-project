#include "io.h"
#include "distance.h"
#include "GPIO.h"
#include "UART.h"
#include "Systick.h"
#include <stdint.h>
#include "GPS.h"
#include <string.h>
#include <stdio.h>
#include "tm4c123gh6pm.h"
#include "bit_utilies.h"
#include <stdlib.h>
#include "Interrupt.h"
#include "eeprom.h"
#include "zabs.h"
//#include "LCD.h"

float latitude=0;
float longitude=0;
float lat[50]={0};						//arrays for saving coordinates into the array
float lon[50]={0};
float Read_latitude[50] = {0};					//arrays for reading from eeprom
float Read_longitude[50] = {0};
char Co_final [2100] = "";
int j=0;
extern char tokens[7][20];
unsigned char button_in1;
unsigned char button_in2;
float Total_distance =0;
float Dis =0;
char ary[20] = {0}; 						//for displaying values on serial monitor

float convert_to_float(char *value)
{
float converted;		
	 converted=atof(value);
return converted;		
}

int main(){
		RGB_INIT();
		UART0_Init();
		UART1_Init();
		SW_INITI();
		eeprom_init();
		interrupt_conf(); 
		Generic_delay(3000);  					//30 SEC "GPS fix"
		j=0;
		Total_distance =0;
	
while(1){
	
		//printStr("Enter:\n");					//for testing

		button_in1 = SW1_Input();
		button_in2 = SW2_Input();
if (Total_distance <= 100 && j<50){					//if total distance surpassed 100 m or the array is full stop taking new coordinates
		GPS_format();
		//LEDs_output(BLUE);					//for testing to make sure that the execution isn't stucked at GPS_format()
		Generic_delay(500);					//delay between each reading
		//LEDs_Clear();
			
		sprintf(ary,"Validity = %s \n",tokens[1]);		//printing the Validity char
		UART0_OutString(ary);	
		sprintf(ary,"j = %d \n",j);					
		UART0_OutString(ary);

if (strcmp(tokens[1],"A")==0){						//checking Validity 
			
//extracting desired variables of the string array
			
if (strcmp (tokens[3],"N")==0)
             	{
			latitude = todegree(convert_to_float(tokens[2]));
			lat[j]=latitude ;
			//UART0_OutString("Made sure of latitude\n") ; 				
            	}
else
                {
			latitude = -(todegree(convert_to_float(tokens[2])));
              		lat[j]=latitude;
			//UART0_OutString("Made sure of latitude\n") ; 
                }
								
if (strcmp (tokens[5],"E")==0)
         	{
			longitude = todegree(convert_to_float(tokens[4]));
			lon[j]= longitude ; 
			//UART0_OutString("Made sure of longitude\n") ; 
				
        	}
else
		{
			longitude = -(todegree(convert_to_float(tokens[4])));
			lon[j]= longitude ;
			//UART0_OutString("Made sure of longitude\n") ; 				
		}
							
if(j!= 0)				//don't calculate distance at first point
		{
			Dis = calcdistance(lon[j-1],lat[j-1],lon[j],lat[j]);
			Total_distance += Dis;
			//UART0_OutString("Made sure of calcultaing distance \n"); 
		}
			
			sprintf(ary,"Latitude = %f \n",latitude);				//printing the temporary longitude and latitude variables
			UART0_OutString(ary);	
			sprintf(ary,"Longitude = %f \n",longitude);
			UART0_OutString(ary);	
			sprintf(ary,"Latitude1 = %f \n",lat[j-1]);				//printing the array to make the data is saved correctly
			UART0_OutString(ary);	
			sprintf(ary,"Longitude1 = %f \n",lon[j-1]);
			UART0_OutString(ary);
			sprintf(ary,"Latitude2 = %f \n",lat[j]);
			UART0_OutString(ary);	
			sprintf(ary,"Longitude2 = %f \n",lon[j]);
			UART0_OutString(ary);
			sprintf(ary,"Total Distance = %f \n",Total_distance);			//printing the Total Distance
			UART0_OutString(ary); 
			j++ ; 
		
		}
}


		if ((button_in1 != 0x10 || Total_distance >= 100)){ 			//if sw1 is pressed then turn on red light and stop taking inputs from gps
			LEDs_output(RED);
			//stop taking new coordinates
			//array into eeprom
			}
		if ((button_in2 != 0x01 )){ //if sw2 is pressed then clear
			LEDs_Clear();
			}
			}
			}
