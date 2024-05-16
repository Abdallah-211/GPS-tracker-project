#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "io.h"
#include "tm4c123gh6pm.h"
#include "UART.h"
#include "GPS.h"
#include "distance.h"
#include "GPIO.h"

		char tokens[7][20];				// 7 is the number of desired data from GPS_module
		
		//const int maxLen = 100;			//for simulation 
		//char command[maxLen]={0}; 
	
		
void GPS_format(void){

	
	char GPS_data [80];             			//array to save the desired data of GPS ($GPRMC logname)
    	char GPS_logname[] = "$GPRMC,";  			//logname of desired data
	char fill_gps_counter = 0;				//counter to fill the (GPS_data) array with the desired data
    	char recieved_char;												
    	const char delimiter[] = ","; 				//to separate data from eachother										
    	char *token ;
	char token_count = 0;
	char i=0;
   	char flag = 1;
	//RGB_INIT();
	

do{
	//UART0_ReadString(command,maxLen);				//for testing
	flag =1;
    	for (i=0; i<7;i++) {
    	if (UART1_getChar()!= GPS_logname[i]) {				//checking for logname ($GPRMC,)
    	flag=0; 
    	break;
    	}
    	}
}while(flag==0);
		//UART0_OutString("Made sure of Logname \n"); 		//Confirmation of checking the Logname for testing
		//LEDs_output(RED);					//LED ON to make sure that the code didn't get stucked at the do-while loop
		
		strcpy(GPS_data,"");					//making sure that the array is empty
		
do									//extracting the $GPRMC logname comand and putting it into array GPS_data
    {									//taken into consideration that ($GPRMC,) isn't in GPS_data array
    recieved_char = UART1_getChar();
    GPS_data[fill_gps_counter++] = recieved_char ;

    }while(recieved_char!='*');
	//UART0_OutString("till the *\n");

	UART0_OutString(GPS_data);					//Printing the logname

	//char *result;							//intial idea if data passed was char array not char by char
    	//simple function to find the required GPS_logname
   	//result = strstr(GPS,GPS_logname[i]);
		
   	//intializing an array starting after the this logname
    	//strcpy(GPS_data,result+strlen(GPS_logname));
    
	//Tokenize the array using strtok
	token = strtok(GPS_data, delimiter); 
	
    	// Loop through each token and save them in string array (tokens)
	while (token != NULL && token_count < 7) {
		strcpy(tokens[token_count], token);
		token_count++;
		token = strtok(NULL, delimiter);
			}

		//strcpy(command,"" );					//for testing (to be able to take more than one command)	

	}
