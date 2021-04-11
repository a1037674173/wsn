//BY QIUJIE TECH.INC.

#include <ioCC2530.h>
#include <string.h>
#include "exboard.h"


//函数声明
void Delay(uint);
void initUARTSEND(void);
void UartTX_Send_String(char *Data,int len);

char Txdata[25];
/****************************************************************
    延时函数											
****************************************************************/
void Delay(uint n)
{
	uint i;
	for(i=0;i<n;i++);
	for(i=0;i<n;i++);
	for(i=0;i<n;i++);
	for(i=0;i<n;i++);
	for(i=0;i<n;i++);
}
/****************************************************************
   串口初始化函数				
****************************************************************/
void initUARTSEND(void)
{

    CLKCONCMD &= ~0x40;                          //设置系统时钟源为32MHZ晶振
    while(CLKCONSTA & 0x40);                     //等待晶振稳定
    CLKCONCMD &= ~0x47;                          //设置系统主时钟频率为32MHZ


    PERCFG = 0x00;				//USART 0使用位置1 P0_2,P0_3口
    P0SEL = 0x3C;				//P0_2,P0_3,P0_4,P0_5用作串口


    U0CSR |= 0x80;				//UART方式
    U0GCR |=9;				
    U0BAUD |= 59;				//波特率设为19200
    UTX0IF = 0;                                 //UART0 TX中断标志初始置位0
}
/****************************************************************
串口发送字符串函数			
****************************************************************/
void UartTX_Send_String(char *Data,int len)
{
  int j;
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
	uchar i;
       	
	initUARTSEND();
	
        strcpy(Txdata,"HELLO ");       //将字符串HELLO赋给Txdata;
	while(1)
	{
           UartTX_Send_String(Txdata,sizeof("HELLO ")); //串口发送数据
           Delay(5000);
	}
}