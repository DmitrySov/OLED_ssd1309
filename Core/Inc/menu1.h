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
#include "printf.h"

typedef enum {
  DATA_TIME_MAIN = 0,
  DATA_TIME_1_WAIT,
}DATA_TIME_StateTypeDef;

typedef enum{
  VOLUME_MAIN = 0,
  VOLUME_WAIT,
}VOLUME_StateTypeDef;

typedef enum{
  EXPENSES_MAIN = 0,
  EXPENSES_WAIT,
}EXPENSES_StateTypeDef;

typedef enum {
  TEMP_PRESS_MAIN = 0,
  TEMP_PRESS_WAIT,
}TEMP_PRESS_StateTypeDef;

typedef enum {
   BATT_STATUS_MAIN = 0,
   BATT_STATUS_WAIT,
}BATT_STATUS_StateTypeDef;

typedef enum {
  AXIS_1_MAIN = 0,
  AXIS_1_WAIT,
}AXIS_StateTypeDef;

typedef enum
{
	axis, data, temperature, humidity,
} counter_button_t;

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
