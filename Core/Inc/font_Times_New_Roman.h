/*
 * font_Times_New_Roman.h
 *
 *  Created on: 16 θών. 2022 γ.
 *      Author: sovetnikov
 */

#ifndef INC_FONT_TIMES_NEW_ROMAN_H_
#define INC_FONT_TIMES_NEW_ROMAN_H_

#include <main.h>
#include "font_Times_New_Roman.h"
#include <stdint.h>

 typedef enum
{
	 pt8 = 0,
	 pt10,
	 pt14,
	 pt16,
}TimNewRom;

typedef struct{
	uint16_t a;

};

//extern typePt_t type_Pt;
/* Font data for Times New Roman 8pt */
extern const uint8_t timesNewRoman_8ptBitmaps[];
extern const uint16_t timesNewRoman_8ptDescriptors[226][2];

/* Font data for Times New Roman 10pt */
extern const uint8_t timesNewRoman_10ptBitmaps[];
extern const uint16_t timesNewRoman_10ptDescriptors[226][2];

/* Font data for Times New Roman 14pt */
extern const uint8_t timesNewRoman_14ptBitmaps[];
extern const uint16_t timesNewRoman_14ptDescriptors[226][2];

/* Font data for Times New Roman 16pt */
extern const uint8_t timesNewRoman_16ptBitmaps[];
extern const uint16_t timesNewRoman_16ptDescriptors[226][2];

#endif /* INC_FONT_TIMES_NEW_ROMAN_H_ */
