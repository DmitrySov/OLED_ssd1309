#include "menu.h"

MENU1_StateTypeDef country = MENU_1_STATE_IDLE;
MENU2_StateTypeDef city = MENU_2_STATE_IDLE;

//uint32_t time = 0;
//----------------------------------------------
void main_menu(void)
{
	switch (country)
	{
		case MENU_1_STATE_IDLE: //старт программы
			country = MENU_1_STATE_WAIT;
			SSD1309_ClearScreen();
			SSD1306_GotoXY(0, 0);
			SSD1309_WriteString("Russia", &Font_7x10);
			SSD1309_UpdateScreen();
			break;
		case MENU_1_STATE_WAIT: //ждем запуска главного меню

			if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET)
			{

				/*SSD1309_init();
				SSD1309_ClearScreen();
				SSD1306_GotoXY(0, 0);
				SSD1309_WriteString("To home", &Font_7x10);
				SSD1309_UpdateScreen();*/
				country = MENU_1_STATE_MAIN;

			}
			break;
		case MENU_1_STATE_MAIN: //запуск главного меню
			city = MENU_2_STATE_IDLE;
			NextMenuProcess();
			break;
	}
  HAL_Delay(50);
}
void NextMenuProcess(void)
{
	while (1)
 {
  switch (city)
  {
	case MENU_2_STATE_IDLE: //старт программы
		city = MENU_2_STATE_WAIT;
		SSD1309_init();
		SSD1309_ClearScreen();
		ssd1306_DrawCircle(3, 3, 2);
		SSD1306_GotoXY(10, 0);
		SSD1309_WriteString("Moscow", &Font_7x10);
		SSD1306_GotoXY(10, 10);
		SSD1309_WriteString("Saint Petersburg", &Font_7x10);
		SSD1306_GotoXY(10, 20);
		SSD1309_WriteString("Kazan", &Font_7x10);
		SSD1306_GotoXY(10, 30);
		SSD1309_WriteString("Ekaterinburg", &Font_7x10);
		SSD1309_UpdateScreen();
		break;
	case MENU_2_STATE_WAIT: //ждем запуска главного меню

		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET)
		{
			city = MENU_2_STATE_WAIT_1;
			SSD1309_init();
			SSD1309_ClearScreen();
			ssd1306_DrawCircle(3, 13, 2);
			SSD1306_GotoXY(10, 0);
			SSD1309_WriteString("Moscow", &Font_7x10);
			SSD1306_GotoXY(10, 10);
			SSD1309_WriteString("Saint Petersburg", &Font_7x10);
			SSD1306_GotoXY(10, 20);
			SSD1309_WriteString("Kazan", &Font_7x10);
			SSD1306_GotoXY(10, 30);
			SSD1309_WriteString("Ekaterinburg", &Font_7x10);
			SSD1309_UpdateScreen();
			break;
		}

	case MENU_2_STATE_WAIT_1: //запуск главного меню
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET)
		{
			city = MENU_2_STATE_WAIT_2;
			SSD1309_init();
			SSD1309_ClearScreen();
			ssd1306_DrawCircle(3, 23, 2);
			SSD1306_GotoXY(10, 0);
			SSD1309_WriteString("Moscow", &Font_7x10);
			SSD1306_GotoXY(10, 10);
			SSD1309_WriteString("Saint Petersburg", &Font_7x10);
			SSD1306_GotoXY(10, 20);
			SSD1309_WriteString("Kazan", &Font_7x10);
			SSD1306_GotoXY(10, 30);
			SSD1309_WriteString("Ekaterinburg", &Font_7x10);
			SSD1309_UpdateScreen();
			break;
		}
		//NextMenuProcess();
		//break;
	case MENU_2_STATE_WAIT_2: //запуск главного меню

		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET)
		{
			city = MENU_2_STATE_WAIT_3;
			SSD1309_init();
			SSD1309_ClearScreen();
			ssd1306_DrawCircle(3, 33, 2);
			SSD1306_GotoXY(10, 0);
			SSD1309_WriteString("Moscow", &Font_7x10);
			SSD1306_GotoXY(10, 10);
			SSD1309_WriteString("Saint Petersburg", &Font_7x10);
			SSD1306_GotoXY(10, 20);
			SSD1309_WriteString("Kazan", &Font_7x10);
			SSD1306_GotoXY(10, 30);
			SSD1309_WriteString("Ekaterinburg", &Font_7x10);
			SSD1309_UpdateScreen();
			break;
		}
			//NextMenuProcess();
			//break;
	case MENU_2_STATE_WAIT_3:

		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET)
		{
			city = MENU_2_STATE_IDLE;
			break;
		}
   }
  HAL_Delay(50);
 }
}

