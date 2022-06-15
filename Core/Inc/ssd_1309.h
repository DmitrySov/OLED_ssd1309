/*
 * ssd_1309.h
 *
 *  Created on: 14 апр. 2022 г.
 *      Author: Sovetnikov
 */

 #ifndef SSD_1309_SSD_1309_H_
 #define SSD_1309_SSD_1309_H_

 /* Includes ------------------------------------------------------------------*/
 //#include "ssd_1309.h"
 #include "main.h"
 #include "stm32f4xx_hal.h"
 #include <stdbool.h>
 #include <string.h>
 #include "font_16.h"
 #include "font_14.h"
 #include "font_8.h"
 #include "fonts.h"



 /* Declarations and definitions ----------------------------------------------*/
 #define SSD1309_X_SIZE                                128
 #define SSD1309_Y_SIZE                                64
 #define SSD1309_BUFFER_SIZE                          (SSD1309_X_SIZE *  SSD1309_Y_SIZE) / 8

#define SSD1309_WIDTH            128
#define SSD1309_HEIGHT           64
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Private SSD1309 structure */
typedef struct {
	uint16_t CurrentX;
	uint16_t CurrentY;
} SSD1309_t;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Functions -----------------------------------------------------------------*/
 void SSD1309_init(void);
 void LL_GPIO_WriteOutputPort(GPIO_TypeDef *GPIOx, uint32_t PortValue);
 void Reset_ssd1309(void);
 void SendCommand(uint8_t Data);
 void SendData (uint8_t Data);
 void Clear_Screen(void);
 void Clear_Sector_x_y(uint8_t x1, uint8_t x2, uint8_t y1, uint8_t y2);
 void Init_sector(uint8_t x1, uint8_t x2, uint8_t y1, uint8_t y2);
 void Output_Char_16pt(uint8_t out_char);
 void Output_Char_14pt(char out_char);
 /***Test******/
 void Output_Char_14pt_Test_russian(uint8_t out_char);
 /************/
 void Output_Char_8pt(uint8_t out_char);
 void Output_String_16pt(const char *string);
 void Output_String_14pt(const char *string);
 void Output_String_8pt(const char *string);
 void SSD1309_DrawFilledRect(uint8_t xStart, uint8_t xEnd, uint8_t yStart, uint8_t yEnd);
 void SSD1309_ClearScreen(void);
 void SSD1309_UpdateScreen(void);
 void SSD1309_UpdateScreen_new(void);
 void Cursor_Screen(void);

 char SSD1309_WriteString(char* str, FontDef_t* Font);
 char SSD1309_WriteChar(char ch, FontDef_t* Font);
 void SSD1309_GotoXY(uint16_t x, uint16_t y);

 void ssd1309_DrawCircle(uint8_t par_x,uint8_t par_y,uint8_t par_r);

 #endif /* SSD_1309_SSD_1309_H_ */
