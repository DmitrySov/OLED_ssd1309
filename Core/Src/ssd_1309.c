/*
 * ssd-1309.c
 *
 *  Created on: 14 апр. 2022 г.
 *      Author: Sovetnikov
 */
 /* Includes ------------------------------------------------------------------*/
#include "ssd_1309.h"
#include "fonts.h"
#include "font_Times_New_Roman.h"
/* Declarations and definitions ----------------------------------------------*/
static uint8_t pixelBuffer[SSD1309_BUFFER_SIZE] = {0};

/* Functions -----------------------------------------------------------------*/
static void SetPixel(uint8_t x, uint8_t y);

/* Private variable -----------------------------------------------------------------*/
SSD1309_t SSD1309;

/*----------------------------------------------------------------------------------
 * Function:		SSD1309_init
 *----------------------------------------------------------------------------------
 * description:		The OLED display is being initialized,
 * 					with the execution of sending commands to display
 * parameters:		-
 *
 * on return:		-
------------------------------------------------------------------------------------*/

 void SSD1309_init(void)
 {
    Reset_ssd1309();
	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);  // CS = 0
	SendCommand(0xAE);	// display off
	//Clear_Screen();

	SendCommand(0xB0);
	SendCommand(0x81);
	SendCommand(0xC8);			//  яркость;
	//////////////////
	SendCommand(0xC8);		//Remapped (C0h / C8h)
	SendCommand(0x00); //---set low column address
	SendCommand(0x10); //---set high column address
	/////////////////
	SendCommand(0xAF);
	HAL_Delay(100);

	SendCommand(0x20);
	SendCommand(0x00);			//  Horizontal Addressing Mode;
	SendCommand(0x21);			//  Область вывода - от 0 до 127 столбца;
	SendCommand(0x00);
	SendCommand(0x7F);
	SendCommand(0x22);			//  Область вывода - от  до  строки;
	SendCommand(0x00);
	SendCommand(0x07);

	SendCommand(0xA1);

	// Set default values for screen object

	SSD1309.CurrentX = 0;
	SSD1309.CurrentY = 0;
 }
 /*----------------------------------------------------------------------------*/
  /**
    * @brief  Write output data register for the port.
    * @rmtoll ODR          ODy           LL_GPIO_WriteOutputPort
    * @param  GPIOx GPIO Port
    * @param  PortValue Level value for each pin of the port
    * @retval None
    */
   void LL_GPIO_WriteOutputPort(GPIO_TypeDef *GPIOx, uint32_t PortValue)
  {
    WRITE_REG(GPIOx->ODR, PortValue);
  }

