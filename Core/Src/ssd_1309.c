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

/* Private variable -----------------------------------------------------------------*/
static SSD1309_t SSD1309;
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

	SendCommand(0xB0);
	SendCommand(0x81);
	SendCommand(0x7F);			//  яркость;
	//////////////////
	SendCommand(0xC8);		//Remapped (C0h / C8h)
	SendCommand(0x00); //---set low column address
	SendCommand(0x10); //---set high column address
	/////////////////
	SendCommand(0xAF);
	HAL_Delay(100);

	SendCommand(0x20);
	SendCommand(0x10);			//  Vertical Addressing Mode;
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
  * Function:		Output_Char_14pt(uint8_t out_char)
  *----------------------------------------------------------------------------------
  * description:
  * parameters:		-uint8_t out_char
  *
  * on return:		-
  ------------------------------------------------------------------------------------*/
 void Output_Char_14pt(uint8_t out_char)
  {
	 //int16_t x0, y0, b;
	         /* Check available space in LCD */
	         	/*if (
	         		SSD1309_WIDTH <= (SSD1309.CurrentX + Font->width) ||
	         		SSD1309_HEIGHT <= (SSD1309.CurrentY + Font->height)
	         	) {*/
	         		/* Error */
	         	//	return 0;
	         //	}
	          /*Translate font to screen buffer*/
	         /*for (y0 = 0; y0 < Font->height; y0++)
	         {
	             b = Font->data[(ch - 32) * Font->height + y0];
	             for (x0 = 0; x0 < Font->width; x0++)
	             {

	               	 SetPixel(SSD1309.CurrentX + x0, SSD1309.CurrentY + y0);
	                 }
	             }
	         }*/
	        /* Increase pointer */
	       //    SSD1309.CurrentX += Font->width;
  	uint16_t width_bitmap, height, begin_bitmap, end_bitmap;
  	int16_t b, *data;
  	uint8_t x0, y0;
  	//uint16_t begin_bitmap, end_bitmap, width_bitmap, i;

  	begin_bitmap = microsoftSansSerif_14ptDescriptors[out_char -' '][1];
  	width_bitmap = microsoftSansSerif_14ptDescriptors[out_char -' '][0];
  	height = 3;

  	end_bitmap = (begin_bitmap + width_bitmap * height) - 1;

  	for(x0 = begin_bitmap; x0 < end_bitmap; x0++)      //записываем значения в массив;
  	{
  		b = data[begin_bitmap + x0];
  		for(y0 = 0; y0 < 8; y0++)
  		{

  			if ((b << y0) & 0x80)
  		   {

  				SetPixel(SSD1309.CurrentX + x0, SSD1309.CurrentY + y0);
  		   }
  		}
  	}


  /*	for (i = 0; i < 3*4; i++)
  	{
  		SendData(0x00);
  	}*/
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

 // char SSD1309_WriteString(int16_t x, int16_t y, char* str, FontDef_t* Font) {
  	/* Write characters */
  //	while (*str) {
  		/* Write character by character */
  	//	if (SSD1309_WriteChar(x, y, *str, Font) != *str) {
  			/* Return error */
  	//		return *str;
  	//	}

  		/* Increase string pointer */
  	//	str++;
  	//}

  	/* Everything OK, zero should be returned */
  //	return *str;
 // }

//  char SSD1309_WriteChar(int16_t x, int16_t y, char ch, FontDef_t* Font)
 // {
     // int16_t x0, y0, b;
      /* Check available space in LCD */
      	//if (
      	//	SSD1309_WIDTH <= (SSD1309.CurrentX + Font->width) ||
      	//	SSD1309_HEIGHT <= (SSD1309.CurrentY + Font->height)
      //	) {
      		/* Error */
      	//	return 0;
      	//}
      /* Translate font to screen buffer*/
     /* for (y0 = 0; y0 < Font->height; y0++)
      {
          b = Font->data[(ch - 32) * Font->height + y0];
          for (x0 = 0; x0 < Font->width; x0++)
          {
               if ((b << x0) & 0x8000)
              {
            	 SetPixel(x + x0, y + y0);
              }
          }
      }*/
      /*Return character written */
   //  return ch;
  //}


  char SSD1309_WriteString(char* str, FontDef_t* Font) {
    	/* Write characters */
    	while (*str) {
    		/* Write character by character */
    		if (SSD1309_WriteChar(*str, Font) != *str) {
    			/* Return error */
    			return *str;
    		}
    		/* Increase string pointer */
    		str++;
    	}

    	/* Everything OK, zero should be returned */
    	return *str;
    }

    char SSD1309_WriteChar(char ch, FontDef_t* Font)
    {
        int16_t x0, y0, b;
        /* Check available space in LCD */
        	if (
        		SSD1309_WIDTH <= (SSD1309.CurrentX + Font->width) ||
        		SSD1309_HEIGHT <= (SSD1309.CurrentY + Font->height)
        	) {
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
/////////////////////////////////////////////////////////////
    void SSD1306_GotoXY(uint16_t x, uint16_t y) {
    	/* Set write pointers */
    	SSD1309.CurrentX = x;
    	SSD1309.CurrentY = y;
    }
///////////////////////////////////////////////////////////
    void ssd1306_DrawCircle(uint8_t par_x,uint8_t par_y,uint8_t par_r) {
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
