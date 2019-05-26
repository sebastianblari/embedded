/*
 * Mailbox.cpp
 *
 */

#include "Mailbox.hpp"

Mailbox::Mailbox(){}

uint8_t Mailbox::ReceiveMsg(st_MsgInfo NewMail){
    int l_iInstanceMsgCounter = msg_counter[NewMail.source];
    //Check the mailbox availability
    if (l_iInstanceMsgCounter<6){
        MsgBoard[NewMail.destiny][l_iInstanceMsgCounter] = NewMail;
        msg_counter[NewMail.destiny]++;
        return 1; //Message sucesfully saved
    }
    else{
        return 0; //Mailbox full
    }
}

int Mailbox::CheckMailbox(uint8_t TaskID){
    return msg_counter[TaskID];
}

st_MsgInfo Mailbox::SendMsg(uint8_t MsgSource, uint8_t MsgDestiny){
    bool l_msgfound = false;
    int index = msg_counter[MsgDestiny]-1;
    st_MsgInfo Msg;
    Msg.source = MsgSource;
    Msg.destiny = MsgDestiny;

    if (this->CheckMailbox(MsgSource)>0){
        while(!l_msgfound){
                if(MsgBoard[MsgDestiny][index].source == MsgSource){
                    Msg.data_ptr = MsgBoard[MsgDestiny][index].data_ptr;

                    msg_counter[MsgDestiny]--;
                    l_msgfound = true;
                }
                else if(index>0){
                    index--;}
                else{// doesnt found the header
                    l_msgfound = true;
                }
            }
        }
    return Msg;
}


Mailbox::~Mailbox()
{

}

