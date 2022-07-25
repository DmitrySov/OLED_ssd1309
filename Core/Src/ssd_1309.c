/*
 * ssd-1309.c

 *      Author: Sovetnikov
 */
 /* Includes ------------------------------------------------------------------*/
#include "ssd_1309.h"
#include "font_Times_New_Roman.h"
/* Declarations and definitions ----------------------------------------------*/
static uint8_t pixelBuffer[SSD1309_BUFFER_SIZE];

/* Functions -----------------------------------------------------------------*/
static void SetPixel(uint8_t x, uint8_t y);

/* Private variable -----------------------------------------------------------------*/
 SSD1309_t SSD1309;
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
    __WRITE_GPIO (CS_GPIO_Port, CS_Pin, 0);
	__WRITE_GPIO (RES_GPIO_Port, RES_Pin, 1);
    __WRITE_GPIO (RES_GPIO_Port, RES_Pin, 0);
 	__WRITE_GPIO (RES_GPIO_Port, RES_Pin, 1);
	__WRITE_GPIO (CS_GPIO_Port, CS_Pin, 1);
 }
 /*----------------------------------------------------------------------------------
  * Function:		SendCommand
  *----------------------------------------------------------------------------------
  * description:	Commands are sent with the corresponding command table 9-1 (datasheet)
  * parameters:		-uint8_t Command
  *
  * on return:		-
  ------------------------------------------------------------------------------------*/
 void SendCommand(uint8_t Command)
 {
	  __WRITE_GPIO (CS_GPIO_Port, CS_Pin, 0);
	  __WRITE_GPIO (D_C_GPIO_Port, D_C_Pin, 0);
	  __WRITE_GPIO (WR_GPIO_Port, WR_Pin, 0);
	  __WRITE_bits_0_7 (GPIOD, Command);
 	  __WRITE_GPIO (WR_GPIO_Port, WR_Pin, 1);
 	  __WRITE_GPIO (CS_GPIO_Port, CS_Pin, 1);
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
	 __WRITE_GPIO (CS_GPIO_Port, CS_Pin, 0);
	 __WRITE_GPIO (D_C_GPIO_Port, D_C_Pin, 1);
	 __WRITE_GPIO (WR_GPIO_Port, WR_Pin, 0);
	 __WRITE_bits_0_7 (GPIOD, Data);
 	 __WRITE_GPIO (WR_GPIO_Port, WR_Pin, 1);
 	 __WRITE_GPIO (CS_GPIO_Port, CS_Pin, 1);
 }
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
	__WRITE_GPIO (CS_GPIO_Port, CS_Pin, 0);
	SendCommand(0xAE);	// display off
	SSD1309_Clear();

	SendCommand(0xB0);
	SendCommand(0x81);
	SendCommand(0xC8);
	//////////////////
	SendCommand(0xC8);		//Remapped (C0h / C8h)
	SendCommand(0x00); //---set low column address
	SendCommand(0x10); //---set high column address
	/////////////////
	SendCommand(0xAF);

	SendCommand(0x20);
	SendCommand(0x00);
	SendCommand(0x21);
	SendCommand(0x00);
	SendCommand(0x7F);
	SendCommand(0x22);
	SendCommand(0x00);
	SendCommand(0x07);

	SendCommand(0xA1);
	__WRITE_GPIO (CS_GPIO_Port, CS_Pin, 1);
	// Set default values for screen object

	SSD1309.CurrentX = 0;
	SSD1309.CurrentY = 0;
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
	if (x >= SSD1309_WIDTH || y >= SSD1309_HEIGHT)
	{
		// Don't write outside the buffer
		return;
	}
	pixelBuffer[x + (y / 8) * SSD1309_X_SIZE] |= (1 << (y % 8));
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
	  for(uint8_t m = 0; m < 8; m++)
	  {
		  SendCommand(0xB0 + m);
		  SendCommand(0x00 + SSD1306_X_OFFSET_LOWER);
		  SendCommand(0x10 + SSD1306_X_OFFSET_UPPER);
		  uint16_t a = m*128;
		  	 for(uint8_t i = 0; i < 128; i++)
		  	 {
		  		 a++;
		  		SendData(pixelBuffer[a]);
		  	 }
	  }
  }
 /*----------------------------------------------------------------------------------
 * Function:		SSD1309_Clear
 *----------------------------------------------------------------------------------
 * description:		- clearing the all buffer screen
 * parameters:		-
 *
 * on return:			-
 ------------------------------------------------------------------------------------*/
