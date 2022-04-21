/*
 * ssd-1309.c
 *
 *  Created on: 14 апр. 2022 г.
 *      Author: Sovetnikov
 */
/*_____ I N C L U D E S ____________________________________________________*/
#include "ssd_1309.h"

/*_____ M A C R O S ________________________________________________________*/


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
 * description:		set the RES# pin LOW value (logical low level), wait at least 3us
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
  * description:	SendCommand
  * parameters:		-Сommands are sent with the corresponding command table 9-1 (datasheet)
  *
  * on return:		-
  ------------------------------------------------------------------------------------*/
 void SendCommand(uint8_t Data)
 {
    HAL_GPIO_WritePin(D_C_GPIO_Port, D_C_Pin, GPIO_PIN_RESET);
 	HAL_GPIO_WritePin(WR_GPIO_Port, WR_Pin, GPIO_PIN_RESET);
 	LL_GPIO_WriteOutputPort(GPIOD, Data);
 	HAL_GPIO_WritePin(WR_GPIO_Port, WR_Pin, GPIO_PIN_SET);
 }
 /*----------------------------------------------------------------------------------
   * Function:		SendCommand
   *----------------------------------------------------------------------------------
   * description:	SendData
   * parameters:	-Data transmission on the display
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
 /*----------------------------------------------------------------------------*/
 void Clear_Screen(void)
 {
	  uint8_t i = 0;
	 for(uint8_t j =0; j < 128; j++)
	     {
	 	  SendCommand(0xB0+i);
	 	  for (uint8_t i = 0; i < 8; i++)
	 	  	{
	 		  SendData(0x0);
	 	  	}
	     }
 }
 /*----------------------------------------------------------------------------*/
  void Clear_Sector_x_y(uint8_t x1, uint8_t x2, uint8_t y1, uint8_t y2)
   {
  	 SendCommand(0x21);			//  Область вывода - от 0 до 127 столбца;
  	 SendCommand(x1);
  	 SendCommand(x2);
  	 SendCommand(0x22);			//  Область вывода - от  до  строки;
  	 SendCommand(y1);
  	 SendCommand(y2);
  	  uint8_t i = 0;
  	 for(uint8_t j =0; j < 128; j++)
  	     {
  	 	  SendCommand(0xB0+i);
  	 	  for (uint8_t i = 0; i < 8; i++)
  	 	  	{
  	 		  SendData(0x0);
  	 	  	}
  	     }
   }
/*----------------------------------------------------------------------------*/
 void init_sector(uint8_t x1, uint8_t x2, uint8_t y1, uint8_t y2)
 {
	 SendCommand(0x21);			//  Область вывода - от 0 до 127 столбца;
	 SendCommand(x1);
	 SendCommand(x2);
	 SendCommand(0x22);			//  Область вывода - от  до  строки;
	 SendCommand(y1);
	 SendCommand(y2);
 }




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
 	for (i = 0; i < 4*3; i++)
 	{
 		SendData(0x00);
 	}
 }

 void Output_String(const char *string)
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


