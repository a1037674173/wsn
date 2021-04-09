#ifndef _LCD1331_H_
#define _LCD1331_H_
#include <ioCC2530.h>

#define uchar unsigned char
#define uint unsigned int

#include "codetab.h"


//当前字体的颜色
uint hz_clor=0x001f;

void DelayMS(unsigned int msec)
{ 
    unsigned int i,j;
    
    for (i=0; i<msec; i++)
        for (j=0; j<600; j++);
}

void write_com(unsigned char data1)
{
    uchar i;
    LCD_DC=0;  

    for(i=0;i<8;i++)
    {
        LCD_SCL = 0;    
        if (data1 & 0x80)
        {
          LCD_SDA = 1;
        }
        else
        {
          LCD_SDA = 0;
        }

        LCD_SCL = 1; 
        data1 <<= 1;    
    }
}

void write_dat(unsigned char data1)
{
    uchar i;
    LCD_DC= 1;
   
    for(i=0;i<8;i++)
    {
        LCD_SCL = 0;    
        if (data1 & 0x80)
        {
          LCD_SDA = 1;
        }
        else
        {
          LCD_SDA = 0;
        }
        

        LCD_SCL = 1;
        data1 <<= 1;    
    }
}

void RAM_ADDRESS(void)
{ 
  write_com(0x15);
  write_com(0x00);
  write_com(0x5f);

  write_com(0x75);
  write_com(0x00);
  write_com(0x3f);

}

//全屏清屏  黑色
void LCD_Clear()
{
 int i,j;
 RAM_ADDRESS();
 for(i=0;i<96;i++) 
  {
    for(j=0;j<64;j++)
     {
      write_dat(0x00);//RAM data write
      write_dat(0x00);//RAM data write
     }
  }
}

void set_address(uchar row,uchar column)
{
  if(row>63) return;
  if(column>127) return;
  
  write_com(0x15);	  
  write_com(column);	//X start 
  write_com(column);	//X end 

  write_com(0x75);	
  write_com(row);	//Y start 
  write_com(row+7);	//Y end 			
}

void transfer_data(uchar data1) 
{
  uchar i; 
  uchar clorh=hz_clor>>8; 
  uchar clorl=hz_clor&0x00ff;

  for(i=0;i<8;i++)
  {
    if (data1& 0x01)	
    { 	
      write_dat(clorh);   //设置字体颜色
      write_dat(clorl);
    }
    else  			
    {
      write_dat(0x00);   //设置背景黑色
      write_dat(0x00);
    }

    data1>>= 1;
  }
}

void LCD_DrawBmp(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1, unsigned char* BMP)
{
  uint index=0;
  uint x=0,y;
  uint i=0;

  for(y=y0; y<y1; y++)
  {
    for(i=0; i<8; i++)
    {
      for(x=x0; x<x1; x++)
      {
          set_address(y*8+i,x);
          index=((y-y0)*8+i)*(x1-x0)*2+(x-x0)*2;
          write_dat(gImage_t[index]);
          write_dat(gImage_t[index+1]);
      }
    }
  }
}

void LCD_Init()
{
  IO_INIT();//IO口初始化
  LCD_RST=0;
  DelayMS(10);
  LCD_RST=1;
  DelayMS(10);

  
  write_com(0xfd);	// command lock
  write_com(0x12);
  write_com(0xae);	// display off
  write_com(0xa4); 	// Normal Display mode
  
  write_com(0x15);	//set column address
  write_com(0x00);	//column address start 00
  write_com(0x5f);	//column address end 95
  write_com(0x75);	//set row address
  write_com(0x00);	//row address start 00
  write_com(0x3f);	//row address end 63	
  
  write_com(0x87);	//master current control
  write_com(0x03);	//9/16(160uA)---??????,????(0x0a)
  
  write_com(0x83);	//Set Contrast for Color R
  write_com(0xA0);
  write_com(0x82);	//Set Contrast for Color G
  write_com(0xA0);
  write_com(0x81);	//Set Contrast for Color B
  write_com(0xA0);
  
  write_com(0x8a);
  write_com(0x61);
  write_com(0x8b);
  write_com(0x62);
  write_com(0x8c);
  write_com(0x63);
  
  write_com(0xa0);	//set re-map & data format
  write_com(0x72);	//Horizontal address increment
  
  write_com(0xa1);	//set display start line
  write_com(0x00);	//start 00 line
  write_com(0xa2);	//set display offset
  write_com(0x00);
  write_com(0xa8);	//set multiplex ratio
  write_com(0x3f);	//64MUX

  
  write_com(0xad);  
  write_com(0x8f);
  
  
  
  write_com(0xb0);	//set power save
  write_com(0x00);	//
  
  write_com(0xb1);
  write_com(0x11);	// Phase 2 period Phase 1 period  ???????
  write_com(0xb3);	// Set Display Clock Divide Ratio/ Oscillator Frequency
  write_com(0xF0);	// 0.97MHZ
  
  write_com(0xbb);	// set pre-charge
  write_com(0x3e);	// ---??????????
  write_com(0xbe);	//set Vcomh
  write_com(0x3e);	//0.83Vref
  
  
  
  write_com(0xad);	//Select external VCC supply at Display ON
  write_com(0x8e); 	//Select External VP voltage supply
  
  LCD_Clear();
  write_com(0xaf);	 //display on
  
}

