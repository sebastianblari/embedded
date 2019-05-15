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
#include <stdio.h>
#include <stdint.h>

#include "HAL_I2C.h"
#include "HAL_OPT3001.h"

#include "Hardware_setup.hpp"
#include "Interruptions_handler.hpp"

#ifndef MAIN_HPP_
#define MAIN_HPP_

#define LED_CTRL P2
#define SYSTEM_WATTS 15
#define LIGHT_THRESHOLD 30

uint8_t g_u8Flags;
int g_iLampOnCount;
float g_fSensorLux;


#endif /* MAIN_HPP_ */
