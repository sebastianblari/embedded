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
 * it is expected to receive values through messages*/

uint8_t GetDifference::run()
{
    if(g_fRollAngle >=  0.8*M_PI/2 && g_fRollAngle <=  1.2*M_PI/2){
        FillScreenTot();
    } else if (g_fRollAngle >=  0.8*3*M_PI/2 && g_fRollAngle <=  1.2*3*M_PI/2) {
        FillScreenTot();
    } else {
        FillScreenDiff();
    }
    return (NO_ERR);
}


uint8_t GetDifference::FillScreenDiff()
{
    int* l_piXYCoordinates = DecodeMsgData();
    if(g_fPitchAngle <=  M_PI/2 && g_fPitchAngle >=  0.95*M_PI/2) {
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BROWN);
        Graphics_Rectangle t_Rectangle1 = {0,0,127,127};
        Graphics_fillRectangle(&g_sContext, &t_Rectangle1);
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
        Graphics_drawLine(&g_sContext, 0, 0, 127, 0);
        for (uint8_t line_index = 0; line_index < 128; line_index++){
            g_iXYCoordinatesPrevious[line_index] = l_piXYCoordinates[line_index];

        }
    } else if (g_fPitchAngle <=  -0.95*M_PI/2 && g_fPitchAngle >=  -M_PI/2) {
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
        Graphics_Rectangle t_Rectangle2 = {0,0,127,127};
        Graphics_fillRectangle(&g_sContext, &t_Rectangle2);
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
        Graphics_drawLine(&g_sContext, 0, 127, 127, 127);
        for (uint8_t line_index = 0; line_index < 128; line_index++){
            g_iXYCoordinatesPrevious[line_index] = l_piXYCoordinates[line_index];
        }
    } else if (g_fRollAngle <= M_PI/2 || g_fRollAngle > 3*M_PI/2) {
        for (uint8_t line_index = 0; line_index < 128; line_index++) {
            if(l_piXYCoordinates[line_index] >= g_iXYCoordinatesPrevious[line_index]){
                Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
                Graphics_drawLine(&g_sContext, line_index, l_piXYCoordinates[line_index], line_index, g_iXYCoordinatesPrevious[line_index]);
            } else if (l_piXYCoordinates[line_index] < g_iXYCoordinatesPrevious[line_index]){
                Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BROWN);
                Graphics_drawLine(&g_sContext, line_index, g_iXYCoordinatesPrevious[line_index], line_index, l_piXYCoordinates[line_index]);
            }
            Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
            Graphics_drawLine(&g_sContext, line_index, l_piXYCoordinates[line_index], line_index, l_piXYCoordinates[line_index]);
            g_iXYCoordinatesPrevious[line_index] = l_piXYCoordinates[line_index];
        }
    } else if (g_fRollAngle > M_PI/2 && g_fRollAngle <= 3*M_PI/2) {
        for (uint8_t line_index = 0; line_index < 128; line_index++) {
            if (l_piXYCoordinates[line_index] >= g_iXYCoordinatesPrevious[line_index]) {
                Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BROWN);
                Graphics_drawLine(&g_sContext, line_index, l_piXYCoordinates[line_index], line_index, g_iXYCoordinatesPrevious[line_index]);
            } else if (l_piXYCoordinates[line_index] < g_iXYCoordinatesPrevious[line_index]) {
                Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
                Graphics_drawLine(&g_sContext, line_index, g_iXYCoordinatesPrevious[line_index], line_index, l_piXYCoordinates[line_index]);
            }
            Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
            Graphics_drawLine(&g_sContext, line_index, l_piXYCoordinates[line_index], line_index, l_piXYCoordinates[line_index]);
            g_iXYCoordinatesPrevious[line_index] = l_piXYCoordinates[line_index];
        }
    }
    return(NO_ERR);
}

uint8_t GetDifference::FillScreenTot()
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
            Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
            Graphics_drawLine(&g_sContext, line_index, l_piXYCoordinates[line_index], line_index, l_piXYCoordinates[line_index]);
            g_iXYCoordinatesPrevious[line_index] = l_piXYCoordinates[line_index];
        }
    } else if (g_fRollAngle > M_PI/2 && g_fRollAngle <= 3*M_PI/2) {
        for (uint8_t line_index = 0; line_index < 128; line_index++) {
            Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BROWN);
            Graphics_drawLine(&g_sContext, line_index, l_piXYCoordinates[line_index], line_index, 0);
            Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
            Graphics_drawLine(&g_sContext, line_index, l_piXYCoordinates[line_index], line_index, 127);
            Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
            Graphics_drawLine(&g_sContext, line_index, l_piXYCoordinates[line_index], line_index, l_piXYCoordinates[line_index]);
            g_iXYCoordinatesPrevious[line_index] = l_piXYCoordinates[line_index];
            g_iXYCoordinatesPrevious[line_index] = l_piXYCoordinates[line_index];
        }
    }
    return(NO_ERR);
}



/*--------------------------------------------------*/
//Saves the mailbox instance pointer
uint8_t GetDifference::setup(Mailbox *i_MailboxPtr)
{
    m_pTaskMailbox = i_MailboxPtr;
    return(NO_ERR);
}
/*--------------------------------------------------*/
/*Builds the data of the message, to be send for a the
 * next task */
uint8_t GetDifference::BuildMsgData()
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
/*Decodes the data message, received from a the
 * previous task */
int* GetDifference::DecodeMsgData()
{
    st_MsgInfo l_stReceivedParameters;
        if (m_pTaskMailbox->CheckMailbox(m_u8TaskID)>0){
            l_stReceivedParameters = m_pTaskMailbox->SendMsg(m_u8TaskID-2,m_u8TaskID);
            m_piLastCoodinates = l_stReceivedParameters.m_piData;
            return l_stReceivedParameters.m_piData;
        }
        else{
            return m_piLastCoodinates;

        }
}
