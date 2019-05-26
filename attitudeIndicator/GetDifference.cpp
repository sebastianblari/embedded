/*
 * GetDifference.cpp
 *
 *  Created on: May 25, 2019
 *      Author: du
 */


#include "GetDifference.hpp"

/*--------------------------------------------------*/
//constructor
GetDifference::GetDifference()
{
    m_u16InitialValue = 0u;
    for (uint16_t l_u16CoordinateCounter = 0; l_u16CoordinateCounter < 129; l_u16CoordinateCounter++){
        g_u16XYCoordinates_initial[l_u16CoordinateCounter] = 0u;
    }
}

/*--------------------------------------------------*/
/*obtains the difference between initial and final point of previous and actual Border line
 * receives values from global variables
 * it is expected to receive and send values through messages*/
uint8_t GetDifference::run()
{
    //if initial point of the border line varies at least 10%
    if( (g_u16XYCoordinates[0] >= ((g_u16XYCoordinates_initial[0]*0.10)+g_u16XYCoordinates_initial[0]))||(g_u16XYCoordinates[0] <= (g_u16XYCoordinates_initial[0]-(g_u16XYCoordinates_initial[0]*0.10))) ){
        g_iDiffInitialPoint = static_cast<int>(g_u16XYCoordinates[0])-static_cast<int>(g_u16XYCoordinates_initial[0]);
        //printf("Initial \t %i \n", g_iDiffInitialPoint);
    }
    //if final point of the border line varies at least 10%
    if( (g_u16XYCoordinates[128] >= ((g_u16XYCoordinates_initial[128]*0.10)+g_u16XYCoordinates_initial[128]))||(g_u16XYCoordinates[128] <= (g_u16XYCoordinates_initial[128]-(g_u16XYCoordinates_initial[128]*0.10))) ){
        g_iDiffFinalPoint = static_cast<int>(g_u16XYCoordinates[128])-static_cast<int>(g_u16XYCoordinates_initial[128]);
        //printf("Final \t %i\n", g_iDiffFinalPoint);
    }

    //refresh old/initial border line to further comparisons
    for (uint16_t l_u16CoordinateCounter = 0; l_u16CoordinateCounter < 129; l_u16CoordinateCounter++){
        g_u16XYCoordinates_initial[l_u16CoordinateCounter] = g_u16XYCoordinates[l_u16CoordinateCounter];
    }
}

/*--------------------------------------------------*/
uint8_t GetDifference::setup()
{
    return(NO_ERR);
}
