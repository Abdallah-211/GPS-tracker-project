#include "io.h"

void RGB_INIT (void)
{
    SYSCTL_RCGCGPIO_R |= 0x20;
    while((SYSCTL_PRGPIO_R & PF_mask) == 0);
    GPIO_PORTF_LOCK_R   = GPIO_LOCK_KEY;
    GPIO_PORTF_CR_R    |= PF123_mask;
    GPIO_PORTF_AMSEL_R &= ~ PF123_mask;
    GPIO_PORTF_AFSEL_R &= ~ PF123_mask;
    GPIO_PORTF_PCTL_R  &= ~ 0xFFF0;
    GPIO_PORTF_DIR_R   |= PF123_mask;
    GPIO_PORTF_DEN_R   |= PF123_mask;
    GPIO_PORTF_DATA_R  &= ~ PF123_mask;
}
void SW_INITI (void) 
{
    GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
    GPIO_PORTF_CR_R    |= 0x11 ;
    GPIO_PORTF_AMSEL_R &= ~ 0x11 ;
    GPIO_PORTF_AFSEL_R &= ~ 0x11;
    GPIO_PORTF_PCTL_R  &= ~0xF000F;
    GPIO_PORTF_DIR_R   &= ~ 0X11 ;
    GPIO_PORTF_DEN_R   |= 0X11 ;
    GPIO_PORTF_PUR_R    = 0X11 ;
}
unsigned char SW1_Input (void) {
return GPIO_PORTF_DATA_R & 0x10;
}
unsigned char SW2_Input (void) {
return GPIO_PORTF_DATA_R & 0x1;
}

void LEDs_output(unsigned char data){
GPIO_PORTF_DATA_R |= data;
}
void LEDs_Clear(void){
GPIO_PORTF_DATA_R &= ~0x0E;
}