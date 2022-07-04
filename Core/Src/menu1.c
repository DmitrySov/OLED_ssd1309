/*
 * menu1.c
 *
 *      Author: sovetnikov
 */

#include "main.h"
#include "menu1.h"


double volume = 79831234.95;
uint32_t value = 245678;
char buff_1 [16] = {0};
uint32_t timer = 0;
uint8_t button_gpio_A0 = 0;
extern uint8_t drdyFlag;
float x_axis = 00.0000;

SPI_HandleTypeDef hspi1_1;
/********LIS3DSH*********/
LIS3DSH_InitTypeDef myAccConfigDef;
LIS3DSH_DataScaled myData;
//char buf_str [15] = {0};
char buffer [10] = {0};
/************************/

MENU1_StateTypeDef start_display = MENU_1_MAIN;
  void start_menu (void)
{
	  myAccConfigDef.dataRate = LIS3DSH_DATARATE_25;
	  myAccConfigDef.fullScale = LIS3DSH_FULLSCALE_4;
	  myAccConfigDef.antiAliasingBW = LIS3DSH_FILTER_BW_50;
	  myAccConfigDef.enableAxes = LIS3DSH_XYZ_ENABLE;
	  myAccConfigDef.interruptEnable = true;
	  LIS3DSH_Init(&hspi1_1, &myAccConfigDef);

	  LIS3DSH_X_calibrate(-1000.0, 980.0);
	  LIS3DSH_Y_calibrate(-1020.0, 1040.0);
	  LIS3DSH_Z_calibrate(-920.0, 1040.0);
	while(1)
	{
		HAL_Delay(300);
		switch(start_display)
		{
		 case MENU_1_START:
			button_rat_GPIO_A0();		// button click processing
			if (button_gpio_A0 == 1)	// button_set - flag on the button status
			{
				start_display = MENU_1_MAIN;
				button_gpio_A0 = 0;
			}
			break;
		case MENU_1_MAIN:
			{
			if (drdyFlag == 1)
			{
				drdyFlag = 0;
				x_axis = LIS3DSH_GetDataScaled_x();
				HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
			}
			start_display = MENU_1_WAIT;
			SendCommand(0xC8);
			SendCommand(0x20);
			SendCommand(0x00);
			SendCommand(0x21);
			SendCommand(0x00);
			SendCommand(0x7F);
			SendCommand(0x22);
			SendCommand(0x00);
			SendCommand(0x07);
			SSD1309_ClearScreen();
			SSD1309_GotoXY(0, 0);
			Output_String_TimesNewRoman("Изменения по оси Х:", pt10);
			SSD1309_GotoXY(10, 12);
			sprintf(buffer, "%2.4f", x_axis);
			Output_String_TimesNewRoman(buffer, pt10);
			SSD1309_UpdateScreen();
					/*sprintf(buff_1, "%9.2lf", volume);
					SendCommand(0xC8);
					SendCommand(0x20);
					SendCommand(0x01);
					SendCommand(0x21);
					SendCommand(0x00);
					SendCommand(0x7F);
					SendCommand(0x22);
					SendCommand(0x05);
					SendCommand(0x07);
					 Init_sector(0x00, 0x7F, 0x05, 0x07);
					  Output_String_16pt(buff_1);*/
			// read the temperature and humidity data once a second

			break;
			}
		case MENU_1_WAIT:

				 if ((HAL_GetTick() - timer) > 1000)
				{
					start_display = MENU_1_MAIN;
					timer = HAL_GetTick();
					break;
				}

		case MENU_2_WAIT:
			{
				/*if( (HAL_GetTick() - timer) > 1000 )
				{ start_display = MENU_1_MAIN;
				timer = HAL_GetTick();}*/
			}

	  }
   }
}

  void button_rat_GPIO_A0 (void)
   {
  	 static uint8_t flag_key1_press = 1;
  	 static uint32_t time_key1_press = 0;

  	 if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET && flag_key1_press)
  	 {
  	   flag_key1_press = 0;
  	   // Click Action
  	   button_gpio_A0 = 1;
  	   time_key1_press = HAL_GetTick();
  	 }

  	 if(!flag_key1_press && (HAL_GetTick() - time_key1_press) > 300)
  	 {
  	   flag_key1_press = 1;
  	 }
  }

  void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
   {
     /* Prevent unused argument(s) compilation warning */
    // UNUSED(GPIO_Pin);
     /* NOTE: This function Should not be modified, when the callback is needed,
              the HAL_GPIO_EXTI_Callback could be implemented in the user file
      */

   	drdyFlag = 1;
   	//HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
   }
