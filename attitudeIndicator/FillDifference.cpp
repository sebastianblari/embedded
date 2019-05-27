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
uint8_t FillDifference::setup(Mailbox *i_MailboxPtr)
{
    TaskMailbox = i_MailboxPtr;
    return(NO_ERR);
}

/*--------------------------------------------------*/
//draws the lines to fill the differential area
uint8_t FillDifference::fill()
{
    uint16_t* Coordinates_ptr = DecodeMsgData();
    for (uint8_t line_index = m_u16InitialValue; line_index < 129; line_index++) {
        Graphics_drawLine(&g_sContext, line_index, Coordinates_ptr[line_index], line_index, g_u16XYCoordinates_initial[line_index]);

        if (Coordinates_ptr[line_index] == g_u16XYCoordinates_initial[line_index]){
            m_u16InitialValue = line_index + 1;
            line_index = 129;
        }
    }
    return(NO_ERR);
}
/*--------------------------------------------------*/
uint8_t FillDifference::BuidMsgData()
{
    st_MsgInfo CoordinatesPtrMsg;
    CoordinatesPtrMsg.source = m_u8TaskID;
    CoordinatesPtrMsg.destiny = m_u8TaskID + 1;

    //building the message
    CoordinatesPtrMsg.data_ptr = m_lastCoodinates;
    TaskMailbox->ReceiveMsg(CoordinatesPtrMsg);

    return 0;
}
/*--------------------------------------------------*/
uint16_t* FillDifference::DecodeMsgData()
{
    st_MsgInfo ParametersReceived;
        if (TaskMailbox->CheckMailbox(m_u8TaskID)>0){
            ParametersReceived = TaskMailbox->SendMsg(m_u8TaskID-1,m_u8TaskID);
            m_lastCoodinates = ParametersReceived.data_ptr;
            return ParametersReceived.data_ptr;
        }
        else{
            return m_lastCoodinates;

        }
}
