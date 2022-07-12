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
		SSD1309_Clear();
		SSD1309_GotoXY(0, 0);
		Output_String_Arial("����", pt12);
		SSD1309_GotoXY(10, 12);
		Output_String_Arial("07-07-2022", pt12);
		SSD1309_UpdateScreen_1();
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

  void volume (void)
 {
 	switch (volume_switch)
 	{
 	case VOLUME_MAIN:
 	{
 		SSD1309_Clear();
 		SSD1309_GotoXY(0, 0);
 		Output_String_Arial("������� ���������:", pt12);
 		SSD1309_GotoXY(10, 14);
 		Output_String_Arial("������ Q [�3/�]", pt12);
 		SSD1309_GotoXY(10, 24);
 		Output_String_Arial("8436485,25", pt12);
 		SSD1309_UpdateScreen_1();
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

  void expenses (void)
{
	switch (expenses_switch)
	{
	case EXPENSES_MAIN:
	{
		SSD1309_Clear();
		SSD1309_GotoXY(0, 0);
		Output_String_Arial("������� ���������:", pt12);
		SSD1309_GotoXY(10, 14);
		Output_String_Arial("����������� ����� [�3]", pt12);
		SSD1309_GotoXY(10, 24);
		Output_String_Arial("8436485,25", pt12);
		SSD1309_UpdateScreen_1();
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

  void temp_press(void)
{
	switch (temp_press_switch)
	{
	case EXPENSES_MAIN:
	{
		SSD1309_Clear();
		SSD1309_GotoXY(0, 0);
		Output_String_Arial("������� ���������:", pt12);
		SSD1309_GotoXY(10, 14);
		Output_String_Arial("T =", pt12);
		SSD1309_GotoXY(10, 24);
		Output_String_Arial("P =", pt12);
		SSD1309_UpdateScreen_1();
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

  void battery_status (void)
{
	switch (battery_status_switch)
	{
	case EXPENSES_MAIN:
	{
		SSD1309_Clear();
		SSD1309_GotoXY(0, 0);
		Output_String_Arial("��������� ��:", pt12);
		SSD1309_GotoXY(10, 14);
		Output_String_Arial("�������� =", pt12);
		SSD1309_GotoXY(10, 24);
		Output_String_Arial("��������� =", pt12);
		SSD1309_UpdateScreen_1();
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

void axis_menu (void)
{
  switch (axis_switch)
   {
	case AXIS_1_MAIN:
	{
		axis_switch = AXIS_1_WAIT;
		SSD1309_Clear();
		SSD1309_GotoXY(0, 0);
		Output_String_Arial("��������� �� �:", pt12);
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
		data_time();
	}
	if ((flag_menu == 1) && (a == 2))
	{
		volume();
	}
	if ((flag_menu == 1) && (a == 3))
	{
		expenses();
	}
	if ((flag_menu == 1) && (a == 4))
	{
		temp_press();
	}
	if ((flag_menu == 1) && (a == 5))
	{
		battery_status();
		a = 0;
	}
}