/*----------------------------------------------------------------------------------
 * Function:		Reset_ssd1309
 *----------------------------------------------------------------------------------
 * description:		Set the RES# pin LOW value (logical low level), wait at least 3us
 * parameters:		-
 *
 * on return:		-
 ------------------------------------------------------------------------------------*/
 void Reset_ssd1309(void)
 {
 	HAL_GPIO_WritePin(RES_GPIO_Port, RES_Pin, GPIO_PIN_SET);
 	HAL_GPIO_WritePin(RES_GPIO_Port, RES_Pin, GPIO_PIN_RESET);
 	HAL_GPIO_WritePin(RES_GPIO_Port, RES_Pin, GPIO_PIN_SET);
 }
 /*----------------------------------------------------------------------------------
  * Function:		SendCommand
  *----------------------------------------------------------------------------------
  * description:	Сommands are sent with the corresponding command table 9-1 (datasheet)
  * parameters:		-uint8_t Command
  *
  * on return:		-
  ------------------------------------------------------------------------------------*/
 void SendCommand(uint8_t Command)
 {
    HAL_GPIO_WritePin(D_C_GPIO_Port, D_C_Pin, GPIO_PIN_RESET);
 	HAL_GPIO_WritePin(WR_GPIO_Port, WR_Pin, GPIO_PIN_RESET);
 	LL_GPIO_WriteOutputPort(GPIOD, Command);
 	HAL_GPIO_WritePin(WR_GPIO_Port, WR_Pin, GPIO_PIN_SET);
 }
 /*----------------------------------------------------------------------------------
   * Function:		SendData
   *----------------------------------------------------------------------------------
   * description:	Data transmission on the display
   * parameters:	-uint8_t Data
   *
   * on return:		-
   ------------------------------------------------------------------------------------*/
 void SendData (uint8_t Data)
 {
	HAL_GPIO_WritePin(D_C_GPIO_Port, D_C_Pin, GPIO_PIN_SET);
 	HAL_GPIO_WritePin(WR_GPIO_Port, WR_Pin, GPIO_PIN_RESET);
 	LL_GPIO_WriteOutputPort(GPIOD, Data);
 	HAL_GPIO_WritePin(WR_GPIO_Port, WR_Pin, GPIO_PIN_SET);
 }
 /*----------------------------------------------------------------------------------
   * Function:		Clear_Screen
   *----------------------------------------------------------------------------------
   * description:	Сleaning the full display(vertically), pages are cleared first,
   * 				then columns
   * parameters:	-
   *
   * on return:		-
   ------------------------------------------------------------------------------------*/
 void Clear_Screen(void)
 {
	  uint8_t i = 0;
	 for(uint8_t j =0; j < 128; j++)
	     {
	 	  SendCommand(0xB0+i);
	 	  for (uint8_t i = 0; i < 8; i++)
	 	  	{
	 		  SendData(0x00);
	 	  	}
	     }
 }
 /*----------------------------------------------------------------------------------
   * Function:		Clear_Sector_x_y
   *----------------------------------------------------------------------------------
   * description:	Clearing the display by coordinates (vertically),
   * 				pages are cleared first, then columns
   * parameters:	-uint8_t x1, uint8_t x2, uint8_t y1, uint8_t y2
   *
   * on return:		-
   ------------------------------------------------------------------------------------*/
  void Clear_Sector_x_y(uint8_t x1, uint8_t x2, uint8_t y1, uint8_t y2)
   {
  	 SendCommand(0x21);			//  Область вывода - от 0 до 127 столбца;
  	 SendCommand(x1);
  	 SendCommand(x2);
  	 SendCommand(0x22);			//  Область вывода - от  до  строки;
  	 SendCommand(y1);
  	 SendCommand(y2);

  	 for(uint8_t j = x1; j <= x2; j++)
  	     {
  	 	  for (uint8_t i = y1; i <= y2; i++)
  	 	  	{
  	 		  SendData(0x0);
  	 		  SendCommand(0xB0+i);
  	 	  	}
  	     }
   }
