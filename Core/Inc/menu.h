/*
 * menu.h
 *
 *  Created on: 20 мая 2022 г.
 *      Author: sovetnikov
 */

#ifndef INC_MENU_H_
#define INC_MENU_H_

#include "main.h"
#include "stdint.h"
#include "stm32f4xx_hal.h"
#include "ssd_1309.h"
//------------------------------------------------
typedef enum {
  MENU_1_STATE_IDLE = 0,
  MENU_1_STATE_WAIT,
  MENU_1_STATE_MAIN,
}MENU1_StateTypeDef;

typedef enum{
  MENU_2_STATE_IDLE = 0,
  MENU_2_STATE_WAIT,
  MENU_2_STATE_EXIT,
  MENU_2_STATE_P0,
  MENU_2_STATE_ENTER,
 /* MENU_2_STATE_P1,
  MENU_2_STATE_P2,
  MENU_2_STATE_P3,
  MENU_2_STATE_P4,*/
}MENU2_StateTypeDef;

typedef enum{
	/*Arbat,
	Tverskaya,
	Bolotnaya,
	Pyatnitskaya,*/
	 MENU_3_0_STATE_IDLE = 0,
	 MENU_3_0_STATE_WAIT,
	 MENU_3_0_STATE_EXIT,
}MENU3_MOSCOW_StateTypedef;

typedef enum{
	/*Nevsky,
	Gorokhovaya,
	Kazanskaya,
	Sadovaya,*/
	MENU_3_1_STATE_IDLE = 0,
    MENU_3_1_STATE_WAIT,
    MENU_3_1_STATE_EXIT,
}MENU3_SAINT_PETERSBURG_StateTypedef;

typedef enum{
	/*Bauman,
	Tatarstan,
	Ershova,*/
	MENU_3_2_STATE_IDLE = 0,
	MENU_3_2_STATE_WAIT,
	MENU_3_2_STATE_EXIT,
}MENU3_KAZAN_StateTypedef;

typedef enum{
	/*Chelyuskintsev,
	East,
	Repina,*/
	MENU_3_3_STATE_IDLE = 0,
	MENU_3_3_STATE_WAIT,
	MENU_3_3_STATE_EXIT,
}MENU3_EKATERINBURG_StateTypedef;

typedef enum{
	/*Uritsky,
	Chapaeva,
	Sovetskaya,*/
	MENU_3_4_STATE_IDLE = 0,
	MENU_3_4_STATE_WAIT,
	MENU_3_4_STATE_EXIT,
}MENU3_SYZRAN_StateTypedef;

void main_menu(void);
void NextMenuProcess1(void);
void NextMenuProcess2_0(void);
void NextMenuProcess2_1(void);
void NextMenuProcess2_3(void);
void NextMenuProcess2_4(void);
void button_rattle_GPIO_A0(void);
void button_rattle_GPIO_E7(void);
void button_rattle_GPIO_E8(void);
void button_rattle_GPIO_E9(void);


#endif /* INC_MENU_H_ */
