#include "menu.h"

MENU1_StateTypeDef country = MENU_1_STATE_IDLE;
MENU2_StateTypeDef city = MENU_2_STATE_IDLE;
MENU3_MOSCOW_StateTypedef moscow = MENU_3_0_STATE_IDLE;
MENU3_SAINT_PETERSBURG_StateTypedef st_peter = MENU_3_1_STATE_IDLE;
MENU3_KAZAN_StateTypedef kazan = MENU_3_2_STATE_IDLE;
MENU3_EKATERINBURG_StateTypedef ekatburg = MENU_3_3_STATE_IDLE;
MENU3_SYZRAN_StateTypedef syzran = MENU_3_4_STATE_IDLE;

uint8_t button_set_gpio_A0 = 0;
uint8_t button_set_gpio_E7 = 0;
uint8_t button_set_gpio_E8 = 0;
uint8_t button_set_gpio_E9 = 0;

int8_t i = 3;	// i - starting position of the cursor on the Y axis

/*----------------------------------------------------------------------------------
  * Function:		NextMenuProcess3_2(void)
  *----------------------------------------------------------------------------------
  * description:	Processing the first menu
  * parameters:		-
  *
  * on return:		-
  ------------------------------------------------------------------------------------*/
void main_menu1(void)
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
			SSD1309_GotoXY(0, 0);
			//SSD1309_WriteString("Russia", &Font_7x10);
			SSD1309_UpdateScreen();
			break;
		/******************************************************/
		case MENU_1_STATE_WAIT:
			button_rattle_GPIO_A0();		// button click processing
			if (button_set_gpio_A0 == 1)	// button_set - flag on the button status
			{
				country = MENU_1_STATE_MAIN;
				button_set_gpio_A0 = 0;
			}
			break;
		/******************************************************/
		case MENU_1_STATE_MAIN:
			city = MENU_2_STATE_IDLE;
			NextMenuProcess2();
			break;
	}
  HAL_Delay(50);
}
/*----------------------------------------------------------------------------------
  * Function:		NextMenuProcess2(void)
  *----------------------------------------------------------------------------------
  * description:	Processing the second menu
  * parameters:		-
  *
  * on return:		-
  ------------------------------------------------------------------------------------*/
