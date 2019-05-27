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
#include "math.h"

/*--------------------------------------------------*/
//constructor
FillScreen::FillScreen()
{
    //...
}

/*--------------------------------------------------*/
/* Fills the screen with each color
 * it can be optimized by decreasing the filling area
 * uses Coordinates_ptr[i] values
 * expected to receive this values from a message
 */
uint8_t FillScreen::run()
{
    printf("--");
    int* Coordinates_ptr = this->DecodeMsgData();
//    printf("FillS received %p\n", Coordinates_ptr);

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
    } else if (g_fRollAngle <= M_PI/2 || g_fRollAngle > 3*M_PI/2) {
        for (uint8_t line_index = 0; line_index < 129; line_index++) {
            Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
            Graphics_drawLine(&g_sContext, line_index, Coordinates_ptr[line_index], line_index, 0);
            Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BROWN);
            Graphics_drawLine(&g_sContext, line_index, Coordinates_ptr[line_index], line_index, 128);
            g_u16XYCoordinates_previous[line_index] = Coordinates_ptr[line_index];
        }
    } else if (g_fRollAngle > M_PI/2 && g_fRollAngle <= 3*M_PI/2) {
        for (uint8_t line_index = 0; line_index < 129; line_index++) {
            Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BROWN);
            Graphics_drawLine(&g_sContext, line_index, Coordinates_ptr[line_index], line_index, 0);
            Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
            Graphics_drawLine(&g_sContext, line_index, Coordinates_ptr[line_index], line_index, 128);
            g_u16XYCoordinates_previous[line_index] = Coordinates_ptr[line_index];
        }
    }
    return(NO_ERR);
}

/*--------------------------------------------------*/
uint8_t FillScreen::setup(Mailbox *i_MailboxPtr)
{
    TaskMailbox = i_MailboxPtr;
    return(NO_ERR);
}

/*--------------------------------------------------*/
uint8_t FillScreen::BuildMsgData()
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
int* FillScreen::DecodeMsgData()
{

    st_MsgInfo ParametersReceived;
        if (TaskMailbox->CheckMailbox(m_u8TaskID)>0){

            ParametersReceived = TaskMailbox->SendMsg(m_u8TaskID-1,m_u8TaskID);
            m_lastCoodinates = ParametersReceived.data_ptr[0];
            return ParametersReceived.data_ptr[0];
        }
        else{
            return m_lastCoodinates;

        }
}
