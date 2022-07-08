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
  AXIS_1_MAIN = 0,
  AXIS_1_WAIT,
}AXIS_StateTypeDef;

typedef enum {
  DATA_1_MAIN = 0,
  //DATA_1_WAIT,
}DATA_StateTypeDef;

typedef enum
{
	axis, data, temperature, humidity,
} counter_button_t;


void menu_display (void);
void start_menu (void);
void button_rattle_GPIO (GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

#endif /* INC_MENU1_H_ */