void NextMenuProcess2(void)
{
	while (1)
 {
  switch (city)
  {
	case MENU_2_STATE_IDLE:
		city = MENU_2_STATE_WAIT;
		SSD1309_init();
		SSD1309_ClearScreen();

		ssd1309_DrawCircle(3, 3, 2);
		SSD1309_GotoXY(10, 0);
		/*SSD1309_WriteString("Moscow", &Font_7x10);
		SSD1309_GotoXY(10, 10);
		SSD1309_WriteString("Saint Petersburg", &Font_7x10);
		SSD1309_GotoXY(10, 20);
		SSD1309_WriteString("Kazan", &Font_7x10);
		SSD1309_GotoXY(10, 30);
		SSD1309_WriteString("Ekaterinburg", &Font_7x10);
		SSD1309_GotoXY(10, 40);
		SSD1309_WriteString("Syzran", &Font_7x10);*/
		SSD1309_UpdateScreen();
		button_set_gpio_A0 = 0;
		break;
	/******************************************************/
	case MENU_2_STATE_WAIT:
		button_rattle_GPIO_A0();
		button_rattle_GPIO_E7();
		button_rattle_GPIO_E8();
		button_rattle_GPIO_E9();
	/******************************************************/
	if (button_set_gpio_E7 == 1) // if the E7 button is pressed, the cursor moves down
		{
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
			     if(i <= 43)
			     { ssd1309_DrawCircle(3, i, 2);} // Cursor shift down by i+10, range 3 to 43
			     else{i = 3;}
			ssd1309_DrawCircle(3, i, 2);
			SSD1309_GotoXY(10, 0);
		/*	SSD1309_WriteString("Moscow", &Font_7x10);
			SSD1309_GotoXY(10, 10);
			SSD1309_WriteString("Saint Petersburg", &Font_7x10);
			SSD1309_GotoXY(10, 20);
			SSD1309_WriteString("Kazan", &Font_7x10);
			SSD1309_GotoXY(10, 30);
			SSD1309_WriteString("Ekaterinburg", &Font_7x10);
			SSD1309_GotoXY(10, 40);
			SSD1309_WriteString("Syzran", &Font_7x10);*/
			SSD1309_UpdateScreen();
			button_set_gpio_E7 = 0;
		}
	/******************************************************/
	if (button_set_gpio_E8 == 1)	// if the E8 button is pressed, the cursor moves up
		{
				SendCommand(0x20);
				SendCommand(0x10);
				SendCommand(0x21);
				SendCommand(0x00);
				SendCommand(0x7F);
				SendCommand(0x22);
				SendCommand(0x00);
				SendCommand(0x07);
				SSD1309_ClearScreen();
					i = i-10;
					if(i < 0)
					{i = 43;}
					ssd1309_DrawCircle(3, i, 2); //  Cursor shift up by i-10, range 3 to 43
				SSD1309_GotoXY(10, 0);
			/*	SSD1309_WriteString("Moscow", &Font_7x10);
				SSD1309_GotoXY(10, 10);
				SSD1309_WriteString("Saint Petersburg", &Font_7x10);
				SSD1309_GotoXY(10, 20);
				SSD1309_WriteString("Kazan", &Font_7x10);
				SSD1309_GotoXY(10, 30);
				SSD1309_WriteString("Ekaterinburg", &Font_7x10);
				SSD1309_GotoXY(10, 40);
				SSD1309_WriteString("Syzran", &Font_7x10);*/
				SSD1309_UpdateScreen();
				button_set_gpio_E8 = 0;
		}
	/******************************************************/
	if (button_set_gpio_E9 == 1) 	// if the E9 button is pressed, back to the start menu
		{
			button_set_gpio_E9 = 0;
			city = MENU_2_STATE_EXIT;
		}
	/******************************************************/
	if (button_set_gpio_A0 == 1)	// if the A0 button is pressed, open the next menu

	{
		city = MENU_2_STATE_P0;
		button_set_gpio_A0 = 0;
	}
    break;
    /******************************************************/
	case MENU_2_STATE_EXIT:
	country = MENU_1_STATE_IDLE;
			return;
	/******************************************************/
	case MENU_2_STATE_P0:
		if(i == 3)		// the first line
		{
			moscow = MENU_3_0_STATE_IDLE;
		    NextMenuProcess3_0();
			break;
		}
		if(i == 13)		// the second line
		{
			st_peter = MENU_3_1_STATE_IDLE;
			NextMenuProcess3_1();
			break;
		}
		if(i == 23)		// the third line
		{
			kazan = MENU_3_2_STATE_IDLE;
			NextMenuProcess3_2();
			break;
		}
		if(i == 33)		// the fourth line
		{
			ekatburg = MENU_3_3_STATE_IDLE;
			NextMenuProcess3_3();
			break;
		}
		if(i == 43)		// the fifth line
		{
			syzran = MENU_3_4_STATE_IDLE;
			NextMenuProcess3_4();
			break;
		}
   }
  HAL_Delay(50);
 }
}
/*----------------------------------------------------------------------------------
  * Function:		NextMenuProcess3_0(void)
  *----------------------------------------------------------------------------------
  * description:	Processing the third menu, item 0
  * parameters:		-
  *
  * on return:		-
  ------------------------------------------------------------------------------------*/
void NextMenuProcess3_0(void)
{
	while (1)
 {
  switch (moscow)
  {
  case MENU_3_0_STATE_IDLE:
	moscow = MENU_3_0_STATE_WAIT;
	SSD1309_init();
	SSD1309_ClearScreen();

	ssd1309_DrawCircle(3, 3, 2);
	SSD1309_GotoXY(10, 0);
/*	SSD1309_WriteString("Arbat", &Font_7x10);
	SSD1309_GotoXY(10, 10);
	SSD1309_WriteString("Tverskaya", &Font_7x10);
	SSD1309_GotoXY(10, 20);
	SSD1309_WriteString("Bolotnaya", &Font_7x10);
	SSD1309_GotoXY(10, 30);
	SSD1309_WriteString("Pyatnitskaya", &Font_7x10);*/
	SSD1309_UpdateScreen();

	   break;
/*	case MENU_3_0_STATE_WAIT:
			button_rattle_GPIO_E9();							// button click processing
			if (button_set_gpio_E9 == 1)							// button_set - flag on the button status
			{
				country = MENU_3_0_STATE_EXIT;
				button_set_gpio_E9 = 0;
			}
			break;
	case MENU_3_0_STATE_EXIT: //запуск главного меню
			city = MENU_2_STATE_IDLE;
			NextMenuProcess1();
			break;*/
  }
  HAL_Delay(50);
 }
}
/*----------------------------------------------------------------------------------
  * Function:		NextMenuProcess3_1(void)
  *----------------------------------------------------------------------------------
  * description:	Processing the third menu, item 1
  * parameters:		-
  *
  * on return:		-
  ------------------------------------------------------------------------------------*/
