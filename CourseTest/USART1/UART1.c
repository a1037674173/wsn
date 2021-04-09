//BY QIUJIE TECH.INC

#include <iocc2530.h>
#include <string.h>
#include "exboard.h"

void initUART0(void);
void InitialAD(void);
void UartTX_Send_String(uchar *Data,int len);

uchar str1[20]="What is your name? ";
uchar str2[7]="hello ";
uchar Recdata[20];
uchar RXTXflag = 1;
uchar temp;
uint  datanumber = 0;
uint  stringlen;
/****************************************************************
初始化串口0函数					
****************************************************************/
void initUART0(void)
{
    P1SEL &= 0x03;
    P1DIR |= 0x03;
  
    CLKCONCMD &= ~0x40;                         //设置系统时钟源为32MHZ晶振
    while(CLKCONSTA & 0x40);                    //等待晶振稳定
    CLKCONCMD &= ~0x47;                         //设置系统主时钟频率为32MHZ

    PERCFG = 0x00;				//位置1 P0口
    P0SEL = 0x3c;				//P0用作串口
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
/****************************************************************
主函数							
****************************************************************/
void main(void)
{	
	P1DIR = 0x03; 				//P1控制LED
	initUART0();

	UartTX_Send_String(str1,20);	
	while(1)
	{
          if(RXTXflag == 1)			     //接收状态
          {

            if( temp != 0 )
            {
                if((temp!='#')&&(datanumber<20))     //’＃‘被定义为结束字符，最多能接收20个字符
                {
                 Recdata[datanumber++] = temp;
                 if (temp == '1')
                 {
                   // LED_1 on
                   LED_1 = 0;
                 } else if (temp == '2')
                 {
                   // LED_2 on
                   LED_2 = 0;
                 } else if (temp == '3')
                 {
                   // LED_1 off
                   LED_1 = 1;
                 } else if (temp == '4')
                 {
                   // LED_2 off
                   LED_2 = 1;
                 }
                }
                else
                {
                  RXTXflag = 3;                      //进入发送状态
                }

              temp  = 0;
            }
          }
          if(RXTXflag == 3)			//发送状态
          {
            		        //发送状态指示
            U0CSR &= ~0x40;			//不能收数
            UartTX_Send_String(str2,6);
            UartTX_Send_String(Recdata,datanumber);
            U0CSR |= 0x40;			//允许接收
            RXTXflag = 1;		        //恢复到接收状态
            datanumber = 0;			//指针归0
            		
          }
	}
}
/****************************************************************
串口接收一个字符:一旦有数据从串口传至CC2530,则进入中断，将接收到的数据赋值给变量temp.
****************************************************************/
#pragma vector = URX0_VECTOR
 __interrupt void UART0_ISR(void)
 {
 	URX0IF = 0;				//清中断标志
	temp = U0DBUF;
 }