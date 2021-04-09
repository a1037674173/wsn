/****************************************************************************
* 文 件 名: main.c
* 描    述: OLED显示
****************************************************************************/

//如果使用彩屏，请定义此宏
//#define OLED_1331


#include <ioCC2530.h>
#ifdef OLED_1331
#include "LCD1331.h"
#else
#include "LCD.h"
#endif

void main()
{
    unsigned char i=0; 

    LCD_Init();
    
    while(1)
    {
      LCD_Clear();
      LCD_TextOut(0, 0, "ITT18013");
      LCD_TextOut(0, 2, "陈尚铀");
      LCD_TextOut(0, 4, "QQ:1037674173");
      LCD_TextOut(0, 6, "TEL:18350616098");
      
      //LCD_P6x8Str(0, 0,"ITT18013");
      //LCD_P6x8Str(0, 2,"TEL:18350616098");
      
      while(1);
      //DelayMS(1000);
      //LCD_Clear();
      //LCD_DrawBmp(0,2,128,128, (unsigned char*)gImage_t);
      //DelayMS(1000);
    }
}   

