/*
 * menu1.c
 *
 *      Author: sovetnikov
 */

#include "main.h"
#include "menu1.h"


//double volume = 79831234.95;
uint32_t value = 245678;
char buff_1 [16] = {0};
uint32_t timer = 0;
uint32_t timer1 = 0;
uint8_t button_gpio = 0;
extern float x_axis;

uint8_t flag_menu = 0;
uint8_t a = 0;

DATA_TIME_StateTypeDef data_time_switch = DATA_TIME_MAIN;
EXPENSES_StateTypeDef expenses_switch = EXPENSES_MAIN;
VOLUME_StateTypeDef volume_switch = VOLUME_MAIN;
TEMP_PRESS_StateTypeDef temp_press_switch = TEMP_PRESS_MAIN;
BATT_STATUS_StateTypeDef battery_status_switch = BATT_STATUS_MAIN;

AXIS_StateTypeDef axis_switch = AXIS_1_MAIN;
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
  void data_time (void)
{
 switch (data_time_switch)
  {
	case DATA_TIME_MAIN:
	{
		battery_status_switch = BATT_STATUS_MAIN;
		data_time_switch = DATA_TIME_1_WAIT;
		SSD1309_Clear();
		SSD1309_GotoXY(40, 10);
		Output_String_Arial("12:59:00", pt12);
		SSD1309_GotoXY(25, 32);
		Output_String_Arial("07-07-2022", pt12);
		SSD1309_UpdateScreen_1();
		timer = HAL_GetTick();
		break;
	}
	case DATA_TIME_1_WAIT:
		if ((HAL_GetTick() - timer) > 6000)
		{
			flag_menu = 0;
			a = 0;
			SSD1309_Clear();
			SSD1309_UpdateScreen_1();
			timer = HAL_GetTick();
			data_time_switch = DATA_TIME_MAIN;
			break;
		}
   }
}
 void volume (void)
 {
  switch (volume_switch)
   {
 	case VOLUME_MAIN:
 	{
 		data_time_switch = DATA_TIME_MAIN;
 		volume_switch = VOLUME_WAIT;
 		timer = HAL_GetTick();
 		SSD1309_Clear();
 		SSD1309_GotoXY(0, 0);
 		Output_String_Arial("Текущие параметры:", pt10);
 		SSD1309_GotoXY(5, 20);
 		Output_String_Arial("Расход Q [м /ч]", pt12);
 		SSD1309_GotoXY(88, 15);
 		Output_String_Arial("3", pt8);
 		SSD1309_GotoXY(10, 40);
 		Output_String_Arial("  0000000,00", pt12);
 		SSD1309_UpdateScreen_1();
 		break;
 	}
 	case VOLUME_WAIT:
		if ((HAL_GetTick() - timer) > 6000)
		{
			flag_menu = 0;
			a = 1;
			SSD1309_Clear();
			SSD1309_UpdateScreen_1();
			volume_switch = VOLUME_MAIN;
			timer = HAL_GetTick();
			break;
		}
 	}
 }
  void expenses (void)
{
	switch (expenses_switch)
	{
	case EXPENSES_MAIN:
	{
		volume_switch = VOLUME_MAIN;
		expenses_switch = EXPENSES_WAIT;
		timer = HAL_GetTick();
		SSD1309_Clear();
		SSD1309_GotoXY(0, 0);
		Output_String_Arial("Текущие параметры:", pt10);
		SSD1309_GotoXY(5, 20);
		Output_String_Arial("Объем накоп. [м ]", pt12);
		SSD1309_GotoXY(113, 15);
		Output_String_Arial("3", pt8);
		SSD1309_GotoXY(10, 40);
		Output_String_Arial("  0000000,00", pt12);
		SSD1309_UpdateScreen_1();
		break;
	}
	case EXPENSES_WAIT:
			if ((HAL_GetTick() - timer) > 6000)
		{
			flag_menu = 0;
			a = 2;
			SSD1309_Clear();
			SSD1309_UpdateScreen_1();
			expenses_switch = EXPENSES_MAIN;
			timer = HAL_GetTick();
			break;
		}
	}
}

  void temp_press(void)
{
	switch (temp_press_switch)
	{
	case TEMP_PRESS_MAIN:
	{
		expenses_switch = EXPENSES_MAIN;
		temp_press_switch = TEMP_PRESS_WAIT;
		timer = HAL_GetTick();
		SSD1309_Clear();
		SSD1309_GotoXY(0, 0);
		Output_String_Arial("Текущие параметры:", pt10);
		SSD1309_GotoXY(3, 20);
		Output_String_Arial("Темп. +27,5  С", pt12);
		ssd1309_DrawCircle(89, 21, 2);
		SSD1309_GotoXY(3, 40);
		Output_String_Arial("Давл. 105,35 кПа", pt12);
		SSD1309_UpdateScreen_1();
		break;
	}
	case TEMP_PRESS_WAIT:
		if ((HAL_GetTick() - timer) > 6000)
		{
			flag_menu = 0;
			a = 3;
			SSD1309_Clear();
			SSD1309_UpdateScreen_1();
			temp_press_switch = TEMP_PRESS_MAIN;
			timer = HAL_GetTick();
			break;
		}
	}
}
void battery_status (void)
{
  switch (battery_status_switch)
	{
	case BATT_STATUS_MAIN:
	{
		temp_press_switch = TEMP_PRESS_MAIN;
		battery_status_switch = BATT_STATUS_WAIT;
		timer = HAL_GetTick();
		SSD1309_Clear();
		SSD1309_GotoXY(0, 0);
		Output_String_Arial("Состояние ЭП:", pt12);
		SSD1309_GotoXY(5, 20);
		Output_String_Arial("Основ.      75%", pt12);
		SSD1309_GotoXY(5, 40);
		Output_String_Arial("Доп.         100%", pt12);
		SSD1309_UpdateScreen_1();
		break;
	}
    case BATT_STATUS_WAIT:
		 if ((HAL_GetTick() - timer) > 6000)
		 {
		 flag_menu = 0;
		 a = 4;
		 SSD1309_Clear();
		 SSD1309_GotoXY(0, 0);
		 Output_String_Arial("?", pt12);
		 SSD1309_UpdateScreen_1();
		 battery_status_switch = BATT_STATUS_MAIN;
		 timer = HAL_GetTick();
		 break;
		}
	}
}

void axis_menu (void)
{
  switch (axis_switch)
   {
	case AXIS_1_MAIN:
	{
		axis_switch = AXIS_1_WAIT;
		SSD1309_Clear();
		SSD1309_GotoXY(0, 0);
		Output_String_Arial("Изменения по Х:", pt12);
		SSD1309_GotoXY(10, 12);
		sprintf(buff_1, "%2.4f", x_axis);
		Output_String_Arial(buff_1, pt12);
		SSD1309_UpdateScreen_1();
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
   void menu_display (void)
{
	button_rattle_GPIO(GPIOA, GPIO_PIN_0);
	if (button_gpio == 1)
	{
		flag_menu = 1;
		button_gpio = 0;
		a++;
	}
	if ((flag_menu == 1) && (a == 1))
	{
		// flag_menu = 0;
		data_time();
	}
	else if ((flag_menu == 1) && (a == 2))
	{
		volume();
	}
	else if ((flag_menu == 1) && (a == 3))
	{
		expenses();
	}
	else if ((flag_menu == 1) && (a == 4))
	{
		temp_press();
	}
	else if ((flag_menu == 1) && (a == 5))
	{
		battery_status();
		//a = 0;
	}
	if (a > 5) {a = 0; a++;}
}



