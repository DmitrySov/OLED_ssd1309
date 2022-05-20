#include "menu.h"

MENU_StateTypeDef menu_state = MENU_STATE;
//MAIN_MENU_StateTypeDef main_menu_state = MAIN_MENU_STATE_IDLE;
//----------------------------------------------
void main_menu(void)
{
	switch (menu_state)
	{
		case MENU_STATE: //старт программы
			menu_state = MENU_STATE_WAIT;
			SSD1309_ClearScreen();
			SSD1306_GotoXY(0, 0);
			SSD1309_WriteString("Welcome", &Font_7x10);
			SSD1309_UpdateScreen();
			break;
		case MENU_STATE_WAIT: //ждем запуска главного меню

			if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET)
			{

				SSD1309_init();
				SSD1309_ClearScreen();
				SSD1306_GotoXY(0, 0);
				SSD1309_WriteString("To home", &Font_7x10);
				SSD1309_UpdateScreen();

			}

			/*if(button_state[Button_Select]&ST_UNPRESSURE)
			{
				SetButtonState(Button_Select,ST_LOCKED);
				ResetButtonState(Button_Select,ST_UNPRESSURE);
				SetButtonState(Button_Select,ST_PRESSURE);
				//обработка нажатия кнопки
				menu_state = MENU_STATE_MAIN;
			}*/
			break;
		/*case MENU_STATE_MAIN: //запуск главного меню
			main_menu_state=MAIN_MENU_STATE_IDLE;
			MainMenuProcess();*/
			//break;
	}
  //HAL_Delay(50);
}
