#include "ioCC2530.H"
#include "exboard.h"

void main(void)
{
  P0SEL &= ~0x02;
  P0INP |= 0x02;  //上拉  0000 0010
  P0IEN |= 0x02;  //P01 设置为中断方式 1  中断使能
  PICTL |= 0x02;  //下降沿触发
  
  EA=1;
  IEN1 |= 0x20;  //P0设置为中断方式
  P0IFG |=0x00; //初始化中断标志位
  
  P1SEL &= ~0x13;
  P1DIR |= 0x13;

  led1=1;
  led2=0;
  
  while(1)
  {
  }
}

#pragma vector = P0INT_VECTOR
__interrupt void P0_ISR(void)
{
  if(P0IFG>0)
  {
    led1=!led1;
    led2=!led2;
    P0IFG=0;
    P0IF=0;
  }
}
