#include <stdio.h>
#include <string.h>



void ftos(float latitude[] , float longitude[], char Co_final[], int size)
{
int k=0;
char temp [50]; // Temporary buffer to hold each float as a string
char lat_final[2100] = ""; // Assuming a maximum length for the character array
	
	for ( k = 0; k < size; k++) {
		
        sprintf(temp, "%.6f", latitude[k]); // Convert float to string with 7 decimal places
        strcat(Co_final, temp); // Concatenate the string representation
        if (k < size ) {
        strcat(Co_final, ","); // Add comma and space if not the last element
        }
    }
	
    for ( k = 0; k < size; k++) {
			
        sprintf(temp, "%.6f", longitude[k]); // Convert float to string with 7 decimal places
        strcat(Co_final, temp); // Concatenate the string representation
        if (k < size - 1) {
        strcat(Co_final, ","); // Add comma and space if not the last element
        }
    }
		
		strcat(Co_final, "\n");
		
}


