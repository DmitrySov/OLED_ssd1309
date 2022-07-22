/*
 * menu1.h
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
#include "printf.h"

void data_time (void);
void volume (void);
void expenses (void);
void temp_press(void);
void battery_status (void);

void tick_ms(void);
void get_time(void);
void menu_display (void);
void button_rattle_GPIO (GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

#endif /* INC_MENU1_H_ */
