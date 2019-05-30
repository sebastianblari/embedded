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
int g_iXYCoordinatesPrevious[128];
Graphics_Context g_sContext; //Graphic library context
float g_fRollAngle; //angle
float g_fPitchAngle;//angle
int g_iyInitPosition;


bool done;

int g_i16XFilteredGravityVector;
int g_i16YFilteredGravityVector;
int g_i16ZFilteredGravityVector;

#endif /* MAIN_HPP_ */
