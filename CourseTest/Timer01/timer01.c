#include <ioCC2530.h>
#include "exboard.h"

uint counter=0;	//统计t1溢出次数
uint counter1=0;//统计t3溢出次数
               //初始化函数声明
void Init_T1(void)
{
  P1SEL &= ~0x03;
  P1DIR = 0x03; 	
   	

    CLKCONCMD &= ~0x7f;                //晶振设置为32MHZ
    while(CLKCONSTA & 0x40);           //等待晶振稳定


    EA = 1;                           //开中断
    T1IE = 1;                         //开T1溢出中断
    T1CTL =0x05;                     //启动，设8分频，设自由模式

    led1=1;
    led2=0;
}

/***************************
//主函数
***************************/
void main()
{
	Init_T1();
        T3IE = 1;
        T3CTL=0x7C;               //T3启动，设8分频，设自由模式
        
       	while(1)   	         //查询溢出
	{

	}
}
#pragma vector = T1_VECTOR
 __interrupt void T1_ISR(void)
 {
 	IRCON = 0x00;			  //清中断标志,也可由硬件自动完成
        if(counter<300)
           counter++;	                 //300次中断LED闪烁一轮（约为5秒时间）
        else
        {
         counter = 0;                    //计数清零
         led1 = !led1;	           //闪烁标志反转
        }
 }
#pragma vector = T3_VECTOR
 __interrupt void T3_ISR(void)
 {
 	IRCON = 0x00;			  //清中断标志,也可由硬件自动完成
        if(counter1<300)
           counter1++;	                 //300次中断LED闪烁一轮（约为5秒时间）
        else
        {
         counter1 = 0;                    //计数清零
         led2 = !led2;	           //闪烁标志反转
        }
 }
