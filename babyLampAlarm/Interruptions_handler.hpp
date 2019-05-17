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

//#include "Hardware_setup.hpp"

#ifndef INTERRUPTIONS_HANDLER_HPP_
#define INTERRUPTIONS_HANDLER_HPP_

#define LAMP_ON_INTERVAL 5

uint8_t g_u8OverThSampleCount;

uint16_t g_u16Adc14Result[6];   //Stores last 5s audio samples
uint16_t g_u16AudioAverage_5s;  //Stores last 5s average audio
uint16_t g_u16AudioAverage_1s;  //Stores last 1s average audio
uint32_t g_u32AudioSampleSum;   //Stores the total amount of audio sample's value in 1s

int g_iAudioThreshold;          //Stores the audio threshold that indicates when there is a crying
int g_iAudioSampleCount;        //Stores the amount of samples in 1s



#endif /* INTERRUPTIONS_HANDLER_HPP_ */
