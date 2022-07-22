/*
 * menu1.c
 *
 *      Author: sovetnikov
 */

#include "main.h"
#include "menu1.h"


//double volume = 79831234.95;
uint32_t value = 245678;
char buff_time [16] = {0};
char buff_date [16] = {0};
uint32_t timer = 0;
uint32_t timer1 = 0;
uint8_t button_gpio = 0;

uint8_t flag_tick = 0;
uint8_t a = 0;

extern RTC_HandleTypeDef hrtc;
//extern TIM_HandleTypeDef htim6;

void button_rattle_GPIO(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	static uint8_t flag_key1_press = 1;
	static uint32_t time_key1_press = 0;

	if (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == GPIO_PIN_SET && flag_key1_press)
	{
		flag_key1_press = 0;
		// Click Action
		button_gpio = 1;
		time_key1_press = HAL_GetTick();
	}

	if (!flag_key1_press && (HAL_GetTick() - time_key1_press) > 300)
	{
		flag_key1_press = 1;
	}
}
void get_time(void)
{
	RTC_TimeTypeDef sTime =
	{ 0 };
	RTC_DateTypeDef sDate =
	{ 0 };

	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN); // RTC_FORMAT_BIN , RTC_FORMAT_BCD
	snprintf(buff_time, 15, "%02d:%02d:%02d", sTime.Hours, sTime.Minutes,
			sTime.Seconds);

	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	snprintf(buff_date, 15, "%02d-%02d-%d", sDate.Date, sDate.Month,
			2000 + sDate.Year);
}
void data_time (void)
{
	if (flag_tick == 1)
	{
		timer = HAL_GetTick();
		flag_tick = 0;
	}
	get_time();
	SSD1309_Clear();
	SSD1309_GotoXY(40, 10);
	Output_String_Arial(buff_time, pt12);
	SSD1309_GotoXY(25, 32);
	Output_String_Arial(buff_date, pt12);
	SSD1309_UpdateScreen_1();
}
 void volume (void)
{
	if (flag_tick == 1)
	{
		timer = HAL_GetTick();
		flag_tick = 0;
	}
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
}
  void expenses (void)
{
	if (flag_tick == 1)
	{
		timer = HAL_GetTick();
		flag_tick = 0;
	}
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
}

  void temp_press(void)
{
	if (flag_tick == 1)
	{
		timer = HAL_GetTick();
		flag_tick = 0;
	}
	SSD1309_Clear();
	SSD1309_GotoXY(0, 0);
	Output_String_Arial("Текущие параметры:", pt10);
	SSD1309_GotoXY(3, 20);
	Output_String_Arial("Темп. +27,5  С", pt12);
	ssd1309_DrawCircle(89, 21, 2);
	SSD1309_GotoXY(3, 40);
	Output_String_Arial("Давл. 105,35 кПа", pt12);
	SSD1309_UpdateScreen_1();
}
void battery_status (void)
{
	if (flag_tick == 1)
	{
		timer = HAL_GetTick();
		flag_tick = 0;
	}
	SSD1309_Clear();
	SSD1309_GotoXY(0, 0);
	Output_String_Arial("Состояние ЭП:", pt12);
	SSD1309_GotoXY(5, 20);
	Output_String_Arial("Основ.      75%", pt12);
	SSD1309_GotoXY(5, 40);
	Output_String_Arial("Доп.         100%", pt12);
	SSD1309_UpdateScreen_1();
}

 void tick_ms(void)
{
	 if ((HAL_GetTick() - timer) > 30000)
	 	 {
		 	 a = 0;
	 		 SSD1309_Clear();
	 		 SSD1309_UpdateScreen_1();
	 		 flag_tick = 1;
	 		 timer = HAL_GetTick();
	 	}
}

 /*  void menu_display (void)
{
	button_rattle_GPIO(GPIOA, GPIO_PIN_0);
	if (button_gpio == 1)
	{
		timer = HAL_GetTick();
		button_gpio = 0;
		a++;
	}
	if (a == 1)
	{
		data_time();
	}
	else if (a == 2)
	{
		volume();
	}
	else if (a == 3)
	{
		expenses();
	}
	else if (a == 4)
	{
		temp_press();
	}
	else if (a == 5)
	{
		battery_status();
	}
	if (a > 5) {a = 0; a++;}
}*/

 void menu_display (void)
{
	 button_rattle_GPIO(GPIOA, GPIO_PIN_0);
	 	if (button_gpio == 1)
	 	{
	 		timer = HAL_GetTick();
	 		button_gpio = 0;
	 		a++;
	 	}
  switch(a)
  {
    case 1:
     {
    	 data_time();
    	 break;
     }
    case 2:
     {
    	 volume();
    	 break;
     }
    case 3:
     {
    	 expenses();
    	 break;
     }
    case 4:
     {
    	 temp_press();
    	 break;
     }
    case 5:
     {
    	 battery_status();
    	 break;
     }
     if (a > 5) {a = 0; a++;}
    //default  : a = 0;
  // a++;
    //break;
  }
}



