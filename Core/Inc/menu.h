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
  MENU_2_STATE_WAIT_1,
  MENU_2_STATE_WAIT_2,
  MENU_2_STATE_WAIT_3,
}MENU2_StateTypeDef;

void main_menu(void);
void NextMenuProcess(void);
void button_rattle(void);

#endif /* INC_MENU_H_ */
