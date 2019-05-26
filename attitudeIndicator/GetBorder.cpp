/*
 * Task: GetBorder
 *
 * GetBorder.cpp
 *
 *  Created on: May 18, 2019
 *
 *      IE-1119 Temas Especiales II: Laboratorio de Introducción a los Sistemas Incrustados
 *
 *      Authors: Dunia, Laura, Sebastian
 */

#include "GetBorder.hpp"

/*--------------------------------------------------*/
//constructor
GetBorder::GetBorder()
{
    //...
}

/*--------------------------------------------------*/
/* Obtains the necessary coordinates to delimit the horizon line
 * saves this coordinates in the g_u16XYCoordinates array
 * expected to send this array to DrawMark and FillScreen Tasks as a message
 * only works in a range within +-45 degrees
 * uses g_fRollAngle and g_fPitchAngle given by the ADC14 converter
 * expected to receive this values from a message
 */
uint8_t GetBorder::run()
{
    uint16_t* Coordinates_ptr = DecodeMsgData();
//    for (uint16_t l_u16XpixelCounter = 0; l_u16XpixelCounter < 129; l_u16XpixelCounter++){
//        g_u16XYCoordinates[l_u16XpixelCounter] = abs( tan(g_fRollAngle)*(l_u16XpixelCounter - 64)
//                                                      + 64*sin(g_fPitchAngle)
//                                                      - 64 );
//    }
    BuidMsgData();
    return(NO_ERR);
}

//---------------------------------------------------
uint8_t GetBorder::setup(Mailbox *i_MailboxPtr)
{
    TaskMailbox = i_MailboxPtr;
    return(NO_ERR);
}
/*--------------------------------------------------*/
uint8_t GetBorder::BuidMsgData()
{
    st_MsgInfo CoordinatesPtrMsg;
    CoordinatesPtrMsg.source = m_u8TaskID;
    CoordinatesPtrMsg.destiny = m_u8TaskID + 1;

    //building the message
    CoordinatesPtrMsg.data_ptr = g_u16XYCoordinates;
    TaskMailbox->ReceiveMsg(CoordinatesPtrMsg);

    return 0;
}
/*--------------------------------------------------*/
uint16_t* GetBorder::DecodeMsgData()
{
    st_MsgInfo ParametersReceived;
    if (TaskMailbox->CheckMailbox(m_u8TaskID)>0){
        ParametersReceived = TaskMailbox->SendMsg(m_u8TaskID-1,m_u8TaskID);
        m_lastCoodinates = ParametersReceived.data_ptr;
    }
    else{
        ParametersReceived.data_ptr = m_lastCoodinates;

    }
    return(ParametersReceived.data_ptr);
}
