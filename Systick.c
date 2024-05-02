#include "tm4c123gh6pm.h"
#include "io.h"
#include <stdint.h>

void TIMER_INIT(void)
{
  NVIC_ST_CTRL_R = 0 ;
  NVIC_ST_RELOAD_R = 0X00FFFFFF;
  NVIC_ST_CURRENT_R = 0;
  NVIC_ST_CTRL_R = 0X05 ;
}
void WAIT_FOR_10MS(uint32_t delay)
{
  NVIC_ST_RELOAD_R = (delay -1);
  while((NVIC_ST_CTRL_R & 0x10000) ==0 ); 
}
void number_of_10ms (uint32_t n)
{
  uint32_t i ;
  for(i=1;i<=n;i++)
  {
    WAIT_FOR_10MS(160000);
  }
}