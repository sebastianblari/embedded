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


#define TIMER32_COUNT_1ms 0x00000BB7

void T32_2_setup(void);
void Uart_setup(void);
void Pin_setpu(void);
void InitialConditions_setup(void);
void Power_up(void);

#endif /* HARDWARE_SETUP_HPP_ */
