#include "tm4c123gh6pm.h"
#include <string.h>
#include <stdint.h>

#define CR 0x0D



//*****************************************************************************
//
// UART0
//
//*****************************************************************************
void UART0_Init(void){
    
    SYSCTL_RCGCUART_R |= 0x0001;
  SYSCTL_RCGCGPIO_R |= 0X0001;
    while((SYSCTL_PRGPIO_R & 0x01) == 0){}
    UART0_CTL_R =~UART_CTL_UARTEN;
    UART0_IBRD_R = 104;
    UART0_FBRD_R = 11;
    UART0_LCRH_R |= 0x70;
    UART0_CTL_R |= 0x301;
    GPIO_PORTA_DEN_R |= 0x03;
    GPIO_PORTA_AFSEL_R |= 0x03;
    GPIO_PORTA_AMSEL_R &= ~0x03;
    GPIO_PORTA_PCTL_R |= (GPIO_PORTA_PCTL_R&~0XFF)|(0X11);
    
}
void UART0_WriteChar(unsigned char ch)   //function to write char
{
    while((UART0_FR_R&0X20)!=0){}
        UART0_DR_R = ch;    
}

unsigned char UART0_ReadChar(void){                                //function that Read Char
    while((UART0_FR_R&0X10) != 0){}
    return (UART0_DR_R&0xFF);
}
void UART0_ReadString(char *str , int len){                    //Read String 
   
     int i;
     char c;
	for(i=0;i<len;i++){
	  c = UART0_ReadChar(); 
		if(c!=CR){
		*str = c;
		str++;
		UART0_WriteChar(c);
		}
		else if(c==CR || i==len) break;
	}	
}


	
    void printStr0(char *str){     //Print String
        while(*str){
            UART0_WriteChar(*str);
            str++;
        }
    }
//*****************************************************************************
//
// UART1
//
//*****************************************************************************


void UART1_Init(void){
SYSCTL_RCGCUART_R |= 0x0002;
SYSCTL_RCGCGPIO_R |= 0X0002;
while((SYSCTL_PRGPIO_R & 0x02) == 0){}
UART1_CTL_R =~UART_CTL_UARTEN;
UART1_IBRD_R=104;
UART1_FBRD_R=11;
UART1_LCRH_R |= 0x70;
UART1_CTL_R |= 0x301;
GPIO_PORTB_DEN_R |= 0x03;
GPIO_PORTB_AFSEL_R |= 0x03;
GPIO_PORTB_AMSEL_R &= ~0x03;
GPIO_PORTB_PCTL_R |= (GPIO_PORTB_PCTL_R&~0XFF)|(0X11);
}


void UART1_WriteChar(unsigned char ch)   //function to write char
{
	while((UART1_FR_R&0x20)!=0){}
		UART1_DR_R = ch;	
}

unsigned char UART1_ReadChar(void){								//function that Read Char
	while((UART1_FR_R&0x10) != 0){}
	return (UART1_DR_R&0xFF);
}


void UART1_ReadString(char *str , int len)	      	//Read String
{	

	int i;
	char c;
	for(i=0;i<len;i++){
	 c = UART1_ReadChar();
		if(c!=CR){
		*str = c;
		str++;
		UART1_WriteChar(c);
		}
		else if(c==CR || i==len) break;
	}
}
 void printStr1(char *str){       //Print String
        while(*str){
            UART1_WriteChar(*str);
            str++;
        }
    }
//*****************************************************************************
//
// UART5
//
//*****************************************************************************

void UART5_Init(){
    SYSCTL_RCGCUART_R |= 0x0020;
    SYSCTL_RCGCGPIO_R |= 0X10;
	while((SYSCTL_PRGPIO_R & (0x01<<4)) == 0){}
  UART5_CTL_R =~UART_CTL_UARTEN;
	UART5_IBRD_R = 104;
	UART5_FBRD_R = 11;
	UART5_LCRH_R |= 0x70;
	UART5_CTL_R |= 0x301;
	GPIO_PORTE_DEN_R |= 0x30;
	GPIO_PORTE_AFSEL_R |= 0x30;
	GPIO_PORTE_AMSEL_R &= ~0x30;
	GPIO_PORTE_PCTL_R |= (GPIO_PORTE_PCTL_R&~0XFF)|(0X11);
	
}
void UART5_WriteChar(unsigned char ch){						//Write Char
	while((UART5_FR_R&0x20) != 0){}
	UART5_DR_R = ch;
}

unsigned char UART5_ReadChar(void){								//Read Char
	while((UART5_FR_R&0x10) != 0){}
	return UART5_DR_R&0xFF;
}

void UART5_ReadString(char *str , int len)	      	//Read String
{	

	int i;
	 char c;
	for(i=0;i<len;i++){
	  c = UART5_ReadChar();
		if(c!=CR){
		*str = c;
		str++;
		UART5_WriteChar(c);
		}
		else if(c==CR || i==len) break;
	}
}
 void printStr5(char *str){       //Print String
        while(*str){
            UART5_WriteChar(*str);
            str++;
        }
    }

//*****************************************************************************
//
// UART7
//
//*****************************************************************************

void UART7_Init(){
	
	SYSCTL_RCGCUART_R |= 0x0080;
    SYSCTL_RCGCGPIO_R |= 0X0010;
	while((SYSCTL_PRGPIO_R & (0x01<<4)) == 0){}
	UART7_CTL_R =~UART_CTL_UARTEN;
	UART7_IBRD_R = 104;
	UART7_FBRD_R = 11;
	UART7_LCRH_R |= 0x70;
	UART7_CTL_R |= 0x301;
	GPIO_PORTE_DEN_R |= 0x03;
	GPIO_PORTE_AFSEL_R |= 0x03;
	GPIO_PORTE_AMSEL_R &= ~0x03;
	GPIO_PORTE_PCTL_R |= (GPIO_PORTE_PCTL_R&~0XFF)|(0X11);
	
}
void UART7_WriteChar(unsigned char ch){						//Write Char
	while((UART7_FR_R&0x02) != 0){}
	UART7_DR_R = ch;
}

unsigned char UART7_ReadChar(void){								//Read Char
	while((UART7_FR_R&0x01) != 0){}
	return UART7_DR_R&0xFF;
}

void UART7_ReadString(char *str , int len)	      	//Read String
{	
 
	int i;
	 char c;
	for(i=0;i<len;i++){
		c = UART7_ReadChar();
		if(c!=CR){
		*str = c;
		str++;
		UART7_WriteChar(c);
		}
		else if(c==CR || i==len) break;
	}
}
 void printStr7(char *str){       //Print String
        while(*str){
            UART7_WriteChar(*str);
            str++;
        }
    }
