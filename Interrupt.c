#include "tm4c123gh6pm.h" 
#include "stdint.h" 
#include "io.h"

void GPIOF_Handler()
{
	  		 __disable_irq();
		               // disable_global_Interrupt_flag 
	      GPIO_PORTF_ICR_R |= 0X10;
	                // clear flag4
        GPIO_PORTF_DATA_R |= 0X02;
	                //turnon_red_led
        	__enable_irq();
		             // Enable_global_Interrupt_flag 
}
void interrupt_conf(void)
{
			 __enable_irq();
	               // Enable_global_Interrupt_flag 
	   GPIO_PORTF_ICR_R |= 0X10;
	               // clear_flag4
		 GPIO_PORTF_IM_R |= 0X10;
	               // arm_interrupt on PF4
    GPIO_PORTF_IS_R &=~ 0x10;
	               // PF4_is_edge_sensitive
    GPIO_PORTF_IBE_R &=~ 0X10;
	               // PF4_is_not_bothedges
    GPIO_PORTF_IEV_R &=~ 0X10;
	               // PF4_falling_edge_event
	  NVIC_EN0_R |=0X40000000;
	               // enable_interrupt_30_in_NVIC 
	  NVIC_PRI7_R = (NVIC_PRI7_R & 0XFF1FFFFF) | 0X00A00000; 
	               // priority
}
