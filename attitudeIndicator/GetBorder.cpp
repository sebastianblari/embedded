/*
 * Task: GetBorder
 *
 * GetBorder.cpp
 *
 *  Created on: May 18, 2019
 *
 *      IE-1119 Temas Especiales II: Laboratorio de Introducción a los Sistemas Incrustados
 *
 *      Authors: Dunia, Laura, Sebastian
 */

#include "GetBorder.hpp"

/*--------------------------------------------------*/
//constructor
GetBorder::GetBorder()
{
    //...
}

/*--------------------------------------------------*/
/* Obtains the necessary coordinates to delimit the horizon line
 * saves this coordinates in the g_u16XYCoordinates array
 * expected to send this array to DrawMark and FillScreen Tasks as a message
 * only works in a range within +-45 degrees
 * uses g_fRollAngle and g_fPitchAngle given by the ADC14 converter
 * expected to receive this values from a message
 */
uint8_t GetBorder::run()
{
//    for (uint16_t l_u16XpixelCounter = 0; l_u16XpixelCounter < 129; l_u16XpixelCounter++){
//        g_u16XYCoordinates[l_u16XpixelCounter] = abs( tan(g_fRollAngle)*(l_u16XpixelCounter - 64)
//                                                      + 64*sin(g_fPitchAngle)
//                                                      - 64 );
//    }

    return(NO_ERR);
}

//---------------------------------------------------
uint8_t GetBorder::setup()
{
    return(NO_ERR);
}
