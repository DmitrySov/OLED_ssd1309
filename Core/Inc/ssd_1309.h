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

/* SSD1306 data buffer */
//static uint8_t SSD1309_Buffer[SSD1309_WIDTH * SSD1309_HEIGHT / 8];
#define SSD1309_WIDTH            128
#define SSD1309_HEIGHT           64
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Struct to store transformations

typedef struct {
  int16_t MaskX1;
  int16_t MaskY1;
  int16_t MaskX2;
  int16_t MaskY2;
  uint8_t Inverted;
//  uint8_t Dirty;
  /*int16_t Ticks;
  uint8_t Frames;
  uint8_t FPS;*/
} SSD1306_t;

typedef enum {
  SSD1306_BLACK = 0x00,
  SSD1306_WHITE = 0x01
} SSD1306_COLOR_t;

typedef enum {
  SSD1306_OVERRIDE = 0x00,
  SSD1306_TRANSPARENT = 0x01
} SSD1306_DRAW_t;


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
 void Output_Char_14pt(uint8_t out_char);
 void Output_Char_8pt(uint8_t out_char);
 void Output_String_16pt(const char *string);
 void Output_String_14pt(const char *string);
 void Output_String_8pt(const char *string);
 void SSD1309_DrawFilledRect(uint8_t xStart, uint8_t xEnd, uint8_t yStart, uint8_t yEnd);
 void SSD1309_ClearScreen(void);
 void SSD1309_UpdateScreen(void);
 void SSD1309_UpdateScreen_new(void);
 void Cursor_Screen(void);

 void SSD1306_WriteChar(int16_t x, int16_t y, char ch, FontDef_t* Font,  SSD1306_COLOR_t color, SSD1306_DRAW_t mode);
 void SSD1306_DrawPixel(int16_t x, int16_t y, SSD1306_COLOR_t color);

 /*char ssd1306_WriteChar(char ch, FontDef Font);
 char ssd1306_WriteString(char* str, FontDef Font);
 void ssd1306_SetCursor(uint8_t x, uint8_t y);*/

 #endif /* SSD_1309_SSD_1309_H_ */
