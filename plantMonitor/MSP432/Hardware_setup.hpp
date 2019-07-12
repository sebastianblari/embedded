/*
 * SETUP
 *
 * Hardware_setup.hpp
 *
 *  Created on: May 5, 2019
 *
 *      IE-1119 Temas Especiales II: Laboratorio de Introducción a los Sistemas Incrustados
 *
 *      Authors: Dunia, Laura, Sebastian
 */

#ifndef HARDWARE_SETUP_HPP_
#define HARDWARE_SETUP_HPP_

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/devices/msp432p4xx/inc/msp.h>
#include "Interruptions_handler.hpp"

void UartSetup(void);
void PinSetpu(void);
void InitialConditionsSetup(void);
void PowerUp(void);

#endif /* HARDWARE_SETUP_HPP_ */
