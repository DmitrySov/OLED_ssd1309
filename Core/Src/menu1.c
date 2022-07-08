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
uint8_t button_gpio = 0;
extern float x_axis;

AXIS_StateTypeDef axis_switch = AXIS_1_MAIN;
DATA_StateTypeDef data_switch = DATA_1_MAIN;
counter_button_t counter_button = axis;

void button_rattle_GPIO (GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
 {
	 static uint8_t flag_key1_press = 1;
	 	 static uint32_t time_key1_press = 0;

	 	 if(HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == GPIO_PIN_SET && flag_key1_press)
	 	 {
	 	   flag_key1_press = 0;
	 	   // Click Action
	 	   button_gpio = 1;
	 	   time_key1_press = HAL_GetTick();
	 	 }

	 	 if(!flag_key1_press && (HAL_GetTick() - time_key1_press) > 300)
	 	 {
	 	   flag_key1_press = 1;
	 	 }
 }

void axis_menu (void)
{
  switch (axis_switch)
   {
	case AXIS_1_MAIN:
	{
		axis_switch = AXIS_1_WAIT;
		SendCommand(0xC8);
		SendCommand(0x20);
		SendCommand(0x00);
		SendCommand(0x21);
		SendCommand(0x00);
		SendCommand(0x7F);
		SendCommand(0x22);
		SendCommand(0x00);
		SendCommand(0x07);
		//SSD1309_init();
		SSD1309_ClearScreen();
		SSD1309_GotoXY(0, 0);
		Output_String_Arial("Изменения по Х:", pt12);
		SSD1309_GotoXY(10, 12);
		sprintf(buff_1, "%2.4f", x_axis);
		Output_String_Arial(buff_1, pt12);
		SSD1309_UpdateScreen();
		break;
	}
	case AXIS_1_WAIT:

		if ((HAL_GetTick() - timer) > 1000)
		{
			axis_switch = AXIS_1_MAIN;
			timer = HAL_GetTick();
			break;
		}
   }
}

 void data_menu (void)
{
  switch (data_switch)
   {
	case DATA_1_MAIN:
	{
		//data_switch = DATA_1_WAIT;
		SendCommand(0xC8);
		SendCommand(0x20);
		SendCommand(0x00);
		SendCommand(0x21);
		SendCommand(0x00);
		SendCommand(0x7F);
		SendCommand(0x22);
		SendCommand(0x00);
		SendCommand(0x07);
		//SSD1309_init();
		SSD1309_ClearScreen();
		SSD1309_GotoXY(0, 0);
		Output_String_Arial("Дата", pt12);
		SSD1309_GotoXY(10, 12);
		//sprintf(buff_1, "%2.4f", x_axis);
		Output_String_Arial("07-07-2022", pt12);
		SSD1309_UpdateScreen();
		break;
	}
	/*case DATA_1_WAIT:

		if ((HAL_GetTick() - timer) > 1000)
		{
			axis_switch = DATA_1_MAIN;
			timer = HAL_GetTick();
			break;
		}*/
   }
}

 void menu_display(void)
{
	switch (counter_button)
		{
			case axis:
			{
				button_gpio = 0;
				//counter_button = data;
				axis_menu();
				break;
			}
			case data:
			{
				counter_button = temperature;
				//data_menu();
				break;
			}
			case temperature:
			{
				counter_button = humidity;
				//temperature_menu();
				break;
			}
			case humidity:
			{
				counter_button = temperature;
				//humidity_menu();
				break;
			}
		}
}