void SSD1309_Clear(void)
{
	memset(pixelBuffer, 0x00, sizeof(pixelBuffer));
}
/*----------------------------------------------------------------------------------
 * Function:		SSD1309_GotoXY
 *----------------------------------------------------------------------------------
 * description:		- the starting coordinates are set
 * parameters:		-
 *
 * on return:			-
 ------------------------------------------------------------------------------------*/
void SSD1309_GotoXY(uint16_t x, uint16_t y)
{
	/* Set write pointers */
	SSD1309.CurrentX = x;
	SSD1309.CurrentY = y;
}
/*----------------------------------------------------------------------------------
 * Function:		Output_String_TimesNewRoman
 *----------------------------------------------------------------------------------
 * description:		- writing a string Times New Roman
 * parameters:		- const char *string
 *
 * on return:		-
 ------------------------------------------------------------------------------------*/
   void Output_String_TimesNewRoman(const char *string, fontSize PtType)
   {
    	while (*string != 0)
     {
    	if (*string < 0x100) // 256
    	{
    		Output_Char_TimesNewRoman(*string, PtType);
    	}
    		string++;
    	}
    }
/*----------------------------------------------------------------------------------
 * Function:		Output_Char_TimesNewRoman
 *----------------------------------------------------------------------------------
 * description:		- writing a char Times New Roman
 * parameters:		- char out_char
 *
 * on return:			-
 ------------------------------------------------------------------------------------*/
   void Output_Char_TimesNewRoman(char out_char, fontSize PtType)
  {
  	uint16_t width_bitmap, height, begin_bitmap;
  	uint8_t b;
  	uint32_t a = 0;
  	uint8_t x0, y0;

  	switch(PtType)
  	{
  	case pt8:
  		begin_bitmap = timesNewRoman_8ptDescriptors[out_char -' '][1];
  		width_bitmap = timesNewRoman_8ptDescriptors[out_char -' '][0];
  		height = 2;
  		break;
  	case pt10:
  		begin_bitmap = timesNewRoman_10ptDescriptors[out_char -' '][1];
  		width_bitmap = timesNewRoman_10ptDescriptors[out_char -' '][0];
  		height = 2;
  		break;
	case pt12:
		begin_bitmap = timesNewRoman_12ptDescriptors[out_char - ' '][1];
		width_bitmap = timesNewRoman_12ptDescriptors[out_char - ' '][0];
		height = 3;
		break;
    case pt14:
  	  	begin_bitmap = timesNewRoman_14ptDescriptors[out_char -' '][1];
  	  	width_bitmap = timesNewRoman_14ptDescriptors[out_char -' '][0];
  	  	height = 3;
  	  	break;
  	case pt16:
  	  	begin_bitmap = timesNewRoman_16ptDescriptors[out_char -' '][1];
  	  	width_bitmap = timesNewRoman_16ptDescriptors[out_char -' '][0];
  	  	height = 3;
  	  	break;
  	}
  	/* getting bytes horizontally */
  	for(x0 = 1; x0 <= width_bitmap; x0++)
  	{
  		// writing vertical bytes into one
  		for(uint8_t i  = 0; i < height; i++)
  		{
  			if(PtType == 14){b = timesNewRoman_14ptBitmaps[begin_bitmap + i];}
  			else if(PtType == 8){b = timesNewRoman_8ptBitmaps[begin_bitmap + i];}
  			else if(PtType == 10){b = timesNewRoman_10ptBitmaps[begin_bitmap + i];}
  			else if(PtType == 12){b = timesNewRoman_12ptBitmaps[begin_bitmap + i];}
  			else if(PtType == 16){b = timesNewRoman_16ptBitmaps[begin_bitmap + i];}
  			a |= b << (((height - 1) - i) * 8);
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
		/* begin next vertical bytes */
		begin_bitmap = begin_bitmap + height;
  	}
  	/* Increase pointer */
  	  SSD1309.CurrentX += width_bitmap + 1;
  }

/*----------------------------------------------------------------------------------
 * Function:		Output_String_TimesNewRoman
 *----------------------------------------------------------------------------------
 * description:		- writing a string Times New Roman
 * parameters:		- const char *string
 *
 * on return:		-
 ------------------------------------------------------------------------------------*/
void Output_String_Arial(const char *string, fontSize PtType)
{
	while (*string != 0)
	{
		if (*string < 0x100) // 256
		{
			Output_Char_Arial(*string, PtType);
		}
		string++;
	}
}
/*----------------------------------------------------------------------------------
 * Function:		Output_Char_TimesNewRoman
 *----------------------------------------------------------------------------------
 * description:		- writing a char Times New Roman
 * parameters:		- char out_char
 *
 * on return:			-
 ------------------------------------------------------------------------------------*/
void Output_Char_Arial(char out_char, fontSize PtType)
{
	uint16_t begin_bitmap;
	uint8_t b, offset, height, width_bitmap;
	uint32_t a = 0;
	uint8_t x0, y0;

	switch (PtType)
	{
	case pt8:
		begin_bitmap = Arial_8ptDescriptors[out_char - ' '][1];
		width_bitmap = Arial_8ptDescriptors[out_char - ' '][0];
		height = 2;
		offset = 2;
		break;
	case pt10:
		begin_bitmap = Arial_10ptDescriptors[out_char - ' '][1];
		width_bitmap = Arial_10ptDescriptors[out_char - ' '][0];
		height = 2;
		offset = 2;
		break;
	case pt12:
		begin_bitmap = Arial_12ptDescriptors[out_char - ' '][1];
		width_bitmap = Arial_12ptDescriptors[out_char - ' '][0];
		height = 2;
		offset = 3;
		break;
	case pt14:
		begin_bitmap = Arial_14ptDescriptors[out_char - ' '][1];
		width_bitmap = Arial_14ptDescriptors[out_char - ' '][0];
		height = 3;
		offset = 3;
		break;
	/*case pt16:
		begin_bitmap = Arial_16ptDescriptors[out_char - ' '][1];
		width_bitmap = Arial_16ptDescriptors[out_char - ' '][0];
		height = 3;
		break;*/
	}
	/* getting bytes horizontally */
	for (x0 = 1; x0 <= width_bitmap; x0++)
	{
		// writing vertical bytes into one
		for (uint8_t i = 0; i < height; i++)
		{
			if (PtType == 14)
			{
				b = Arial_14ptBitmaps[begin_bitmap + i];
			}
			else if (PtType == 8)
			{
				b = Arial_8ptBitmaps[begin_bitmap + i];
			}
			else if (PtType == 10)
			{
				b = Arial_10ptBitmaps[begin_bitmap + i];
			}
			else if (PtType == 12)
			{
				b = Arial_12ptBitmaps[begin_bitmap + i];
			}
			/*else if (PtType == 16)
			{
				b = Arial_16ptBitmaps[begin_bitmap + i];
			}*/
			a |= b << (((height - 1) - i) * 8);
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
		/* begin next vertical bytes */
		begin_bitmap = begin_bitmap + offset;
	}
	/* Increase pointer */
	SSD1309.CurrentX += width_bitmap + 2;
}
/*----------------------------------------------------------------------------------
 * Function:		SSD1309_DrawFilledRect
 *----------------------------------------------------------------------------------
 * description:		- x and y axis coordinates
 * parameters:		-
 *
 * on return:			-
 ------------------------------------------------------------------------------------*/
void SSD1309_DrawFilledRect(uint8_t xStart, uint8_t xEnd, uint8_t yStart,
		uint8_t yEnd)
{
	for (uint8_t i = xStart; i < xEnd; i++)
	{
		for (uint8_t j = yStart; j < yEnd; j++)
		{
			SetPixel(i, j);
		}
	}
}
/*----------------------------------------------------------------------------------
 * Function:		ssd1309_DrawCircle
 *----------------------------------------------------------------------------------
 * description:		- drawing circle
 * parameters:		-
 *
 * on return:		-
 ------------------------------------------------------------------------------------*/
void ssd1309_DrawCircle(uint8_t par_x, uint8_t par_y, uint8_t par_r)
{
	int32_t x = -par_r;
	int32_t y = 0;
	int32_t err = 2 - 2 * par_r;
	int32_t e2;

	if (par_x >= SSD1309_WIDTH || par_y >= SSD1309_HEIGHT)
	{
		return;
	}

	do
	{
		SetPixel(par_x - x, par_y + y);
		SetPixel(par_x + x, par_y + y);
		SetPixel(par_x + x, par_y - y);
		SetPixel(par_x - x, par_y - y);
		e2 = err;
		if (e2 <= y)
		{
			y++;
			err = err + (y * 2 + 1);
			if (-x == y && e2 <= x)
			{
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
		if (e2 > x)
		{
			x++;
			err = err + (x * 2 + 1);
		}
		else
		{
			/*nothing to do*/
		}
	} while (x <= 0);

	return;
}
