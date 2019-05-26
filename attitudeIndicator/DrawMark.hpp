/*
 * Task: DrawMark
 *
 * DrawMark.hpp
 *
 *  Created on: May 18, 2019
 *
 *      IE-1119 Temas Especiales II: Laboratorio de Introducción a los Sistemas Incrustados
 *
 *      Authors: Dunia, Laura, Sebastian
 */

#ifndef DRAWMARK_HPP_
#define DRAWMARK_HPP_

#include "Task.hpp"

/* Class: DrawMark
 * inherit from Class Task
 */
class DrawMark : public Task
{
    public:
        DrawMark(); //constructor
        uint16_t* m_lastCoodinates;
        virtual uint8_t run(void);
        virtual uint8_t setup(Mailbox *i_MailboxPtr);
        uint8_t BuidMsgData(void);
        uint16_t* DecodeMsgData(void);

    protected:
    private:
};

#endif /* DRAWMARK_HPP_ */
