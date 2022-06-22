/*
 * menu1.h
 *
 *  Created on: 21 θών. 2022 γ.
 *      Author: sovetnikov
 */

#ifndef INC_MENU1_H_
#define INC_MENU1_H_

#include "main.h"
#include "stdint.h"
#include "stm32f4xx_hal.h"
#include "ssd_1309.h"
#include "string.h"
#include "stdio.h"

typedef enum {
  MENU_1_START = 0,
  MENU_1_MAIN,
  MENU_1_WAIT,
}MENU1_StateTypeDef;

void start_menu (void);
void button_rat_GPIO_A0 (void);

#endif /* INC_MENU1_H_ */
