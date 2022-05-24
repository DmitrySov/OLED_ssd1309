#include "menu.h"

MENU1_StateTypeDef country = MENU_1_STATE_IDLE;
MENU2_StateTypeDef city = MENU_2_STATE_IDLE;

uint8_t button_set = 0;
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
				button_rattle();							//
			if (button_set == 1)
			{
				country = MENU_1_STATE_MAIN;
				button_set = 0;
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
		button_set = 0;
		break;
	case MENU_2_STATE_WAIT: //ждем запуска главного меню
         button_rattle();
		//if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET)
	if (button_set == 1)
		{
			city = MENU_2_STATE_WAIT_1;
			//SSD1309_init();
		        SendCommand(0xB0);
				SendCommand(0x81);
				SendCommand(0x7F);
				//////////////////
				SendCommand(0xC8);
				SendCommand(0x00);
				SendCommand(0x10);
				/////////////////

				SendCommand(0x20);
				SendCommand(0x10);
				SendCommand(0x21);
				SendCommand(0x00);
				SendCommand(0x7F);
				SendCommand(0x22);
				SendCommand(0x00);
				SendCommand(0x07);

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
			button_set = 0;
			break;
		}

	case MENU_2_STATE_WAIT_1: //запуск главного меню
			button_rattle();
		if (button_set == 1)
		{
			city = MENU_2_STATE_WAIT_2;
				//SSD1309_init();
				SendCommand(0xB0);
				SendCommand(0x81);
				SendCommand(0x7F);
				//////////////////
				SendCommand(0xC8);
				SendCommand(0x00);
				SendCommand(0x10);
				/////////////////

				SendCommand(0x20);
				SendCommand(0x10);
				SendCommand(0x21);
				SendCommand(0x00);
				SendCommand(0x7F);
				SendCommand(0x22);
				SendCommand(0x00);
				SendCommand(0x07);
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
			button_set = 0;
			break;
		}
		//NextMenuProcess();
		//break;
	case MENU_2_STATE_WAIT_2: //запуск главного меню
		    button_rattle();
		if (button_set == 1)
		{
			city = MENU_2_STATE_WAIT_3;
			//SSD1309_init();
				SendCommand(0xB0);
				SendCommand(0x81);
				SendCommand(0x7F);
				//////////////////
				SendCommand(0xC8);
				SendCommand(0x00);
				SendCommand(0x10);
				/////////////////

				SendCommand(0x20);
				SendCommand(0x10);
				SendCommand(0x21);
				SendCommand(0x00);
				SendCommand(0x7F);
				SendCommand(0x22);
				SendCommand(0x00);
				SendCommand(0x07);
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
			button_set = 0;
			break;
		}
			//NextMenuProcess();
			//break;
	case MENU_2_STATE_WAIT_3:
		button_rattle();
		if(button_set == 1)
		{
			city = MENU_2_STATE_IDLE;

			break;
		}
   }
  HAL_Delay(50);
 }
}

 void button_rattle (void)
 {
	 static uint8_t flag_key1_press = 1;
	   static uint8_t flag_wait = 1;
	   static uint32_t time_key1_press = 0;
	  // uint8_t flag_str = 0;

	  if( (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET) && flag_key1_press)
	 	{
		  flag_key1_press = 0;
		  flag_wait = 0;
		  time_key1_press = HAL_GetTick();
	 	}
	 if(flag_wait == 0 && ((HAL_GetTick() - time_key1_press) > 200))
	   {
		 if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET)
		 {
			button_set = 1;
		 }
		 else
		 {
			 flag_wait = 1;
			 flag_key1_press = 1;
		 }
	   }

	   if(!flag_key1_press && (HAL_GetTick() - time_key1_press) > 300)
	 {
	         flag_key1_press = 1;
	 }
}
