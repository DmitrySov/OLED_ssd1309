/*
 * ssd_1309.h
 *
 *  Created on: 14 апр. 2022 г.
 *      Author: Sovetnikov
 */

 #ifndef SSD_1309_SSD_1309_H_
 #define SSD_1309_SSD_1309_H_

 /* Includes ------------------------------------------------------------------*/
 #include "main.h"
 #include "stm32f4xx_hal.h"
 #include <stdbool.h>
 #include <string.h>
 #include "font_Times_New_Roman.h"
 #include "font_Arial.h"

 typedef enum
{
	 pt8 = 8,
	 pt10 = 10,
	 pt12 = 12,
	 pt14 = 14,
	 pt16 = 16,
}fontSize;

/* Declarations and definitions ----------------------------------------------*/
#define SSD1309_X_SIZE                                128
#define SSD1309_Y_SIZE                                64
#define SSD1309_BUFFER_SIZE                          (SSD1309_X_SIZE *  SSD1309_Y_SIZE) / 8

#define SSD1309_WIDTH            128
#define SSD1309_HEIGHT           64

#define SSD1306_X_OFFSET_LOWER 0
#define SSD1306_X_OFFSET_UPPER 0

#define D0_Pin 						GPIO_PIN_0
#define D0_GPIO_Port 				GPIOD

#define D1_Pin 						GPIO_PIN_1
#define D1_GPIO_Port 				GPIOD

#define D2_Pin 						GPIO_PIN_2
#define D2_GPIO_Port 				GPIOD

#define D3_Pin 						GPIO_PIN_3
#define D3_GPIO_Port 				GPIOD

#define D4_Pin 						GPIO_PIN_4
#define D4_GPIO_Port 				GPIOD

#define D5_Pin 						GPIO_PIN_5
#define D5_GPIO_Port 				GPIOD

#define D6_Pin 						GPIO_PIN_6
#define D6_GPIO_Port 				GPIOD

#define D7_Pin 						GPIO_PIN_7
#define D7_GPIO_Port 				GPIOD

#define RD_E_Pin 					GPIO_PIN_3
#define RD_E_GPIO_Port 				GPIOB

#define WR_Pin 						GPIO_PIN_4
#define WR_GPIO_Port				GPIOB

#define CS_Pin 						GPIO_PIN_5
#define CS_GPIO_Port 				GPIOB

#define D_C_Pin 					GPIO_PIN_6
#define D_C_GPIO_Port				GPIOB

#define RES_Pin 					GPIO_PIN_7
#define RES_GPIO_Port 				GPIOB


#define __WRITE_GPIO(__GPIOx__, __PIN__, __STATE__)	(HAL_GPIO_WritePin(__GPIOx__, __PIN__, __STATE__))

// writing the value to bits 0 - 7
#define __WRITE_bits_0_7(__GPIO__, __Value__)  WRITE_REG(__GPIO__->ODR, __Value__);
/* Private SSD1309 structure */
typedef struct {
	uint16_t CurrentX;
	uint16_t CurrentY;
} SSD1309_t;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Functions -----------------------------------------------------------------*/
 void SSD1309_init(void);
 void Reset_ssd1309(void);
 void SendCommand(uint8_t Data);
 void SendData (uint8_t Data);

 void Init_sector(uint8_t x1, uint8_t x2, uint8_t y1, uint8_t y2);

 void SSD1309_ClearScreen(void);
 void SSD1309_Fill(void);
 void SSD1309_Clear(void);

 void SSD1309_UpdateScreen(void);
 void SSD1309_UpdateScreen_1(void);
 void Cursor_Screen(void);

 void Output_Char_16pt(uint8_t out_char);
 void Output_String_16pt(const char *string);

 void SSD1309_GotoXY(uint16_t x, uint16_t y);

 void SSD1309_DrawFilledRect(uint8_t xStart, uint8_t xEnd, uint8_t yStart, uint8_t yEnd);
 void ssd1309_DrawCircle(uint8_t par_x,uint8_t par_y,uint8_t par_r);

 void Output_Char_TimesNewRoman(char out_char, fontSize PtType);
 void Output_String_TimesNewRoman(const char *string, fontSize PtType);

 void Output_Char_Arial(char out_char, fontSize PtType);
 void Output_String_Arial(const char *string, fontSize PtType);
 #endif /* SSD_1309_SSD_1309_H_ */
