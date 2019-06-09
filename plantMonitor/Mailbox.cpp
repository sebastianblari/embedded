/*
 * Mailbox.cpp
 *
 */

#include "Mailbox.hpp"

Mailbox::Mailbox(){
}


/*Message received the new message by a task, is saved in the m_stiMsgBoard
 * of the destiny and the respective counter also increments
 * */
uint8_t Mailbox::ReceiveMsg(st_MsgInfo i_stNewMail){

    int l_iInstanceMsgCounter = m_iMsgcounter[i_stNewMail.m_u8Destiny];
    //Check the mailbox availability
    if (l_iInstanceMsgCounter<NUMBER_MAX_MSG){
        m_stiMsgBoard[i_stNewMail.m_u8Destiny][l_iInstanceMsgCounter] = i_stNewMail;
        m_iMsgcounter[i_stNewMail.m_u8Destiny]++;
        return 1; //Message sucesfully saved
    }
    else{
        return 0; //Mailbox full
    }
}

/*Returns the amount of message saved for a certain task
 * */

int Mailbox::CheckMailbox(uint8_t i_u8TaskID){
    return m_iMsgcounter[i_u8TaskID];
}

/*Send/Returns the message with the type Source-Destiny specified,
 * and decrements the counter of message saved of the destiny
 * */

st_MsgInfo Mailbox::SendMsg(uint8_t i_u8MsgSource, uint8_t i_u8MsgDestiny){
    bool l_MsgFound = false;
    int l_iIndex = m_iMsgcounter[i_u8MsgDestiny]-1;
    st_MsgInfo l_stMsg;
    l_stMsg.m_u8Source = i_u8MsgSource;
    l_stMsg.m_u8Destiny = i_u8MsgDestiny;

    if (this->CheckMailbox(i_u8MsgDestiny)>0){
        while(!l_MsgFound){
                if(m_stiMsgBoard[i_u8MsgDestiny][l_iIndex].m_u8Source == i_u8MsgSource){
                    l_stMsg.m_piData= m_stiMsgBoard[i_u8MsgDestiny][l_iIndex].m_piData;

                    m_iMsgcounter[i_u8MsgDestiny]--;
                    l_MsgFound = true;
                }
                else if(l_iIndex>0){
                    l_iIndex--;}
                else{// doesnt found the header
                    l_MsgFound = true;
                    l_stMsg.m_piData= nullptr;
                }
            }
        }
    return l_stMsg;
}


Mailbox::~Mailbox()
{

}

