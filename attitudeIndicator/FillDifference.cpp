/*
 * GetDifference.cpp
 *
 *  Created on: May 25, 2019
 *      Author: du
 */


#include "FillDifference.hpp"

/*--------------------------------------------------*/
//constructor
FillDifference::FillDifference()
{
    //...
}

/*--------------------------------------------------*/
//determines the color based on the difference between initial and final points of previous and actual border line
uint8_t FillDifference::run()
{
    if(g_iDiffInitialPoint > 0){
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);

        if(g_iDiffFinalPoint < 0){
            m_u16InitialValue = 0;
            fill();
            Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BROWN);
            fill();
            m_u16InitialValue = 0u;
        }
        else{
            m_u16InitialValue = 0;
            fill();
        }
    }

    else if(g_iDiffInitialPoint < 0){
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BROWN);

        if(g_iDiffFinalPoint > 0){
            m_u16InitialValue = 0;
            fill();
            Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
            fill();
            m_u16InitialValue = 0;
        }
        else{
            m_u16InitialValue = 0;
            fill();
        }
    }

    else{
        if(g_iDiffFinalPoint > 0){
            Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
            m_u16InitialValue = 0;
            fill();
        }
        else if(g_iDiffFinalPoint > 0){
            Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BROWN);
            m_u16InitialValue = 0;
            fill();
        }
    }
    return(NO_ERR);
}

/*--------------------------------------------------*/
uint8_t FillDifference::setup()
{
    return(NO_ERR);
}

/*--------------------------------------------------*/
//draws the lines to fill the differential area
uint8_t FillDifference::fill()
{
    for (uint8_t line_index = m_u16InitialValue; line_index < 129; line_index++) {
        Graphics_drawLine(&g_sContext, line_index, g_u16XYCoordinates[line_index], line_index, g_u16XYCoordinates_initial[line_index]);

        if (g_u16XYCoordinates[line_index] == g_u16XYCoordinates_initial[line_index]){
            m_u16InitialValue = line_index + 1;
            line_index = 129;
        }
    }
    return(NO_ERR);
}