void NextMenuProcess3_1(void)
{
	while (1)
 {
  switch (st_peter)
  {
	case MENU_3_1_STATE_IDLE:
	st_peter = MENU_3_1_STATE_WAIT;
	SSD1309_init();
	SSD1309_ClearScreen();

	ssd1309_DrawCircle(3, 3, 2);
	SSD1309_GotoXY(10, 0);
	/*SSD1309_WriteString("Nevsky", &Font_7x10);
	SSD1309_GotoXY(10, 10);
	SSD1309_WriteString("Gorokhovaya", &Font_7x10);
	SSD1309_GotoXY(10, 20);
	SSD1309_WriteString("Kazanskaya", &Font_7x10);
	SSD1309_GotoXY(10, 30);
	SSD1309_WriteString("Sadovaya", &Font_7x10);*/
	SSD1309_UpdateScreen();

	   break;
/*	case MENU_3_1_STATE_WAIT:
			button_rattle_GPIO_E9();							// button click processing
			if (button_set_gpio_E9 == 1)							// button_set - flag on the button status
			{
				country = MENU_3_0_STATE_EXIT;
				button_set_gpio_E9 = 0;
			}
			break;
	case MENU_3_1_STATE_EXIT: //запуск главного меню
			city = MENU_2_STATE_IDLE;
			NextMenuProcess1();
			break;*/
  }
  HAL_Delay(50);
 }
}
/*----------------------------------------------------------------------------------
  * Function:		NextMenuProcess3_2(void)
  *----------------------------------------------------------------------------------
  * description:	Processing the third menu, item 2
  * parameters:		-
  *
  * on return:		-
  ------------------------------------------------------------------------------------*/
void NextMenuProcess3_2(void)
{
	while (1)
 {
  switch (kazan)
  {
  case MENU_3_2_STATE_IDLE:
  	kazan = MENU_3_2_STATE_WAIT;
  	SSD1309_init();
  	SSD1309_ClearScreen();

  	ssd1309_DrawCircle(3, 3, 2);
  	/*SSD1309_GotoXY(10, 0);
  	SSD1309_WriteString("Bauman", &Font_7x10);
  	SSD1309_GotoXY(10, 10);
  	SSD1309_WriteString("Tatarstan", &Font_7x10);
  	SSD1309_GotoXY(10, 20);
  	SSD1309_WriteString("Ershova", &Font_7x10);*/
  	SSD1309_UpdateScreen();
  	break;
  /*	case MENU_3_2_STATE_WAIT:
  			button_rattle_GPIO_E9();							// button click processing
  			if (button_set_gpio_E9 == 1)							// button_set - flag on the button status
  			{
  				country = MENU_3_0_STATE_EXIT;
  				button_set_gpio_E9 = 0;
  			}
  			break;
  	case MENU_3_2_STATE_EXIT: //запуск главного меню
  			city = MENU_2_STATE_IDLE;
  			NextMenuProcess1();
  			break;*/
  }
  HAL_Delay(50);
 }
}
/*----------------------------------------------------------------------------------
  * Function:		NextMenuProcess3_3(void)
  *----------------------------------------------------------------------------------
  * description:	Processing the third menu, item 3
  * parameters:		-
  *
  * on return:		-
  ------------------------------------------------------------------------------------*/
void NextMenuProcess3_3(void)
{
	while (1)
 {
  switch (ekatburg)
  {
  case MENU_3_3_STATE_IDLE:
    	ekatburg = MENU_3_3_STATE_WAIT;
    	SSD1309_init();
    	SSD1309_ClearScreen();

    	ssd1309_DrawCircle(3, 3, 2);
    	/*SSD1309_GotoXY(10, 0);
    	SSD1309_WriteString("Chelyuskintsev", &Font_7x10);
    	SSD1309_GotoXY(10, 10);
    	SSD1309_WriteString("East", &Font_7x10);
    	SSD1309_GotoXY(10, 20);
    	SSD1309_WriteString("Repina", &Font_7x10);*/
    	SSD1309_UpdateScreen();
    	break;
    /*	case MENU_3_3_STATE_WAIT:
    			button_rattle_GPIO_E9();							// button click processing
    			if (button_set_gpio_E9 == 1)							// button_set - flag on the button status
    			{
    				country = MENU_3_0_STATE_EXIT;
    				button_set_gpio_E9 = 0;
    			}
    			break;
    	case MENU_3_3_STATE_EXIT: //запуск главного меню
    			city = MENU_2_STATE_IDLE;
    			NextMenuProcess1();
    			break;*/
  }
  HAL_Delay(50);
 }
}
/*----------------------------------------------------------------------------------
  * Function:		NextMenuProcess3_4(void)
  *----------------------------------------------------------------------------------
  * description:	Processing the third menu, item 4
  * parameters:		-
  *
  * on return:		-
  ------------------------------------------------------------------------------------*/
