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
//    printf("getborder->run\n");
//    int16_t g_u16XYCoordinates[129]; // Cambiar 129 por un parámetro
    // Esta lógica funciona para para un -45 < ángulo de roll < 45, puede copiar y cambiar una serie de parámetros para la lógica de los demás cuadrantes.
    for (uint16_t l_u16XpixelCounter = 0; l_u16XpixelCounter < 129; l_u16XpixelCounter++){
//            g_u16XYCoordinates[l_u16XpixelCounter] = - ( tan(g_fRollAngle)*(l_u16XpixelCounter - 64)
//                                                   + 64*sin(g_fPitchAngle)
//                                                   - 64 );

            m_oXYZarrayValues[l_u16XpixelCounter] = - ( tan(-g_fRollAngle)*(l_u16XpixelCounter - 64)
                                                           + 64*sin(g_fPitchAngle)
                                                           - 64 );
            if (m_oXYZarrayValues[l_u16XpixelCounter] > 128) {
//                g_u16XYCoordinates[l_u16XpixelCounter] = 129;
                m_oXYZarrayValues[l_u16XpixelCounter] = 129;
            } else if (m_oXYZarrayValues[l_u16XpixelCounter] < 0) {
//                g_u16XYCoordinates[l_u16XpixelCounter] = -1;
                m_oXYZarrayValues[l_u16XpixelCounter] = 0;
            }
    //        printf("Par ordenado X,Y:\t (%d,%d)\n",l_u16XpixelCounter,g_u16XYCoordinates[l_u16XpixelCounter]);
        }
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
    CoordinatesPtrMsg.data_ptr = m_oXYZarrayValues;
    TaskMailbox->ReceiveMsg(CoordinatesPtrMsg);
//    CoordinatesPtrMsg.destiny = m_u8TaskID + 2;
//    TaskMailbox->ReceiveMsg(CoordinatesPtrMsg);

    return 0;
}
/*--------------------------------------------------*/
uint16_t* GetBorder::DecodeMsgData()
{
    return nullptr;
}
