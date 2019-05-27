/*
 * GetDifference.cpp
 *
 *  Created on: May 25, 2019
 *      Author: du
 */


#include "GetDifference.hpp"

/*--------------------------------------------------*/
//constructor
GetDifference::GetDifference()
{
    m_u16InitialValue = 0u;
    for (uint16_t l_u16CoordinateCounter = 0; l_u16CoordinateCounter < 129; l_u16CoordinateCounter++){
        g_u16XYCoordinates_initial[l_u16CoordinateCounter] = 0u;
    }
}

/*--------------------------------------------------*/
/*obtains the difference between initial and final point of previous and actual Border line
 * receives values from global variables
 * it is expected to receive and send values through messages*/
uint8_t GetDifference::run()
{
    uint16_t* Coordinates_ptr = DecodeMsgData();
    //if initial point of the border line varies at least 10%
    if( (Coordinates_ptr[0] >= ((g_u16XYCoordinates_initial[0]*0.10)+g_u16XYCoordinates_initial[0]))||(Coordinates_ptr[0] <= (g_u16XYCoordinates_initial[0]-(g_u16XYCoordinates_initial[0]*0.10))) ){
        g_iDiffInitialPoint = static_cast<int>(Coordinates_ptr[0])-static_cast<int>(g_u16XYCoordinates_initial[0]);
        //printf("Initial \t %i \n", g_iDiffInitialPoint);
    }
    //if final point of the border line varies at least 10%
    if( (Coordinates_ptr[128] >= ((g_u16XYCoordinates_initial[128]*0.10)+g_u16XYCoordinates_initial[128]))||(Coordinates_ptr[128] <= (g_u16XYCoordinates_initial[128]-(g_u16XYCoordinates_initial[128]*0.10))) ){
        g_iDiffFinalPoint = static_cast<int>(Coordinates_ptr[128])-static_cast<int>(g_u16XYCoordinates_initial[128]);
        //printf("Final \t %i\n", g_iDiffFinalPoint);
    }

    //refresh old/initial border line to further comparisons
    for (uint16_t l_u16CoordinateCounter = 0; l_u16CoordinateCounter < 129; l_u16CoordinateCounter++){
        g_u16XYCoordinates_initial[l_u16CoordinateCounter] = Coordinates_ptr[l_u16CoordinateCounter];
    }
}

/*--------------------------------------------------*/
uint8_t GetDifference::setup(Mailbox *i_MailboxPtr)
{
    TaskMailbox = i_MailboxPtr;
    return(NO_ERR);
}
/*--------------------------------------------------*/
uint8_t GetDifference::BuidMsgData()
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
uint16_t* GetDifference::DecodeMsgData()
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
