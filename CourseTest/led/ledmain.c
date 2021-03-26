#include "ioCC2530.H"
#include "exboard.h"

void delay(int n)
{
  int i;
  for(i=0;i<n;i++);
  for(i=0;i<n;i++);
  for(i=0;i<n;i++);
  for(i=0;i<n;i++);
  for(i=0;i<n;i++);
  for(i=0;i<n;i++);
}
void main(void)
{
  //P0SEL &= ~0x01;
  P0SEL &= ~0x02;
  P0DIR &= ~0x02;

  P2SEL &= ~0x01;
  P2DIR &= ~0x01;
  P2INP |= ~0x01;

  P1SEL &=~0x03;// led1 P1_0
  P1DIR |=0x03;

  while(1)
  {
    led1=0;
    led2=0;
    while(1)
    {
      if(key2==0)
      {
        if(key2==0)
        {
          while(key2==0);
          led1=!led1;
          led2=!led2;
        }
      }
    }
  }
}