void NextMenuProcess3_4(void)
{
	while (1)
 {
  switch (syzran)
  {
  case MENU_3_4_STATE_IDLE:
      	syzran = MENU_3_4_STATE_WAIT;
      	SSD1309_init();
      	SSD1309_ClearScreen();

      	ssd1309_DrawCircle(3, 3, 2);
      	SSD1309_GotoXY(10, 0);
      	/*SSD1309_WriteString("Uritsky", &Font_7x10);
      	SSD1309_GotoXY(10, 10);
      	SSD1309_WriteString("Chapaeva", &Font_7x10);
      	SSD1309_GotoXY(10, 20);
      	SSD1309_WriteString("Sovetskaya", &Font_7x10);
      	SSD1309_UpdateScreen();*/
      	break;
      /*	case MENU_3_4_STATE_WAIT:
      			button_rattle_GPIO_E9();							// button click processing
      			if (button_set_gpio_E9 == 1)							// button_set - flag on the button status
      			{
      				country = MENU_3_0_STATE_EXIT;
      				button_set_gpio_E9 = 0;
      			}
      			break;
      	case MENU_3_4_STATE_EXIT: //запуск главного меню
      			city = MENU_2_STATE_IDLE;
      			NextMenuProcess1();
      			break;*/
  }
  HAL_Delay(50);
 }
}

/*----------------------------------------------------------------------------------
  * Function:		button_rattle_GPIO_A0 (void)
  *----------------------------------------------------------------------------------
  * description:	Getting the state of the button PA0,
  * 				taking into account the rattle of contacts
  * parameters:		-
  *
  * on return:		-
  ------------------------------------------------------------------------------------*/
 void button_rattle_GPIO_A0 (void)
 {
	/* static uint8_t flag_key1_press = 1;
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
			button_set_gpio_A0 = 1;
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

	 if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET && flag_key1_press)
	 {
	   flag_key1_press = 0;
	   // Click Action
	   button_set_gpio_A0 = 1;
	   time_key1_press = HAL_GetTick();
	 }

	 if(!flag_key1_press && (HAL_GetTick() - time_key1_press) > 300)
	 {
	   flag_key1_press = 1;
	 }
}
 /*----------------------------------------------------------------------------------
   * Function:		button_rattle_GPIO_E7 (void)
   *----------------------------------------------------------------------------------
   * description:	Getting the state of the button PE7,
   * 				taking into account the rattle of contacts
   * parameters:		-
   *
   * on return:		-
   ------------------------------------------------------------------------------------*/
 void button_rattle_GPIO_E7 (void)
 {
	 static uint8_t flag_key1_press = 1;
	 	 static uint32_t time_key1_press = 0;

	 	 if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_7) == GPIO_PIN_SET && flag_key1_press)
	 	 {
	 	   flag_key1_press = 0;
	 	   // Click Action
	 	   button_set_gpio_E7 = 1;
	 	   time_key1_press = HAL_GetTick();
	 	 }

	 	 if(!flag_key1_press && (HAL_GetTick() - time_key1_press) > 300)
	 	 {
	 	   flag_key1_press = 1;
	 	 }
 }
 /*----------------------------------------------------------------------------------
   * Function:		button_rattle_GPIO_E8 (void)
   *----------------------------------------------------------------------------------
   * description:	Getting the state of the button PE8,
   * 				taking into account the rattle of contacts
   * parameters:		-
   *
   * on return:		-
   ------------------------------------------------------------------------------------*/
 void button_rattle_GPIO_E8 (void)
 {
	 static uint8_t flag_key1_press = 1;
	 	 static uint32_t time_key1_press = 0;

	 	 if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_8) == GPIO_PIN_SET && flag_key1_press)
	 	 {
	 	   flag_key1_press = 0;
	 	   // Click Action
	 	   button_set_gpio_E8 = 1;
	 	   time_key1_press = HAL_GetTick();
	 	 }

	 	 if(!flag_key1_press && (HAL_GetTick() - time_key1_press) > 300)
	 	 {
	 	   flag_key1_press = 1;
	 	 }
 }
 /*----------------------------------------------------------------------------------
   * Function:		button_rattle_GPIO_E9 (void)
   *----------------------------------------------------------------------------------
   * description:	Getting the state of the button PE9,
   * 				taking into account the rattle of contacts
   * parameters:		-
   *
   * on return:		-
   ------------------------------------------------------------------------------------*/
 void button_rattle_GPIO_E9 (void)
 {
	 static uint8_t flag_key1_press = 1;
	 	 static uint32_t time_key1_press = 0;

	 	 if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_9) == GPIO_PIN_SET && flag_key1_press)
	 	 {
	 	   flag_key1_press = 0;
	 	   // Click Action
	 	   button_set_gpio_E9 = 1;
	 	   time_key1_press = HAL_GetTick();
	 	 }

	 	 if(!flag_key1_press && (HAL_GetTick() - time_key1_press) > 300)
	 	 {
	 	   flag_key1_press = 1;
	 	 }
 }

