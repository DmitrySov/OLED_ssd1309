#include "menu.h"

MENU1_StateTypeDef country = MENU_1_STATE_IDLE;
MENU2_StateTypeDef city = MENU_2_STATE_IDLE;

uint8_t button_set_gpio_A0 = 0;
uint8_t button_set_gpio_E7 = 0;
uint8_t button_set_gpio_E8 = 0;
uint8_t button_set_gpio_E9 = 0;

int8_t i = 3;
//----------------------------------------------
void main_menu(void)
{
	switch (country)
	{
		case MENU_1_STATE_IDLE:
			country = MENU_1_STATE_WAIT;
				SendCommand(0x20);
				SendCommand(0x10);
				SendCommand(0x21);
				SendCommand(0x00);
				SendCommand(0x7F);
				SendCommand(0x22);
				SendCommand(0x00);
				SendCommand(0x07);
			SSD1309_ClearScreen();
			SSD1306_GotoXY(0, 0);
			SSD1309_WriteString("Russia", &Font_7x10);
			SSD1309_UpdateScreen();
			break;
		case MENU_1_STATE_WAIT:
			button_rattle_GPIO_A0();							// button click processing
			if (button_set_gpio_A0 == 1)							// button_set - flag on the button status
			{
				country = MENU_1_STATE_MAIN;
				button_set_gpio_A0 = 0;
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

	case MENU_2_STATE_IDLE:
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
		SSD1306_GotoXY(10, 40);
		SSD1309_WriteString("Syzran", &Font_7x10);
		SSD1309_UpdateScreen();
		button_set_gpio_A0 = 0;
		break;
	case MENU_2_STATE_WAIT:
		button_rattle_GPIO_A0();
		button_rattle_GPIO_E7();
		button_rattle_GPIO_E8();
		button_rattle_GPIO_E9();
		//if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET)
	if (button_set_gpio_E7 == 1)
		{

			//city = MENU_2_STATE_WAIT_1;
				SendCommand(0x20);
				SendCommand(0x10);
				SendCommand(0x21);
				SendCommand(0x00);
				SendCommand(0x7F);
				SendCommand(0x22);
				SendCommand(0x00);
				SendCommand(0x07);
			SSD1309_ClearScreen();
				i = i+10;
			     if(i < 53)
			     { ssd1306_DrawCircle(3, i, 2);}
			     else{i = 3;}
			ssd1306_DrawCircle(3, i, 2);
			SSD1306_GotoXY(10, 0);
			SSD1309_WriteString("Moscow", &Font_7x10);
			SSD1306_GotoXY(10, 10);
			SSD1309_WriteString("Saint Petersburg", &Font_7x10);
			SSD1306_GotoXY(10, 20);
			SSD1309_WriteString("Kazan", &Font_7x10);
			SSD1306_GotoXY(10, 30);
			SSD1309_WriteString("Ekaterinburg", &Font_7x10);
			SSD1306_GotoXY(10, 40);
			SSD1309_WriteString("Syzran", &Font_7x10);
			SSD1309_UpdateScreen();
			button_set_gpio_E7 = 0;
			//break;
		}
	if (button_set_gpio_E8 == 1)
		{
		        //city = MENU_2_STATE_WAIT_1;
				SendCommand(0x20);
				SendCommand(0x10);
				SendCommand(0x21);
				SendCommand(0x00);
				SendCommand(0x7F);
				SendCommand(0x22);
				SendCommand(0x00);
				SendCommand(0x07);
				SSD1309_ClearScreen();
				i = i - 10;
				if(i < 0)
				{i = 53;}
				//if (i < 54) {
					ssd1306_DrawCircle(3, i, 2);
				/*} else {
					i = 3;
				}*/
				SSD1306_GotoXY(10, 0);
				SSD1309_WriteString("Moscow", &Font_7x10);
				SSD1306_GotoXY(10, 10);
				SSD1309_WriteString("Saint Petersburg", &Font_7x10);
				SSD1306_GotoXY(10, 20);
				SSD1309_WriteString("Kazan", &Font_7x10);
				SSD1306_GotoXY(10, 30);
				SSD1309_WriteString("Ekaterinburg", &Font_7x10);
				SSD1306_GotoXY(10, 40);
				SSD1309_WriteString("Syzran", &Font_7x10);
				SSD1309_UpdateScreen();
				button_set_gpio_E8 = 0;
				//break;
		}
	if (button_set_gpio_E9 == 1)
		{
			button_set_gpio_E9 = 0;
			city = MENU_2_STATE_EXIT;
		}

	case MENU_2_STATE_EXIT:
		city = MENU_1_STATE_IDLE;
			return;

			//NextMenuProcess();
			//break;
	/*case MENU_2_STATE_WAIT_3:
		button_rattle_GPIO_A0();
		if(button_set_gpio_A0 == 1)
		{
			city = MENU_2_STATE_IDLE;

			break;
		}*/
   }
  HAL_Delay(50);
 }
}

 void button_rattle_GPIO_A0 (void)
 {
	 /*static uint8_t flag_key1_press = 1;
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
	 }*/
	 static uint8_t flag_key1_press = 1;
	 static uint32_t time_key1_press = 0;

	 if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET && flag_key1_press) // подставить свой пин
	 {
	   flag_key1_press = 0;
	   // действие на нажатие
	   button_set_gpio_A0 = 1;
	   time_key1_press = HAL_GetTick();
	 }

	 if(!flag_key1_press && (HAL_GetTick() - time_key1_press) > 300)
	 {
	   flag_key1_press = 1;
	 }
}

 void button_rattle_GPIO_E7 (void)
 {
	 static uint8_t flag_key1_press = 1;
	 	 static uint32_t time_key1_press = 0;

	 	 if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_7) == GPIO_PIN_SET && flag_key1_press) // подставить свой пин
	 	 {
	 	   flag_key1_press = 0;
	 	   // действие на нажатие
	 	   button_set_gpio_E7 = 1;
	 	   time_key1_press = HAL_GetTick();
	 	 }

	 	 if(!flag_key1_press && (HAL_GetTick() - time_key1_press) > 300)
	 	 {
	 	   flag_key1_press = 1;
	 	 }
 }

 void button_rattle_GPIO_E8 (void)
 {
	 static uint8_t flag_key1_press = 1;
	 	 static uint32_t time_key1_press = 0;

	 	 if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_8) == GPIO_PIN_SET && flag_key1_press) // подставить свой пин
	 	 {
	 	   flag_key1_press = 0;
	 	   // действие на нажатие
	 	   button_set_gpio_E8 = 1;
	 	   time_key1_press = HAL_GetTick();
	 	 }

	 	 if(!flag_key1_press && (HAL_GetTick() - time_key1_press) > 300)
	 	 {
	 	   flag_key1_press = 1;
	 	 }
 }
 void button_rattle_GPIO_E9 (void)
 {
	 static uint8_t flag_key1_press = 1;
	 	 static uint32_t time_key1_press = 0;

	 	 if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_9) == GPIO_PIN_SET && flag_key1_press) // подставить свой пин
	 	 {
	 	   flag_key1_press = 0;
	 	   // действие на нажатие
	 	   button_set_gpio_E9 = 1;
	 	   time_key1_press = HAL_GetTick();
	 	 }

	 	 if(!flag_key1_press && (HAL_GetTick() - time_key1_press) > 300)
	 	 {
	 	   flag_key1_press = 1;
	 	 }
 }
