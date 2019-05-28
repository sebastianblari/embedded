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

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "Hardware_setup.hpp"
#include "Interruptions_handler.hpp"

#ifndef MAIN_HPP_
#define MAIN_HPP_

/* GLOBAL VARIABLES */
int g_u16XYCoordinates[129]; //Array with (x,y) coordinates to determine limits
int g_u16XYCoordinates_previous[129];
Graphics_Context g_sContext; //Graphic library context
float g_fRollAngle; //angle
float g_fPitchAngle;//angle
int g_iyInitPosition;

int g_iDiffInitialPoint;
int g_iDiffFinalPoint;

bool done;

int fXg;
int fYg;
int fZg;

#endif /* MAIN_HPP_ */
