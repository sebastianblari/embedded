/*
 * Mailbox.hpp
 *
 *  Created on: May 18, 2019
 *      Author: laura
 */

#ifndef MAILBOX_HPP_
#define MAILBOX_HPP_

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>


const uint8_t NUMBERS_OF_TASKS_INSTANCES =  5;
const uint8_t NUMBER_MAX_MSG =  6;
struct st_MsgInfo {
    uint8_t m_u8Source;
    uint8_t m_u8Destiny;
    int* m_piData;
};

class Mailbox
{
public:
    Mailbox();
    /*arreglo de contadores de mensajes para cada instacia de tarea, donde cada instancia tiene su propio id
     * y el id va a a ser indice del arreglo*/
    int m_iMsgcounter [NUMBERS_OF_TASKS_INSTANCES] = {};
    st_MsgInfo m_stiMsgBoard [NUMBERS_OF_TASKS_INSTANCES][NUMBER_MAX_MSG];

    uint8_t ReceiveMsg(st_MsgInfo);
    int CheckMailbox(uint8_t);
    st_MsgInfo SendMsg(uint8_t,uint8_t);
    virtual ~Mailbox();
};

#endif /* MAILBOX_HPP_ */
