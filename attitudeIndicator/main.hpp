/*
 * SMART LAMP
 *
 * main.hpp
 *
 *  Created on: Apr 15, 2019
 *
 *      IE-1119 Temas Especiales II: Laboratorio de Introducción a los Sistemas Incrustados
 *
 *      Authors: Dunia, Laura, Sebastian
 */

#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include <stdio.h>

//#include "HAL_I2C.h"
//#include "HAL_OPT3001.h"

#include "Hardware_setup.hpp"
#include "Interruptions_handler.hpp"

#ifndef MAIN_HPP_
#define MAIN_HPP_

/* Graphic library context */
Graphics_Context g_sContext;

/* ADC results buffer */
//static uint16_t resultsBuffer[3];

int g_iyInitPosition;
float g_fRollAngle;
float g_fPitchAngle;

void LCD_DrawStatus();
void LCD_DrawTitle();
void LCD_DrawAccelData();
void LCD_DrawRectangle(const int yInitPosition);
void LCD_DrawRollLine(const float i_fRollAngle, const float i_fPitchAngle);
void LCD_DrawRollRect (const float i_fRollAngle, const float i_fPitchAngle);

#endif /* MAIN_HPP_ */
