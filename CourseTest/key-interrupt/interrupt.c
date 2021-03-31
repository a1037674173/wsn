 #include <ioCC2530.h>
 #include "exboard.h"


void main()
{
 //KEY1  KEY2 配置
  
  P0SEL &= ~0X02;//0000 0010
  P0INP |= 0x02; //上拉 00000010  
  P0IEN |= 0x02;   //P0—1设置为中断方式 1 中断使能 P2IEN |=0X01
  P2IEN |=0X01;
  PICTL |= 0X02;   //下降沿触发0000 0010  PICTL |=OX01

  EA = 1;
   IEN1 |= 0X20;  // P0设置为中断方式使能;0010 0000  IEN2 |=0X02
   IEN2 |=0X02;
  P0IFG |= 0x00;   //初始化中断标志位 P2IFG |=0X00
  P2IFG |=0X00;

 // P1SEL &= ~0xc0; //设置led
 // P1DIR|=0xC0;
 P1SEL &=~0x13;
 P1DIR |=0x13;
 
  led1=1;
  led2=0;
   while(1)
   {


   }

}
#pragma vector = P0INT_VECTOR   //端口P0的中断处理函数
 __interrupt void P0_ISR(void)
 {
    if(P0IFG>0)            //按键中断 P2IFG
   {
       led1=!led1;
       led2=!led2;

       P0IFG = 0;          //清除P0_0中断标志
       P0IF = 0;           //清除P0中断标志


    }

 }
#pragma vector = P2INT_VECTOR    //端口P2的中断处理函数
 __interrupt void P2_ISR(void)
 {
    if(P2IFG>0)            //按键中断 P2IFG
   {
       led1=!led1;
       led2=!led2;

       P2IFG = 0;          //清除P0_0中断标志
       P2IF = 0;           //清除P0中断标志


    }

 }