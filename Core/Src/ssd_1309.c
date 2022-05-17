/*
 * ssd-1309.c
 *
 *  Created on: 14 апр. 2022 г.
 *      Author: Sovetnikov
 */
 /* Includes ------------------------------------------------------------------*/
#include "ssd_1309.h"

/* Declarations and definitions ----------------------------------------------*/
static uint8_t pixelBuffer[SSD1309_BUFFER_SIZE] = {0};


/* Functions -----------------------------------------------------------------*/
static void SetPixel(uint8_t x, uint8_t y);

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
	Clear_Screen();

	/*SendCommand(0xD5);
	SendCommand(0x80);

	SendCommand(0x8D);
	SendCommand(0x14);

	SendCommand(0x40);

	SendCommand(0xA1);

	SendCommand(0xC8);

	SendCommand(0xDA);
	SendCommand(0x12);

	SendCommand(0xA8);
	SendCommand(0x3F);

	SendCommand(0xD3);
	SendCommand(0x00);

	SendCommand(0x20);
	SendCommand(0x01);

	SendCommand(0x22);
	SendCommand(0x00);
	SendCommand(0x07);

	SendCommand(0x81);
	SendCommand(0x7F);

	SendCommand(0xA4);
	SendCommand(0xA6);
	SendCommand(0xAF);*/

	//SendCommand(0xB0);
   // SendCommand(0x81);
	SendCommand(0xB0);
	SendCommand(0x81);
	SendCommand(0x7F);			//  яркость;
	SendCommand(0xAF);
	HAL_Delay(100);

	SendCommand(0x20);
	SendCommand(0x01);			//  Vertical Addressing Mode;
	SendCommand(0x21);			//  Область вывода - от 0 до 127 столбца;
	SendCommand(0x00);
	SendCommand(0x7F);
	SendCommand(0x22);			//  Область вывода - от  до  строки;
	SendCommand(0x00);
	SendCommand(0x07);
	//SendCommand(0xDA); //
   // SendCommand(0x12); //
	SendCommand(0xA1);

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
 * description:	initializing the display by coordinates
 * parameters:	-uint8_t x1, uint8_t x2, uint8_t y1, uint8_t y2
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
  * description:
  * parameters:		-uint8_t out_char
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
  * Function:		Output_Char_8pt(uint8_t out_char)
  *----------------------------------------------------------------------------------
  * description:
  * parameters:		-uint8_t out_char
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
  * Function:		Output_Char_14pt(uint8_t out_char)
  *----------------------------------------------------------------------------------
  * description:
  * parameters:		-uint8_t out_char
  *
  * on return:		-
  ------------------------------------------------------------------------------------*/
 void Output_Char_14pt(uint8_t out_char)
  {
  	uint16_t begin_bitmap, end_bitmap, width_bitmap, i;

  	begin_bitmap = microsoftSansSerif_14ptDescriptors[out_char -' '][1];
  	width_bitmap = microsoftSansSerif_14ptDescriptors[out_char -' '][0];
  	end_bitmap = begin_bitmap + width_bitmap * 3;


  	for (i = begin_bitmap; i < end_bitmap; i++)
  	{
  		SendData(microsoftSansSerif_14ptBitmaps[i]);
  	}
  	for (i = 0; i < 3*4; i++)
  	{
  		SendData(0x00);
  	}
  }
 /*----------------------------------------------------------------------------------
  * Function:		Output_String_16pt
  *----------------------------------------------------------------------------------
  * description:
  * parameters:		-const char *string
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
  * description:
  * parameters:		-const char *string
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
   * description:
   * parameters:		-const char *string
   *
   * on return:		-
   ------------------------------------------------------------------------------------*/
  void Output_String_14pt(const char *string)
  {

  	while (*string != 0)
  	{
  		if (*string < 0x7F)
  		{
  			Output_Char_14pt(*string);
  		}
  		string++;
  	}
  }

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

  static void SetPixel(uint8_t x, uint8_t y)
  {
	  if(x >= SSD1309_WIDTH || y >= SSD1309_HEIGHT)
	        {
	            // Don't write outside the buffer
	            return;
	        }
    pixelBuffer[x + (y / 8) * SSD1309_X_SIZE] |= (1 << (y % 8));
  }

  void SSD1309_ClearScreen(void)
  {
    for (uint16_t i = 0; i <= SSD1309_BUFFER_SIZE; i++)
    {
      pixelBuffer[i] = 0x00;
    }
    SSD1309_UpdateScreen();
  }

  void SSD1309_UpdateScreen(void)
  {
	  for(uint16_t i = 0; i <= SSD1309_BUFFER_SIZE; i++)
	  {
		  SendData(pixelBuffer[i]);
	  }

  }

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

