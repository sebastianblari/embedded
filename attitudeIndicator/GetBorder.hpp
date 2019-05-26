/*
 * Task: GetBorder
 *
 * GetBorder.hpp
 *
 *  Created on: May 18, 2019
 *
 *      IE-1119 Temas Especiales II: Laboratorio de Introducción a los Sistemas Incrustados
 *
 *      Authors: Dunia, Laura, Sebastián
 */


#ifndef GETBORDER_HPP_
#define GETBORDER_HPP_

#include "math.h"
#include "Task.hpp"

#define __NOP __nop
#define PIXELS 128 //cantidad de pixeles

/* Class: GetBorder
 * inherit from Class Task
 */
class GetBorder : public Task
{
    public:
        GetBorder(); //constructor
        uint16_t* m_lastCoodinates;
        virtual uint8_t run(void);
        virtual uint8_t setup(Mailbox *i_MailboxPtr);
        uint8_t BuidMsgData(void);
        uint16_t* DecodeMsgData(void);

    protected:
    private:
};

#endif /* GETBORDER_HPP_ */
