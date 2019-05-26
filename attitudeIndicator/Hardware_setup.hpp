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

/* T interrupts with 48MHz clock and clock divided by 16 */
#define TIMER32_COUNT_1us 0x00000002  //~1us
#define TIMER32_COUNT_5us 0x0000000E  //~5us
#define TIMER32_COUNT_8us 0x00000017  //~8us
#define TIMER32_COUNT_10us    0x0000001D  //~10us
#define TIMER32_COUNT_100us   0x0000012B  //~100us
#define TIMER32_COUNT_250us   0x000002ED  //~250us
#define TIMER32_COUNT_500Us   0x000005DB
#define TIMER32_COUNT_1ms 0x00000BB7
#define TIMER32_COUNT_5ms 0x00003A97
#define TIMER32_COUNT_10ms    0x0000752F
#define TIMER32_COUNT_100ms   0x000493DF
#define TIMER32_COUNT_300ms   0x00000383
#define TIMER32_COUNT_350ms   0x0010058F
#define TIMER32_COUNT_400ms   0x00124F7F
#define TIMER32_COUNT_450ms   0x0014996F
#define TIMER32_COUNT_500ms   0x0016E35F
#define TIMER32_COUNT_1s  0x002DC6BF

/* T interrupts with 48MHz clock and clock divided by 256 */
//#define TIMER32_COUNT_500ms 0x00016E35    //~0.5s
//#define TIMER32_COUNT_1s 0x0002DC6B   //~1s
#define TIMER32_COUNT_5s 0x000E4E1B   //~5s
#define TIMER32_COUNT_60s 0x00ABA94F  //~60s
#define TIMER32_COUNT_30s 0x0055D4A7  //~30s

void LCD_setup(void);
void Pin_setup(void);
void T32_1_setup(void);
void T32_2_setup(void);
void ADC_setup(void);

void InitialConditions_setup(void);
void Power_up(void);

#endif /* HARDWARE_SETUP_HPP_ */
