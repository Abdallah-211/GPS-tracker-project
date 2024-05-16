#include "tm4c123gh6pm.h"
#include "io.h"
#include <stdint.h>

void Systick_wait(unsigned long delay){
	NVIC_ST_CTRL_R = 0 ;
  NVIC_ST_RELOAD_R = delay-1;
  NVIC_ST_CURRENT_R = 0;
  NVIC_ST_CTRL_R = 0X05 ;
	while ((NVIC_ST_CTRL_R & 0x00010000) == 0);
}

void Generic_delay(unsigned long time_delay){
	int i =0;
	for(i=0 ; i<time_delay ; i++){
		Systick_wait(160000); 											//wait 10 ms 
	}
}