/*----------------------------------------------------------------------------------
 * Function:		init_sector
 *----------------------------------------------------------------------------------
 * description:	- initializing the display by coordinates
 * parameters:	- uint8_t x1, uint8_t x2, uint8_t y1, uint8_t y2
 *
 * on return:	-
 ------------------------------------------------------------------------------------*/
 void Init_sector(uint8_t x1, uint8_t x2, uint8_t y1, uint8_t y2)
 {
	 SendCommand(0x21);			//  Область вывода - от 0 до 127 столбца;
	 SendCommand(x1);
	 SendCommand(x2);
	 SendCommand(0x22);			//  Область вывода - от  до  строки;
	 SendCommand(y1);
	 SendCommand(y2);
 }
 /*----------------------------------------------------------------------------------
  * Function:		Output_Char_16pt
  *----------------------------------------------------------------------------------
  * description:	- uint8_t out_char
  * parameters:		-
  *
  * on return:		-
  ------------------------------------------------------------------------------------*/
 void Output_Char_16pt(uint8_t out_char)
 {
 	uint16_t begin_bitmap, end_bitmap, width_bitmap, i;

 	begin_bitmap = microsoftSansSerif_16ptDescriptors[out_char -' '][1];
 	width_bitmap = microsoftSansSerif_16ptDescriptors[out_char -' '][0];
 	end_bitmap = begin_bitmap + width_bitmap * 3;

 	for (i = begin_bitmap; i < end_bitmap; i++)
 	{
 		SendData(microsoftSansSerif_16ptBitmaps[i]);
 	}
 	for (i = 0; i < 12; i++)
 	{
 		SendData(0x00);
 	}
 }
 /*----------------------------------------------------------------------------------
  * Function:		Output_Char_14pt(uint8_t out_char)
  *----------------------------------------------------------------------------------
  * description:	- uint8_t out_char
  * parameters:		-
  *
  * on return:		-
  ------------------------------------------------------------------------------------*/
 void Output_Char_14pt(char out_char)
  {
  	uint16_t width_bitmap, height, begin_bitmap;
  	uint8_t b;
  	uint32_t a = 0;
  	uint8_t x0, y0;

  	begin_bitmap = timesNewRoman_14ptDescriptors[out_char -' '][1];
  	width_bitmap = timesNewRoman_14ptDescriptors[out_char -' '][0];
  	height = 3;

  	/* getting bytes horizontally */
  	for(x0 = 1; x0 <= width_bitmap; x0++)
  	{
  		// writing 3 vertical bytes into one (24-bit)
  		for(uint8_t i  = 0; i < height; i++)
  		{
  			b = timesNewRoman_14ptBitmaps[begin_bitmap + i];
  			a |= b << ((2 - i) * 8);
  		}
  		/* writing 24-bit pixels */
		for (y0 = 0; y0 < 24; y0++)
		{
			if ((a >> y0) & 1)
			{
				SetPixel(SSD1309.CurrentX + x0, SSD1309.CurrentY + y0);
			}
		}
		a = 0;
		/* character interval */
		begin_bitmap = begin_bitmap + 3;
  	}
  	/* Increase pointer */
  	  SSD1309.CurrentX += width_bitmap+1;
  }

 //void Output_Char_TimesNewRoman(char out_char, TimNewRom PtType)
 void Output_Char_TimesNewRoman(char out_char, uint8_t pt)
  {
  	uint16_t width_bitmap, height, begin_bitmap;
  	uint8_t b;
  	uint32_t a = 0;
  	uint8_t x0, y0;

  	switch(pt)
  	{
  	 case 14:
  		begin_bitmap = timesNewRoman_14ptDescriptors[out_char -' '][1];
  		width_bitmap = timesNewRoman_14ptDescriptors[out_char -' '][0];
  		height = 3;
  		break;
  	case 8:
  		begin_bitmap = timesNewRoman_8ptDescriptors[out_char -' '][1];
  		width_bitmap = timesNewRoman_8ptDescriptors[out_char -' '][0];
  		height = 2;
  		break;
  	case 10:
  		begin_bitmap = timesNewRoman_10ptDescriptors[out_char -' '][1];
  		width_bitmap = timesNewRoman_10ptDescriptors[out_char -' '][0];
  		height = 2;
  		break;
  	case 16:
  	  	begin_bitmap = timesNewRoman_16ptDescriptors[out_char -' '][1];
  	  	width_bitmap = timesNewRoman_16ptDescriptors[out_char -' '][0];
  	  	height = 3;
  	  	break;
  	}
  	/*begin_bitmap = timesNewRoman_14ptDescriptors[out_char -' '][1];
  	width_bitmap = timesNewRoman_14ptDescriptors[out_char -' '][0];
  	height = 3;*/

  	/* getting bytes horizontally */
  	for(x0 = 1; x0 <= width_bitmap; x0++)
  	{
  		// writing 3 vertical bytes into one (24-bit)
  		for(uint8_t i  = 0; i < height; i++)
  		{
  			if(pt == 14){b = timesNewRoman_14ptBitmaps[begin_bitmap + i];}
  			else if(pt == 8){b = timesNewRoman_8ptBitmaps[begin_bitmap + i];}
  			else if(pt == 10){b = timesNewRoman_10ptBitmaps[begin_bitmap + i];}
  			else if(pt == 16){b = timesNewRoman_16ptBitmaps[begin_bitmap + i];}
  			//b = timesNewRoman_10ptBitmaps[begin_bitmap + i];
  			//uint8_t h = height - 1;
  			a |= b << (((height - 1) - i) * 8);
  			//HAL_Delay(100);
  		}
  		/* writing height byte pixels */
		for (y0 = 0; y0 < height * 8; y0++)
		{
			if ((a >> y0) & 1)
			{
				SetPixel(SSD1309.CurrentX + x0, SSD1309.CurrentY + y0);
			}
		}
		a = 0;
		/* character interval */
		begin_bitmap = begin_bitmap + 3;
  	}
  	/* Increase pointer */
  	  SSD1309.CurrentX += width_bitmap+1;
  }
 /*----------------------------------------------------------------------------------
  * Function:		Output_Char_8pt(uint8_t out_char)
  *----------------------------------------------------------------------------------
  * description:	- uint8_t out_char
  * parameters:		-
  *
  * on return:		-
  ------------------------------------------------------------------------------------*/
 void Output_Char_8pt(uint8_t out_char)
  {
  	uint16_t begin_bitmap, end_bitmap, width_bitmap, i;

  	begin_bitmap = microsoftSansSerif_8ptDescriptors[out_char -' '][1];
  	width_bitmap = microsoftSansSerif_8ptDescriptors[out_char -' '][0];
  	end_bitmap = begin_bitmap + width_bitmap * 2;

  	for (i = begin_bitmap; i < end_bitmap; i++)
  	{
  		SendData(microsoftSansSerif_8ptBitmaps[i]);
  	}
  	for (i = 0; i < 2*2; i++)
  	{
  		SendData(0x00);
  	}
  }

 /*----------------------------------------------------------------------------------
  * Function:		Output_String_16pt
  *----------------------------------------------------------------------------------
  * description:	- const char *string
  * parameters:		-
  *
  * on return:		-
  ------------------------------------------------------------------------------------*/
 void Output_String_16pt(const char *string)
 {

 	while (*string != 0)
 	{
 		if (*string < 0x7F)
 		{
 			Output_Char_16pt(*string);
 		}
 		string++;
 	}
 }
 /*----------------------------------------------------------------------------------
  * Function:		Output_String_8pt
  *----------------------------------------------------------------------------------
  * description:	- const char *string
  * parameters:		-
  *
  * on return:		-
  ------------------------------------------------------------------------------------*/
 void Output_String_8pt(const char *string)
 {

 	while (*string != 0)
 	{
 		if (*string < 0x7F)
 		{
 			Output_Char_8pt(*string);
 		}
 		string++;
 	}
 }
 /*----------------------------------------------------------------------------------
   * Function:		Output_String_14pt
   *----------------------------------------------------------------------------------
   * description:		- const char *string
   * parameters:		-
   *
   * on return:			-
   ------------------------------------------------------------------------------------*/
  void Output_String_14pt(const char *string)
  {

  	while (*string != 0)
  	{
  		if (*string < 0x100) // 256
  		{
  			Output_Char_14pt(*string);
  		}
  		string++;
  	}
  }

  /*----------------------------------------------------------------------------------
     * Function:		Output_String
     *----------------------------------------------------------------------------------
     * description:		- const char *string
     * parameters:		-
     *
     * on return:			-
     ------------------------------------------------------------------------------------*/
    void Output_String_TimesNewRoman(const char *string)
    {

    	while (*string != 0)
    	{
    		if (*string < 0x100) // 256
    		{
    			Output_Char(*string);
    		}
    		string++;
    	}
    }
  /*----------------------------------------------------------------------------------
   * Function:		SSD1309_DrawFilledRect
   *----------------------------------------------------------------------------------
   * description:		- x and y axis coordinates
   * parameters:		-
   *
   * on return:			-
   ------------------------------------------------------------------------------------*/
  void SSD1309_DrawFilledRect(uint8_t xStart, uint8_t xEnd, uint8_t yStart, uint8_t yEnd)
  {
    for (uint8_t i = xStart; i < xEnd; i++)
    {
      for (uint8_t j = yStart; j <  yEnd; j++)
      {
        SetPixel(i, j);
      }
    }
  }
  /*----------------------------------------------------------------------------------
   * Function:		SSD1309_GotoXY
   *----------------------------------------------------------------------------------
   * description:		- the starting coordinates are set
   * parameters:		-
   *
   * on return:			-
   ------------------------------------------------------------------------------------*/
  void SSD1309_GotoXY(uint16_t x, uint16_t y) {
  	/* Set write pointers */
  	SSD1309.CurrentX = x;
  	SSD1309.CurrentY = y;
  }
  /*----------------------------------------------------------------------------------
   * Function:		SetPixel
   *----------------------------------------------------------------------------------
   * description:		- write pixel by coordinates to the buffer
   * parameters:		-
   *
   * on return:			-
   ------------------------------------------------------------------------------------*/
  static void SetPixel(uint8_t x, uint8_t y)
  {
	  if(x >= SSD1309_WIDTH || y >= SSD1309_HEIGHT)
	        {
	            // Don't write outside the buffer
	            return;
	        }
    pixelBuffer[x + (y / 8) * SSD1309_X_SIZE] |= (1 << (y % 8));
  }
  /*----------------------------------------------------------------------------------
   * Function:		SSD1309_ClearScreen
   *----------------------------------------------------------------------------------
   * description:		- clearing the all buffer screen
   * parameters:		-
   *
   * on return:			-
   ------------------------------------------------------------------------------------*/
  void SSD1309_ClearScreen(void)
  {
    for (uint16_t i = 0; i <= SSD1309_BUFFER_SIZE; i++)
    {
      pixelBuffer[i] = 0x00;
    }
    SSD1309_UpdateScreen();
  }
  /*----------------------------------------------------------------------------------
   * Function:		SSD1309_UpdateScreen
   *----------------------------------------------------------------------------------
   * description:		- updating the screen by buffer values
   * parameters:		-
   *
   * on return:			-
   ------------------------------------------------------------------------------------*/
  void SSD1309_UpdateScreen(void)
  {
	  for(uint16_t i = 0; i <= SSD1309_BUFFER_SIZE; i++)
	  {
		  SendData(pixelBuffer[i]);
	  }
  }
  /*----------------------------------------------------------------------------------
    * Function:		SSD1309_UpdateScreen
    *----------------------------------------------------------------------------------
    * description:		- clearing screen without buffer
    * parameters:		-
    *
    * on return:		-
    ------------------------------------------------------------------------------------*/
  void Cursor_Screen(void)
  {
 	  uint8_t i = 0;
 	 for(uint8_t j =0; j < 2; j++)
 	     {
 	 	  SendCommand(0xB5+i);
 	 	  for (uint8_t i = 0; i < 2; i++)
 	 	  	{
 	 		  SendData(0x03);
 	 	  	}
 	     }
  }
  /*----------------------------------------------------------------------------------
    * Function:		SSD1309_WriteString
    *----------------------------------------------------------------------------------
    * description:      - write string for font.c
    * parameters:		-
    *
    * on return:		- *str
    ------------------------------------------------------------------------------------*/
  char SSD1309_WriteString(char *str, FontDef_t *Font)
{
	/* Write characters */
	while (*str)
	{
		/* Write character by character */
		if (SSD1309_WriteChar(*str, Font) != *str)
		{
			//if (SSD1309_WriteChar(*str, Font) != *str) {
			/* Return error */
			return *str;
		}
		/* Increase string pointer */
		str++;
	}

	/* Everything OK, zero should be returned */
	return *str;
}
  /*----------------------------------------------------------------------------------
    * Function:		SSD1309_WriteChar
    *----------------------------------------------------------------------------------
    * description:		- write char for font.c
    * parameters:		-
    *
    * on return:		- ch
    ------------------------------------------------------------------------------------*/
  char SSD1309_WriteChar(char ch, FontDef_t *Font)
{
	uint16_t x0 = 0;
	uint16_t y0 = 0;
	int16_t b = 0;
	/* Check available space in LCD */
	if (
	SSD1309_WIDTH <= (SSD1309.CurrentX + Font->width) ||
	SSD1309_HEIGHT <= (SSD1309.CurrentY + Font->height))
	{
		/* Error */
		return 0;
	}
	/*Translate font to screen buffer*/
	for (y0 = 0; y0 < Font->height; y0++)
	{
		b = Font->data[(ch - 32) * Font->height + y0];
		for (x0 = 0; x0 < Font->width; x0++)
		{
			if ((b << x0) & 0x8000)
			{
				SetPixel(SSD1309.CurrentX + x0, SSD1309.CurrentY + y0);
			}
		}
	}
	/* Increase pointer */
	SSD1309.CurrentX += Font->width;
	/* Return character written */
	return ch;
}
  /*----------------------------------------------------------------------------------
    * Function:		ssd1309_DrawCircle
    *----------------------------------------------------------------------------------
    * description:		- drawing circle
    * parameters:		-
    *
    * on return:		-
    ------------------------------------------------------------------------------------*/
    void ssd1309_DrawCircle(uint8_t par_x,uint8_t par_y,uint8_t par_r) {
      int32_t x = -par_r;
      int32_t y = 0;
      int32_t err = 2 - 2 * par_r;
      int32_t e2;

      if (par_x >= SSD1309_WIDTH || par_y >= SSD1309_HEIGHT) {
        return;
      }

        do {
          SetPixel(par_x - x, par_y + y);
          SetPixel(par_x + x, par_y + y);
          SetPixel(par_x + x, par_y - y);
          SetPixel(par_x - x, par_y - y);
            e2 = err;
            if (e2 <= y) {
                y++;
                err = err + (y * 2 + 1);
                if(-x == y && e2 <= x) {
                  e2 = 0;
                }
                else
                {
                  /*nothing to do*/
                }
            }
            else
            {
              /*nothing to do*/
            }
            if(e2 > x) {
              x++;
              err = err + (x * 2 + 1);
            }
            else
            {
              /*nothing to do*/
            }
        } while(x <= 0);

        return;
    }
