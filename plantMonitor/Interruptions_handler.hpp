/*
 * INTERRUPTIONS
 *
 * Interruptions_handler.hpp
 *
 *  Created on: Apr 15, 2019
 *
 *      IE-1119 Temas Especiales II: Laboratorio de Introducción a los Sistemas Incrustados
 *
 *      Authors: Dunia, Laura, Sebastian
 */

#ifndef INTERRUPTIONS_HANDLER_HPP_
#define INTERRUPTIONS_HANDLER_HPP_

#include <stdio.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* GLOBAL VARIABLES */
uint64_t g_SystemTicks;         //The system counter
uint8_t g_u8BytesCounter;       //Counter of bytes received
uint16_t g_u16BytesReceived;    //Save the bytes received


#endif /* INTERRUPTIONS_HANDLER_HPP_ */
