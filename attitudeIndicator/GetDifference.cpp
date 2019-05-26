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
//refresh the initial value of coordinates
uint8_t GetDifference::run()
{
    //m_iDiffInitialPoint = static_cast<int>(g_u16XYCoordinates[0])-static_cast<int>(m_u16XYCoordinates_initial[0]);
    //m_iDiffFinalPoint = static_cast<int>(g_u16XYCoordinates[128])-static_cast<int>(m_u16XYCoordinates_initial[128]);

    //((m_u16XYCoordinates_initial[0]*0.1)+m_u16XYCoordinates_initial[0])

    if( (g_u16XYCoordinates[0] >= ((g_u16XYCoordinates_initial[0]*0.10)+g_u16XYCoordinates_initial[0]))||(g_u16XYCoordinates[0] <= (g_u16XYCoordinates_initial[0]-(g_u16XYCoordinates_initial[0]*0.10))) ){
        m_iDiffInitialPoint = static_cast<int>(g_u16XYCoordinates[0])-static_cast<int>(g_u16XYCoordinates_initial[0]);
//        printf("Initial \t %i \n", m_iDiffInitialPoint);
        //fill2();
    }
    if( (g_u16XYCoordinates[128] >= ((g_u16XYCoordinates_initial[128]*0.10)+g_u16XYCoordinates_initial[128]))||(g_u16XYCoordinates[128] <= (g_u16XYCoordinates_initial[128]-(g_u16XYCoordinates_initial[128]*0.10))) ){
        m_iDiffFinalPoint = static_cast<int>(g_u16XYCoordinates[128])-static_cast<int>(g_u16XYCoordinates_initial[128]);
//        printf("Final \t %i\n", m_iDiffFinalPoint);
        //fill2();
    }
    //printf("Initial \t %i \nFinal \t %i\n", m_iDiffInitialPoint,m_iDiffFinalPoint);
    /**********************************/

    /**********************************/
    //si uno es positivo y el otro negativo
    //cuando son iguales empieza a pintar azul desde el nuevo hasta el viejo
    for (uint16_t l_u16CoordinateCounter = 0; l_u16CoordinateCounter < 129; l_u16CoordinateCounter++){
        g_u16XYCoordinates_initial[l_u16CoordinateCounter] = g_u16XYCoordinates[l_u16CoordinateCounter];
    }
    return 0;
}

/*--------------------------------------------------*/
uint8_t GetDifference::setup(Mailbox *i_MailboxPtr)
{
    return(NO_ERR);
}

/*--------------------------------------------------*/
uint8_t GetDifference::fill()
{
    for (uint8_t line_index = m_u16InitialValue; line_index < 129; line_index++) {
        Graphics_drawLine(&g_sContext, line_index, g_u16XYCoordinates[line_index], line_index, g_u16XYCoordinates_initial[line_index]);

        if (g_u16XYCoordinates[line_index] == g_u16XYCoordinates_initial[line_index]){
            m_u16InitialValue = line_index + 1;
            line_index = 129;
        }
        /*else{
            l_u16InitialValue = 0u;
        }*/
    }
    return 0;
}

/*--------------------------------------------------*/
uint8_t GetDifference::fill2()
{
    if(m_iDiffInitialPoint > 0){
                Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);

                if(m_iDiffFinalPoint < 0){
                    //Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
                    m_u16InitialValue = 0;
                    fill();
                    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BROWN);
                    fill();
                    m_u16InitialValue = 0u;
                }
                //si punto inicial es positivo empieza pintar cafe hasta que las coordenadas sean iguales desde el nuevo hasta el viejo
                //else if(l_iDiffFinalPoint < 0){
                else{
                    //Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
                    m_u16InitialValue = 0;
                    fill();
                }
            }
            //si los dos son negativos pinta cafe
            else if(m_iDiffInitialPoint < 0){
                Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BROWN);
            //si es cero o negativo
                if(m_iDiffFinalPoint > 0){
                    //Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BROWN);
                    m_u16InitialValue = 0;
                    fill();
                    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
                    fill();
                    m_u16InitialValue = 0;
                }
                //else if(l_iDiffFinalPoint > 0){
                else{
                    //Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BROWN);
                    m_u16InitialValue = 0;
                    fill();
                }
            }
            else{
                if(m_iDiffFinalPoint > 0){
                    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
                    m_u16InitialValue = 0;
                    fill();
                }
                else if(m_iDiffFinalPoint > 0){
                    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BROWN);
                    m_u16InitialValue = 0;
                    fill();
                }
            }
    return 0;
}
