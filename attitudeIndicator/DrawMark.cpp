/*
 * Task: DrawMark
 *
 * DrawMark.cpp
 *
 *  Created on: May 18, 2019
 *
 *      IE-1119 Temas Especiales II: Laboratorio de Introducción a los Sistemas Incrustados
 *
 *      Authors: Dunia, Laura, Sebastian
 */

#include "DrawMark.hpp"

/*--------------------------------------------------*/
//constructor
DrawMark::DrawMark()
{
    //...
}

/*--------------------------------------------------*/
/* Draws the white line/mark that divides horizon
 * uses g_u16XYCoordinates[0] and g_u16XYCoordinates[128]
 * expected to receive this values from a message
 */
uint8_t DrawMark::run()
{
//    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
//    Graphics_drawLine(&g_sContext, 0, g_u16XYCoordinates[0], 128, g_u16XYCoordinates[128]);

    return(NO_ERR);
}

/*--------------------------------------------------*/
uint8_t DrawMark::setup()
{
    return(NO_ERR);
}
