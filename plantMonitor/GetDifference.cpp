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

}


uint8_t GetDifference::FillScreenDiff()
{

}

uint8_t GetDifference::FillScreenTot()
{
}



/*--------------------------------------------------*/
//Saves the mailbox instance pointer
uint8_t GetDifference::setup(Mailbox *i_MailboxPtr)
{
//    m_pTaskMailbox = i_MailboxPtr;
//    return(NO_ERR);
}
/*--------------------------------------------------*/
/*Builds the data of the message, to be send for a the
 * next task */
uint8_t GetDifference::BuildMsgData()
{
//    st_MsgInfo l_stCoordinatesPtrMsg;
//    l_stCoordinatesPtrMsg.m_u8Source = m_u8TaskID;
//    l_stCoordinatesPtrMsg.m_u8Destiny = m_u8TaskID + 1;
//
//    //building the message
//    l_stCoordinatesPtrMsg.m_piData = m_piLastCoodinates;
//    m_pTaskMailbox->ReceiveMsg(l_stCoordinatesPtrMsg);
//
//    return (NO_ERR);
}
/*--------------------------------------------------*/
/*Decodes the data message, received from a the
 * previous task */
int* GetDifference::DecodeMsgData()
{
//    st_MsgInfo l_stReceivedParameters;
//        if (m_pTaskMailbox->CheckMailbox(m_u8TaskID)>0){
//            l_stReceivedParameters = m_pTaskMailbox->SendMsg(m_u8TaskID-2,m_u8TaskID);
//            m_piLastCoodinates = l_stReceivedParameters.m_piData;
//            return l_stReceivedParameters.m_piData;
//        }
//        else{
//            return m_piLastCoodinates;
//
//        }
}
