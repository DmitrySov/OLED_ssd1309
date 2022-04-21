/*
 * ssd_1309.h
 *
 *  Created on: 14 апр. 2022 г.
 *      Author: sovetnikov
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

 /* Declarations and definitions ----------------------------------------------*/
 #define SSD1309_X_SIZE                                128
 #define SSD1309_Y_SIZE                                64
 #define SSD1309_BUFFER_SIZE                          (SSD1309_X_SIZE *  SSD1309_Y_SIZE) / 8


#define SSD1306_WIDTH            128
#define SSD1306_HEIGHT           64


//static uint8_t pixelBuffer[SSD1306_BUFFER_SIZE];
/* Functions -----------------------------------------------------------------*/
 void SSD1309_init();
 void Write_OLED(uint8_t data);
 void LL_GPIO_WriteOutputPort(GPIO_TypeDef *GPIOx, uint32_t PortValue);
 void Reset_ssd1309(void);
 void SendCommand(uint8_t Data);
 void SendData (uint8_t Data);
 void Clear_Screen(void);
 void Update_Sreen(void);
 void Write_ScreenBuf(void);
 //static void SetPixel(uint8_t x, uint8_t y);
 void Output_Char_16pt(uint8_t out_char);
 void Output_String(const char *string);
 void SSD1309_DrawFilledRect(uint8_t xStart, uint8_t xEnd, uint8_t yStart, uint8_t yEnd);
 void SSD1306_DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
 void SSD1306_DrawPixel(uint16_t x, uint16_t y);
 void init_sector(uint8_t x1, uint8_t x2, uint8_t y1, uint8_t y2);
 void Clear_Sector_x_y(uint8_t x1, uint8_t x2, uint8_t y1, uint8_t y2);

 #endif /* SSD_1309_SSD_1309_H_ */
