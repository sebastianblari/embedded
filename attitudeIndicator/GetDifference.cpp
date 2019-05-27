/*
 * GetDifference.cpp
 *
 *  Created on: May 25, 2019
 *      Author: du
 */

#include "Mailbox.hpp"
#include "GetDifference.hpp"
#include "math.h"
/*--------------------------------------------------*/
//constructor
GetDifference::GetDifference()
{
    m_u16InitialValue = 0u;
}

/*--------------------------------------------------*/
/*obtains the difference between initial and final point of previous and actual Border line
 * receives values from global variables
 * it is expected to receive and send values through messages*/
uint8_t GetDifference::run()
{

    int* Coordinates_ptr = DecodeMsgData();
    if(g_fPitchAngle <=  M_PI/2 && g_fPitchAngle >=  0.95*M_PI/2) {
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BROWN);
        Graphics_Rectangle t_Rectangle2 = {0,0,128,128};
        Graphics_fillRectangle(&g_sContext, &t_Rectangle2);
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
        Graphics_drawLine(&g_sContext, 0, 0, 128, 0);
        for (uint8_t line_index = 0; line_index < 129; line_index++){
            g_u16XYCoordinates_previous[line_index] = Coordinates_ptr[line_index];
        }
    } else if (g_fPitchAngle <=  -0.95*M_PI/2 && g_fPitchAngle >=  -M_PI/2) {
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
        Graphics_Rectangle t_Rectangle2 = {0,128,128,128};
        Graphics_fillRectangle(&g_sContext, &t_Rectangle2);
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
        Graphics_drawLine(&g_sContext, 0, 128, 128, 128);
        for (uint8_t line_index = 0; line_index < 129; line_index++){
            g_u16XYCoordinates_previous[line_index] = Coordinates_ptr[line_index];
        }
    }
    if (g_fRollAngle <= M_PI/2 || g_fRollAngle > 3*M_PI/2) {
        for (uint8_t line_index = 0; line_index < 129; line_index++) {
            if(Coordinates_ptr[line_index] >= g_u16XYCoordinates_previous[line_index]){
                Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
                Graphics_drawLine(&g_sContext, line_index, Coordinates_ptr[line_index], line_index, g_u16XYCoordinates_previous[line_index]);
            } else if (Coordinates_ptr[line_index] < g_u16XYCoordinates_previous[line_index]){
                Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BROWN);
                Graphics_drawLine(&g_sContext, line_index, g_u16XYCoordinates_previous[line_index], line_index, Coordinates_ptr[line_index]);
            }
            g_u16XYCoordinates_previous[line_index] = Coordinates_ptr[line_index];
        }
    } else if (g_fRollAngle > M_PI/2 && g_fRollAngle <= 3*M_PI/2) {
        for (uint8_t line_index = 0; line_index < 129; line_index++) {
            if (Coordinates_ptr[line_index] >= g_u16XYCoordinates_previous[line_index]) {
                Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BROWN);
                Graphics_drawLine(&g_sContext, line_index, Coordinates_ptr[line_index], line_index, g_u16XYCoordinates_previous[line_index]);
            } else if (Coordinates_ptr[line_index] < g_u16XYCoordinates_previous[line_index]) {
                Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
                Graphics_drawLine(&g_sContext, line_index, g_u16XYCoordinates_previous[line_index], line_index, Coordinates_ptr[line_index]);
            }
            g_u16XYCoordinates_previous[line_index] = Coordinates_ptr[line_index];
        }
    }
    return(NO_ERR);
}

//    //m_iDiffInitialPoint = static_cast<int>(g_u16XYCoordinates[0])-static_cast<int>(m_u16XYCoordinates_initial[0]);
//    //m_iDiffFinalPoint = static_cast<int>(g_u16XYCoordinates[128])-static_cast<int>(m_u16XYCoordinates_initial[128]);
//
//    //((m_u16XYCoordinates_initial[0]*0.1)+m_u16XYCoordinates_initial[0])
//
//    if( (g_u16XYCoordinates[0] >= ((g_u16XYCoordinates_initial[0]*0.10)+g_u16XYCoordinates_initial[0]))||(g_u16XYCoordinates[0] <= (g_u16XYCoordinates_initial[0]-(g_u16XYCoordinates_initial[0]*0.10))) ){
//        m_iDiffInitialPoint = static_cast<int>(g_u16XYCoordinates[0])-static_cast<int>(g_u16XYCoordinates_initial[0]);
////        printf("Initial \t %i \n", m_iDiffInitialPoint);
//        //fill2();
//    }
//    if( (g_u16XYCoordinates[128] >= ((g_u16XYCoordinates_initial[128]*0.10)+g_u16XYCoordinates_initial[128]))||(g_u16XYCoordinates[128] <= (g_u16XYCoordinates_initial[128]-(g_u16XYCoordinates_initial[128]*0.10))) ){
//        m_iDiffFinalPoint = static_cast<int>(g_u16XYCoordinates[128])-static_cast<int>(g_u16XYCoordinates_initial[128]);
////        printf("Final \t %i\n", m_iDiffFinalPoint);
//        //fill2();
//    }
//    //printf("Initial \t %i \nFinal \t %i\n", m_iDiffInitialPoint,m_iDiffFinalPoint);
//    /**********************************/
//
//    /**********************************/
//    //si uno es positivo y el otro negativo
//    //cuando son iguales empieza a pintar azul desde el nuevo hasta el viejo
//    for (uint16_t l_u16CoordinateCounter = 0; l_u16CoordinateCounter < 129; l_u16CoordinateCounter++){
//        g_u16XYCoordinates_initial[l_u16CoordinateCounter] = g_u16XYCoordinates[l_u16CoordinateCounter];
//    }
//    return 0;
//}

/*--------------------------------------------------*/
uint8_t GetDifference::setup(Mailbox *i_MailboxPtr)
{
    TaskMailbox = i_MailboxPtr;
    return(NO_ERR);
}
/*--------------------------------------------------*/
uint8_t GetDifference::BuildMsgData()
{
    st_MsgInfo CoordinatesPtrMsg;
    CoordinatesPtrMsg.source = m_u8TaskID;
    CoordinatesPtrMsg.destiny = m_u8TaskID + 1;

    //building the message
    CoordinatesPtrMsg.data_ptr[0] = m_lastCoodinates;
    TaskMailbox->ReceiveMsg(CoordinatesPtrMsg);

    return 0;
}
/*--------------------------------------------------*/
int* GetDifference::DecodeMsgData()
{
    st_MsgInfo ParametersReceived;
        if (TaskMailbox->CheckMailbox(m_u8TaskID)>0){
            ParametersReceived = TaskMailbox->SendMsg(m_u8TaskID-2,m_u8TaskID);
            m_lastCoodinates = ParametersReceived.data_ptr[0];
            return ParametersReceived.data_ptr[0];
        }
        else{
            return m_lastCoodinates;

        }
}
