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
  MENU_STATE = 0,
  MENU_STATE_WAIT,
  MENU_STATE_MAIN,
}MENU_StateTypeDef;

void main_menu(void);

#endif /* INC_MENU_H_ */
