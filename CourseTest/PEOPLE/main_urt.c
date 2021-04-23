#include "ioCC2530.h"
#include <string.h>


#define LED_1 P1_0
#define LED_2 P1_1
#define SIGNAL P0_4
#define uchar unsigned char
#define uint unsigned int

void Delay(uint n)
{
  for (uint i = 0; i < n; i++);
  for (uint i = 0; i < n; i++);
  for (uint i = 0; i < n; i++);
  for (uint i = 0; i < n; i++);
  for (uint i = 0; i < n; i++);
  for (uint i = 0; i < n; i++);
}
void initUART0(void)
{
    CLKCONCMD &= ~0x40;                         //设置系统时钟源为32MHZ晶振
    while(CLKCONSTA & 0x40);                    //等待晶振稳定
    CLKCONCMD &= ~0x47;                         //设置系统主时钟频率为32MHZ

    PERCFG = 0x00;				//位置1 P0口
    P0SEL = 0x2c;				//P0用作串口
    P2DIR &= ~0XC0;                             //P0优先作为UART0
    U0CSR |= 0x80;				//串口设置为UART方式
    U0GCR |= 9;				
    U0BAUD |= 59;				//波特率设为19200
    UTX0IF = 1;                                 //UART0 TX中断标志初始置位1
    U0CSR |= 0X40;				//允许接收
    IEN0 |= 0x84;				//开总中断，接收中断
}
/****************************************************************
串口发送字符串函数				
****************************************************************/
void UartTX_Send_String(uchar *Data,int len)
{
  uint j;
  for(j=0;j<len;j++)
  {
    U0DBUF = *Data++;
    while(UTX0IF == 0);
    UTX0IF = 0;
  }
}

void initPeople(void)
{
  P1SEL &= ~0x03;
  P1DIR |= 0x03;
  
  P0SEL &= ~0x10;
  P0DIR &= ~0x10;
}
void main(void)
{

  initPeople();
  initUART0();
  
  // P0SEL &= ~0x10;P2INP |= 0X20; 		// P0_4设置成通用IO 即第四位为0， 所以 与上1110 1111

  while(1)
  {
    if (SIGNAL)
    {
      LED_1 = 1;
      LED_2 = 1;
      UartTX_Send_String(" leave ", 8);
      Delay(10000);
    }
    else
    {
      LED_1 = 0;
      LED_2 = 0;
      UartTX_Send_String(" coming ", 8);
      Delay(10000);
    }
  }
}