#include "tm4c123gh6pm.h"
#include "bit_utilies.h"
#include "SysTick.h"
#include <stdint.h>

void Printdata(unsigned char data);
void LCD_Data(unsigned char data);
void LCD_Cmd(unsigned char cmd);
void LCD_String(unsigned char *str , unsigned char len);
void LCD_Init(void);
	// RS = PD0
	// RW = PD1
	// EN = PD2
	
	// D0 = PA7
	// D1 = PA6
	// D2 = PA5
	// D3 = PB4
	// D4 = PE5
	// D5 = PE4
	// D6 = PE1
	// D7 = PD3
	unsigned char arr[5]="Ahmed";	

void PORTA_Init(){
	
	SYSCTL_RCGCGPIO_R |= 0x01;
	while((SYSCTL_PRGPIO_R &= 0x01)==0);
	GPIO_PORTA_CR_R |=0xFC;
	GPIO_PORTA_AMSEL_R = 0x00;
	GPIO_PORTA_AFSEL_R = 0x00;
	GPIO_PORTA_PCTL_R = 0x00000000;
	GPIO_PORTA_DIR_R =0x0FC;
	GPIO_PORTA_DEN_R =0x0FF;
	GPIO_PORTA_DATA_R =0X00;
}

void PORTB_Init(){

	SYSCTL_RCGCGPIO_R |= 0X02;
	while((SYSCTL_PRGPIO_R &= 0X02)==0);
	GPIO_PORTB_CR_R |=0xFF;
	GPIO_PORTB_AMSEL_R = 0x00;
	GPIO_PORTB_AFSEL_R = 0x00;
	GPIO_PORTB_PCTL_R = 0x00000000;
	GPIO_PORTB_DIR_R =0x0FF;
	GPIO_PORTB_DEN_R =0x0FF;
	GPIO_PORTB_DATA_R =0x00;
}




void LCD_Data(unsigned char data){	
	
	Printdata(data);	//Pass the 8 Bit data to the datalines of LCD
	GPIO_PORTD_DATA_R &= (~(1<<1));		//Turn OFF the RW for write operation in LCD
	GPIO_PORTD_DATA_R |= (1<<0);			//Turn ON the RS for writing to the data register of LCD
	GPIO_PORTD_DATA_R |= (1<<2);			//Turn ON the En of LCD for enabling the clock of LCD
	Generic_delay(10);				//Wait for sometime
	GPIO_PORTD_DATA_R &= (~(1<<2));		//Turn OFF the En of LCD
}


//to print a String which is array of char we will call LCD_Data until we print all the String

void LCD_String(unsigned char *str , unsigned char len){
	char i;
	for(i=0 ; i<len ; i++){
		LCD_Data(str[i]);
		}
}

int LCD(){
	
  PORTA_Init();
	PORTB_Init();
	PORTD_Init();
	PORTE_Init();
	// Clock of PORTA, PORTB, PORTD, PORTE
	SYSCTL_RCGCGPIO_R |=0x1B ;
	// Digitalize the datapins and config pins
	GPIO_PORTA_DEN_R |= 0xE0 ;
	GPIO_PORTB_DEN_R |= 0x10 ;
	GPIO_PORTD_DEN_R |= 0x0F ;
	GPIO_PORTE_DEN_R |= 0x32 ;
	// Direction of datapins and config pins -> Output Pins
	GPIO_PORTA_DIR_R |= 0xE0 ;
	GPIO_PORTB_DIR_R |= 0x10 ;
	GPIO_PORTD_DIR_R |= 0x0F ;
	GPIO_PORTE_DIR_R |= 0x32 ;
		
	while(1){
		

	}
return 0 ;
}