/*
 * Task: DrawMark
 *
 * DrawMark.cpp
 *
 *  Created on: May 18, 2019
 *
 *      IE-1119 Temas Especiales II: Laboratorio de Introducción a los Sistemas Incrustados
 *
 *      Authors: Dunia, Laura, Sebastian
 */

#include "DrawMark.hpp"

/*--------------------------------------------------*/
//constructor
DrawMark::DrawMark()
{
//    m_lastCoodinates = nullptr;
}

/*--------------------------------------------------*/
/* Draws the white line/mark that divides horizon
 * uses g_u16XYCoordinates[0] and g_u16XYCoordinates[128]
 * expected to receive this values from a message
 */
uint8_t DrawMark::run()
{
//    printf("drawmark->run\n");
    uint16_t* Coordinates_ptr = DecodeMsgData();
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_GREEN);
//    printf("(0,%d)->(128,%d)\n",g_u16XYCoordinates[0],g_u16XYCoordinates[128]);
//    for (int index = 0; index < 129; index++){
//        printf("Par ordenado X,Y:\t (%d,%d)\n",index,g_u16XYCoordinates[index]);
//    }
//    Graphics_drawLine(&g_sContext, 0, 128, 128, 128);
    Graphics_drawLine(&g_sContext, 0, Coordinates_ptr[0], 128, Coordinates_ptr[128]);
    BuidMsgData();
    return(NO_ERR);
}

/*--------------------------------------------------*/
uint8_t DrawMark::setup(Mailbox *i_MailboxPtr)
{
   TaskMailbox = i_MailboxPtr;

    return(NO_ERR);
}
/*--------------------------------------------------*/
uint8_t DrawMark::BuidMsgData()
{
    st_MsgInfo CoordinatesPtrMsg;
    CoordinatesPtrMsg.source = m_u8TaskID;
    CoordinatesPtrMsg.destiny = m_u8TaskID + 1;

    //building the message
    CoordinatesPtrMsg.data_ptr = m_lastCoodinates;
    TaskMailbox->ReceiveMsg(CoordinatesPtrMsg);

    return 0;
}

uint16_t* DrawMark::DecodeMsgData()
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
