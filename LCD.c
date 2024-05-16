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


void PORTD_Init(){

	SYSCTL_RCGCGPIO_R |= 0X08;
	while((SYSCTL_PRGPIO_R &= 0X08)==0);
	GPIO_PORTD_CR_R |=0xFF;
	GPIO_PORTD_AMSEL_R = 0x00;
	GPIO_PORTD_AFSEL_R = 0x00;
	GPIO_PORTD_PCTL_R = 0x00000000;
	GPIO_PORTD_DIR_R =0x0FF;
	GPIO_PORTD_DEN_R =0x0FF;
	GPIO_PORTD_DATA_R =0x00;
}

void PORTE_Init(){

	SYSCTL_RCGCGPIO_R |= 0X010;
	while((SYSCTL_PRGPIO_R &= 0X010)==0);
	GPIO_PORTE_CR_R |=0xFF;
	GPIO_PORTE_AMSEL_R = 0x00;
	GPIO_PORTE_AFSEL_R = 0x00;
	GPIO_PORTE_PCTL_R = 0x00000000;
	GPIO_PORTE_DIR_R =0x0FF;
	GPIO_PORTE_DEN_R =0x0FF;
	GPIO_PORTB_DATA_R =0x00;
}

void Printdata (unsigned char data){ // data = 8 bit hexadecimal data
	// zeroth bit = D0 = PA7
	if((data&0x01) == 0x01)	{	GPIO_PORTA_DATA_R |= (1<<7)		;	}
	else										{	GPIO_PORTA_DATA_R &= (~(1<<7));	}
	//First bit = D1 = PA6
	if((data&0x02) == 0x02)	{	GPIO_PORTA_DATA_R |= (1<<6)		;	}
	else										{	GPIO_PORTA_DATA_R &= (~(1<<6));	}
	//Second bit = D2 = PA5
	if((data&0x04) == 0x04)	{	GPIO_PORTA_DATA_R |= (1<<5)		;	}
	else										{	GPIO_PORTA_DATA_R &= (~(1<<5));	}
	//Third bit = D3 = PB4
	if((data&0x08) == 0x08)	{	GPIO_PORTB_DATA_R |= (1<<4)		;	}
	else										{	GPIO_PORTB_DATA_R &= (~(1<<4));	}
	//Fourth bit = D4 = PE5
	if((data&0x10) == 0x10)	{	GPIO_PORTE_DATA_R |= (1<<5)		;	}
	else										{	GPIO_PORTE_DATA_R &= (~(1<<5));	}
	//Fifth bit = D5 = PE4
	if((data&0x20) == 0x20)	{	GPIO_PORTE_DATA_R |= (1<<4)		;	}
	else										{	GPIO_PORTE_DATA_R &= (~(1<<4));	}
	//Sixth bit = D6 = PB1->PE1
	if((data&0x40) == 0x40)	{	GPIO_PORTE_DATA_R |= (1<<1)		;	}
	else										{	GPIO_PORTE_DATA_R &= (~(1<<1));	}
	//Seventh bit = D7 = PB0->PD3
	if((data&0x80) == 0x80)	{	GPIO_PORTD_DATA_R |= (1<<3)		;	}
	else										{	GPIO_PORTD_DATA_R &= (~(1<<3));	}
}




void LCD_Data(unsigned char data){	
	
	Printdata(data);	//Pass the 8 Bit data to the datalines of LCD
	GPIO_PORTD_DATA_R &= (~(1<<1));		//Turn OFF the RW for write operation in LCD
	GPIO_PORTD_DATA_R |= (1<<0);			//Turn ON the RS for writing to the data register of LCD
	GPIO_PORTD_DATA_R |= (1<<2);			//Turn ON the En of LCD for enabling the clock of LCD
	Generic_delay(10);				//Wait for sometime
	GPIO_PORTD_DATA_R &= (~(1<<2));		//Turn OFF the En of LCD
}

void LCD_Cmd(unsigned char cmd){
	Printdata(cmd);										//Pass the 8 Bit data to the datalines of LCD
	Generic_delay(1);
	GPIO_PORTD_DATA_R &= (~(1<<1));		//Turn OFF the RW for write operation in LCD
	Generic_delay(1);
	GPIO_PORTD_DATA_R &= (~(1<<0));		//Turn OFF the RS for writing to the data register of LCD
	Generic_delay(1);
	GPIO_PORTD_DATA_R |= (1<<2);			//Turn ON the En of LCD for enabling the clock of LCD
	Generic_delay(10);			//Wait for sometime
	GPIO_PORTD_DATA_R &= (~(1<<2));		//Turn OFF the En of LCD
}


//to print a String which is array of char we will call LCD_Data until we print all the String

void LCD_String(unsigned char *str , unsigned char len){
	char i;
	for(i=0 ; i<len ; i++){
		LCD_Data(str[i]);
		}
}
void LCD_Init(void){
	Generic_delay(1);
		LCD_Cmd(0x38);		//Turn ON 8 Bit Mode
	Generic_delay(1);
	LCD_Cmd(0x38);      //making sure
	Generic_delay(1);
	LCD_Cmd(0x38);      //making sure again
	Generic_delay(1);
	LCD_Cmd(0x08);      //turn off display
	Generic_delay(1);
		LCD_Cmd(0x06);		//Auto increment the cursor when prints the data in current
	Generic_delay(1);
		LCD_Cmd(0x01);		//Clear Screen
	Generic_delay(1);
	LCD_Cmd(0x0C);		//Cursor OFF and display ON
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

	
	Generic_delay(10);
	LCD_Init();
	Generic_delay(1);
	LCD_Cmd(0x80);				// cursor to first row and first column
	Generic_delay(1);
	LCD_Data('A');
	Generic_delay(1);
	LCD_Cmd(0xC0);
	Generic_delay(1);
	LCD_String( arr,5 );
	
		
	while(1){
		

	}
return 0 ;
}
