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
/* Fills the screen with each color for the first time
 * uses l_piXYCoordinates[i] values
 * expected to receive this pointer from a message
 */
uint8_t FillScreen::run()
{
    int* l_piXYCoordinates = DecodeMsgData();

    if(g_fPitchAngle <=  M_PI/2 && g_fPitchAngle >=  0.95*M_PI/2) {
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BROWN);
        Graphics_Rectangle t_Rectangle2 = {0,0,127,127};
        Graphics_fillRectangle(&g_sContext, &t_Rectangle2);
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
        Graphics_drawLine(&g_sContext, 0, 0, 127, 0);
        for (uint8_t line_index = 0; line_index < 128; line_index++){
            g_iXYCoordinatesPrevious[line_index] = l_piXYCoordinates[line_index];
        }
    } else if (g_fPitchAngle <=  -0.95*M_PI/2 && g_fPitchAngle >=  -M_PI/2) {
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
        Graphics_Rectangle t_Rectangle2 = {0,127,127,127};
        Graphics_fillRectangle(&g_sContext, &t_Rectangle2);
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
        Graphics_drawLine(&g_sContext, 0, 127, 127, 127);
        for (uint8_t line_index = 0; line_index < 128; line_index++){
            g_iXYCoordinatesPrevious[line_index] = l_piXYCoordinates[line_index];
        }
    } else if (g_fRollAngle <= M_PI/2 || g_fRollAngle > 3*M_PI/2) {
        for (uint8_t line_index = 0; line_index < 128; line_index++) {
            Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
            Graphics_drawLine(&g_sContext, line_index, l_piXYCoordinates[line_index], line_index, 0);
            Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BROWN);
            Graphics_drawLine(&g_sContext, line_index, l_piXYCoordinates[line_index], line_index, 127);
            g_iXYCoordinatesPrevious[line_index] = l_piXYCoordinates[line_index];
        }
    } else if (g_fRollAngle > M_PI/2 && g_fRollAngle <= 3*M_PI/2) {
        for (uint8_t line_index = 0; line_index < 128; line_index++) {
            Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BROWN);
            Graphics_drawLine(&g_sContext, line_index, l_piXYCoordinates[line_index], line_index, 0);
            Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
            Graphics_drawLine(&g_sContext, line_index, l_piXYCoordinates[line_index], line_index, 127);
            g_iXYCoordinatesPrevious[line_index] = l_piXYCoordinates[line_index];
        }
    }
    return(NO_ERR);
}

/*--------------------------------------------------*/
//Saves the mailbox instance pointer
uint8_t FillScreen::setup(Mailbox *i_pMailboxPtr)
{
    m_pTaskMailbox = i_pMailboxPtr;
    return(NO_ERR);
}

/*--------------------------------------------------*/
/*Builds the data of the message, to be send for a the
 * next task */
uint8_t FillScreen::BuildMsgData()
{
    st_MsgInfo l_stCoordinatesPtrMsg;
    l_stCoordinatesPtrMsg.m_u8Source = m_u8TaskID;
    l_stCoordinatesPtrMsg.m_u8Destiny = m_u8TaskID + 1;

    //building the message
    l_stCoordinatesPtrMsg.m_piData = m_piLastCoodinates;
    m_pTaskMailbox->ReceiveMsg(l_stCoordinatesPtrMsg);

    return (NO_ERR);
}
/*--------------------------------------------------*/
/*Decodes the data message received from a the
 * previous task */
int* FillScreen::DecodeMsgData()
{

    st_MsgInfo ParametersReceived;
        if (m_pTaskMailbox->CheckMailbox(m_u8TaskID)>0){

            ParametersReceived = m_pTaskMailbox->SendMsg(m_u8TaskID-1,m_u8TaskID);
            m_piLastCoodinates = ParametersReceived.m_piData;
            return ParametersReceived.m_piData;
        }
        else{
            return m_piLastCoodinates;

        }
}
