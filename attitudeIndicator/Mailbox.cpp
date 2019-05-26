/*
 * Mailbox.cpp
 *
 */

#include <Mailbox.hpp>

Mailbox::Mailbox(){}

uint8_t Mailbox::ReceiveMsg(st_MsgInfo NewMail){
    int l_iInstanceMsgCounter = msg_counter[NewMail.source];
    //Check the mailbox availability
    if (l_iInstanceMsgCounter<6){
        MsgBoard[NewMail.source][l_iInstanceMsgCounter] = NewMail;
        msg_counter[NewMail.source]++;
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
    bool l_msgfind = false;
    int index = msg_counter[MsgSource]-1;
    st_MsgInfo Msg;
    Msg.source = MsgSource;
    Msg.destiny = MsgDestiny;

    if (this->CheckMailbox(MsgSource)>0){
        while(!l_msgfind){
                if(MsgBoard[MsgSource][index].destiny == MsgDestiny){
                    Msg.data_ptr = MsgBoard[MsgSource][index].data_ptr;
                    for(int i = 0; i<8; i++){
                        Msg.data[i] = MsgBoard[MsgSource][index].data[i];
                    }

                    msg_counter[MsgSource]--;
                    l_msgfind = true;
                }
                else if(index>0){
                    index--;}
                else{// doesnt header found
                    l_msgfind = true;
                }
            }
        }
    return Msg;
}


Mailbox::~Mailbox()
{

}