void display_clor(uchar clor1,uchar clor2)
{
  int i,j;
  RAM_ADDRESS();
  for(i=0;i<96;i++) 
  {
    for(j=0;j<64;j++)
    {
      write_dat(clor1);//RAM data write
      write_dat(clor2);//RAM data write
    }
  }
}


void SetColor(uchar y)
{
    //每行字的颜色
    if(y==0||y==1)
    {
      hz_clor=0x001f;  //蓝色
    }
    else if(y==2||y==3)
    {
      hz_clor=0xf81f;  //紫色
    }
    else if(y==4||y==5)
    {
      hz_clor=0xf800;  //红色
    }
    else if(y==6||y==7)
    {
      hz_clor=0x07e0;  //绿色
    }
    else
    {
      hz_clor=0xf81f;  //紫色
    }
}


/***************功能描述：显示5*8一组标准ASCII字符串    显示的坐标（x,y），y为页范围0～7****************/
void LCD_P6x8Str(unsigned char x, unsigned char y,unsigned char text[])
{
  uint i=0,j,k,disp_data;
  uchar reverse=0;//1表示反显

  SetColor(y);
  while(text[i]>0x00)
  {	
    if((text[i]>=0x20)&&(text[i]<=0x7e))
    {
      j=text[i]-0x20;

      for(k=0;k<6;k++)
      {
        if(reverse==1)
        {
          disp_data=~F6x8[j][k];
        }
        else
        {
          disp_data=F6x8[j][k];
        }
        set_address(y*8,x+k);
        transfer_data(disp_data);	//写数据到LCD,每写完1字节的数据后列地址自动加1
      }
            
      i++;
      x+=6;
      if(x>91)
      {
        x=1;
      }
    }
    else
    {
      i++;
    }
  }
}

/***************功能描述：显示5*8一组标准ASCII字符串 显示的坐标（x,y），y为页范围0～7****************/
void display_string_8x16(uchar x,uchar y,uchar *text)
{
	uint i=0,j,k,n;
	if(x>89)
	{
		x=1;

	}
	while(text[i]>0x00)
	{	
		if((text[i]>=0x20)&&(text[i]<=0x7e))
		{
			j=text[i]-0x20;
			for(n=0;n<2;n++)
			{			
				for(k=0;k<8;k++)
				{					
					set_address(n*8+y*8,x+k);
          transfer_data(F8X16[j*16+k+8*n]);	//写数据到LCD
				}
			}
			i++;
			x+=8;
		}
		else
		i++;
	}
}

/***************功能描述：显示16*16汉字 显示的坐标（x,y），y为页范围0～7****************/
void display_string_16x16(uchar x,uchar y,uchar *text)
{
  uchar i,j,k;
  uint address; 
  unsigned char* addr=0;

  j = 0;
  while(text[j] != '\0')
  {
    i = 0;
    address = 1;
    addr=getChineseCode(text);//取出汉字编码首地址

    for(k=0;k<2;k++)
    {  			
      for(i = 0; i < 16; i++)               
      {
        set_address(k*8+y*8,x+i);
        transfer_data(addr[address]);     
        address++;
      }
    }
    j += 2;
    x+=16;
  }
}


/***************功能描述：显示8*16或者16*16一组混合字符串    显示的坐标（x,y），y为页范围0～7****************/
void LCD_TextOut(uchar x,uchar y, uchar *text)
{
    uchar temp[3];
    uchar i = 0;    

    SetColor(y);
    while(text[i] != '\0')
    {
        if(text[i] > 0x7e)
        {
            temp[0] = text[i];
            temp[1] = text[i + 1];
            temp[2] = '\0';          //汉字为两个字节
            display_string_16x16(x,y,temp);  //显示汉字
            x += 16;
            i += 2;
        }
        else
        {
            temp[0] = text[i];    
            temp[1] = '\0';          //字母占一个字节
            display_string_8x16(x, y, temp);  //显示字母
            x += 8;
            i++;
        }
    }
}

#endif
