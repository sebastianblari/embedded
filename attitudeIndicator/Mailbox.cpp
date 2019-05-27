/*
 * Mailbox.cpp
 *
 */

#include "Mailbox.hpp"

Mailbox::Mailbox(){
}

uint8_t Mailbox::ReceiveMsg(st_MsgInfo NewMail){

    int l_iInstanceMsgCounter = msg_counter[NewMail.destiny];
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

    if (this->CheckMailbox(MsgDestiny)>0){
        while(!l_msgfound){
                if(MsgBoard[MsgDestiny][index].source == MsgSource){
                    Msg.data_ptr[0] = MsgBoard[MsgDestiny][index].data_ptr[0];
                    Msg.data_ptr[1] = MsgBoard[MsgDestiny][index].data_ptr[1];

                    msg_counter[MsgDestiny]--;
                    l_msgfound = true;
                }
                else if(index>0){
                    index--;}
                else{// doesnt found the header
                    l_msgfound = true;
                    Msg.data_ptr[0] = nullptr;
                }
            }
        }
    return Msg;
}


Mailbox::~Mailbox()
{

}

