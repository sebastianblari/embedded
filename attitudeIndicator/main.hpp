/*
 * ATTITUDE INDICATOR
 *
 * main.hpp
 *
 *  Created on: May 1, 2019
 *
 *      IE-1119 Temas Especiales II: Laboratorio de Introducción a los Sistemas Incrustados
 *
 *      Authors: Dunia, Laura, Sebastian
 */

#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>

#include "LcdDriver/Crystalfontz128x128_ST7735.h"
//#include "HAL_I2C.h"
//#include "HAL_OPT3001.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "Hardware_setup.hpp"
#include "Interruptions_handler.hpp"

#ifndef MAIN_HPP_
#define MAIN_HPP_

/* GLOBAL VARIABLES */
uint16_t g_u16XYCoordinates[128]; //Array with (x,y) coordinates to determine limits
Graphics_Context g_sContext; //Graphic library context
float g_fRollAngle; //angle
float g_fPitchAngle;//angle
int g_iyInitPosition;

/* FUNCTIONS */
void LCD_DrawStatus();
void LCD_DrawTitle();
void LCD_DrawAccelData();
void LCD_DrawRectangle(const int yInitPosition);
void LCD_DrawRollLine(const float i_fRollAngle, const float i_fPitchAngle);
void LCD_DrawRollRect (const float i_fRollAngle, const float i_fPitchAngle);

#endif /* MAIN_HPP_ */
