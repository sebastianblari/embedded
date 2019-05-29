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


#define TIMER32_COUNT_1ms   0x00000BB7
#define TIMER32_COUNT_100ms 0x000493DF


void LCD_setup(void);
void T32_2_setup(void);
void ADC_setup(void);

void InitialConditions_setup(void);
void Power_up(void);

#endif /* HARDWARE_SETUP_HPP_ */
