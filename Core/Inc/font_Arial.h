/*
 * font_Arial.h
 *      Author: Sovetnikov
 */

#ifndef INC_FONT_ARIAL_H_
#define INC_FONT_ARIAL_H_

#include <main.h>
#include "font_Times_New_Roman.h"
#include <stdint.h>

/* Font data for Arial 8pt */
extern const uint8_t Arial_8ptBitmaps[];
extern const uint16_t Arial_8ptDescriptors[226][2];

/* Font data for Arial 10pt */
extern const uint8_t Arial_10ptBitmaps[];
extern const uint16_t Arial_10ptDescriptors[226][2];

/* Font data for Arial 12pt */
extern const uint8_t Arial_12ptBitmaps[];
extern const uint16_t Arial_12ptDescriptors[226][2];

/* Font data for Times New Roman 14pt */
extern const uint8_t Arial_14ptBitmaps[];
extern const uint16_t Arial_14ptDescriptors[226][2];

/* Font data for Times New Roman 16pt */
//extern const uint8_t Arial_16ptBitmaps[];
//extern const uint16_t Arial_16ptDescriptors[226][2];

#endif /* INC_FONT_ARIAL_H_ */
