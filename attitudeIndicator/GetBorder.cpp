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
 * saves this coordinates in the m_iXYCoordinates array
 * expected to send this array to FillScreen and GetDifference Tasks as a message
 * uses g_fRollAngle and g_fPitchAngle given by the ADC14 converter
 */
uint8_t GetBorder::run()
{

    for (uint16_t l_u16XpixelCounter = 0; l_u16XpixelCounter < PIXELS; l_u16XpixelCounter++){
        if(g_fPitchAngle <=  M_PI/2 && g_fPitchAngle >=  0.95*M_PI/2) {
                m_iXYCoordinates[l_u16XpixelCounter] = 0;
            } else if (g_fPitchAngle <=  -0.95*M_PI/2 && g_fPitchAngle >=  -M_PI/2) {
                m_iXYCoordinates[l_u16XpixelCounter] = PIXELS-2;
            } else {
                m_iXYCoordinates[l_u16XpixelCounter] = - ( tan(-g_fRollAngle)*(l_u16XpixelCounter - 64)
                                                               + 64*sin(g_fPitchAngle)
                                                               - 64 );
                if (m_iXYCoordinates[l_u16XpixelCounter] > PIXELS-1) {

                    m_iXYCoordinates[l_u16XpixelCounter] = PIXELS;
                } else if (m_iXYCoordinates[l_u16XpixelCounter] < 0) {

                    m_iXYCoordinates[l_u16XpixelCounter] = 0;
                }

            }
    }
        BuildMsgData();
        return(NO_ERR);
}

//---------------------------------------------------
//Saves the mailbox instance pointer
uint8_t GetBorder::setup(Mailbox *i_pMailboxPtr)
{
    m_pTaskMailbox = i_pMailboxPtr;
    return(NO_ERR);
}
/*--------------------------------------------------*/
/*Builds the data of the message, to be send for a the
 * next task */
uint8_t GetBorder::BuildMsgData()
{
    st_MsgInfo l_stCoordinatesPtrMsg;
    l_stCoordinatesPtrMsg.m_u8Source = m_u8TaskID;
    l_stCoordinatesPtrMsg.m_u8Destiny = m_u8TaskID + 1;

    //building the message
    l_stCoordinatesPtrMsg.m_piData = m_iXYCoordinates;
    m_pTaskMailbox->ReceiveMsg(l_stCoordinatesPtrMsg);

    l_stCoordinatesPtrMsg.m_u8Destiny = m_u8TaskID + 2;
    m_pTaskMailbox->ReceiveMsg(l_stCoordinatesPtrMsg);


    return(NO_ERR);
}
