/*
 * menu1.c
 *
 *      Author: sovetnikov
 */
#include "menu1.h"

double volume = 79831234.95;
char buff_1 [16] = {0};
uint32_t timer = 0;
uint8_t button_gpio_A0 = 0;

MENU1_StateTypeDef start_display = MENU_1_START;
  void start_menu (void)
{
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
			start_display = MENU_1_WAIT;

			SendCommand(0x20);
			SendCommand(0x10);
			SendCommand(0x21);
			SendCommand(0x00);
			SendCommand(0x7F);
			SendCommand(0x22);
			SendCommand(0x00);
			SendCommand(0x07);
			SSD1309_ClearScreen();
			SSD1309_GotoXY(0, 0);
			Output_String_TimesNewRoman("Накопленный объем:", pt10);
			SSD1309_UpdateScreen();
			/*SSD1309_GotoXY(0, 10);
			Output_String_TimesNewRoman(buff_1, pt10);
			SSD1309_UpdateScreen();*/
			break;
			}
		case MENU_1_WAIT:
			{
				start_display = MENU_2_WAIT;
				SendCommand(0x20);
				SendCommand(0x10);
				SendCommand(0x21);
				SendCommand(0x00);
				SendCommand(0x7F);
				SendCommand(0x22);
				SendCommand(0x00);
				SendCommand(0x07);
				sprintf(buff_1, "%9.2lf", volume);
				SSD1309_GotoXY(0, 10);
				Output_String_TimesNewRoman(buff_1, pt10);
				SSD1309_UpdateScreen();
			}
		case MENU_2_WAIT:
			{
				if( (HAL_GetTick() - timer) > 500 )
				{ start_display = MENU_1_MAIN;
				timer = HAL_GetTick();}
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
