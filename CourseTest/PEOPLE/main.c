#include "ioCC2530.h"

#define LED_1 P1_0
#define LED_2 P1_1
#define SIGNAL P0_4
#define uchar unsigned char
#define uint unsigned int

void main(void)
{
  P1SEL &= ~0x03;
  P1DIR |= 0x03;
  
  P0SEL &= ~0x10;
  P0DIR &= ~0x10;
    
  while(1)
  {
    if (SIGNAL)
    {
      LED_1 = 1;
      LED_2 = 1;
    }
    else
    {
      LED_1 = 0;
      LED_2 = 0;
    }
  }
}