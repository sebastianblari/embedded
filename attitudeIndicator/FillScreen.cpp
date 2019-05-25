/*
 * Task: FillScreen
 *
 * FillScreen.cpp
 *
 *  Created on: May 18, 2019
 *
 *      IE-1119 Temas Especiales II: Laboratorio de Introducción a los Sistemas Incrustados
 *
 *      Authors: Dunia, Laura, Sebastian
 */
#include "FillScreen.hpp"

/*--------------------------------------------------*/
//constructor
FillScreen::FillScreen()
{
    //...
}

/*--------------------------------------------------*/
/* Fills the screen with each color
 * it can be optimized by decreasing the filling area
 * uses g_u16XYCoordinates[i] values
 * expected to receive this values from a message
 */
uint8_t FillScreen::run()
{
//    for (uint8_t line_index = 0; line_index < 129; line_index++) {
//        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
//        Graphics_drawLine(&g_sContext, line_index, g_u16XYCoordinates[line_index] - 1, line_index, 0);
//        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BROWN);
//        Graphics_drawLine(&g_sContext, line_index, g_u16XYCoordinates[line_index] + 1, line_index, 128);
//    }
    return(NO_ERR);
}

/*--------------------------------------------------*/
uint8_t FillScreen::setup()
{
    return(NO_ERR);
}


