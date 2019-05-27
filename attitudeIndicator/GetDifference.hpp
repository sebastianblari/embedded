/*
 * GetDifference.hpp
 *
 *  Created on: May 25, 2019
 *      Author: du
 */

#ifndef GETDIFFERENCE_HPP_
#define GETDIFFERENCE_HPP_

#include "Task.hpp"

/* Class: GetDifference
 * inherit from Class Task
 */
class GetDifference : public Task
{
    public:
        GetDifference(); //constructor

        uint16_t m_u16InitialValue;
        int* m_lastCoodinates;

        virtual uint8_t run(void);
        virtual uint8_t setup(Mailbox *i_MailboxPtr);
        uint8_t BuildMsgData(void);
        int* DecodeMsgData(void);

    protected:
    private:
};

#endif /* GETDIFFERENCE_HPP_ */
