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

        //uint16_t m_u16XYCoordinates_initial[128]; //Array with (x,y) initial coordinates (old)
        //uint16_t g_u16XYCoordinates_f[128]; //Array with (x,y) final coordinates (new)

        uint16_t m_u16InitialValue;
        //int m_iDiffInitialPoint;
        //int m_iDiffFinalPoint;

        virtual uint8_t run(void);
        virtual uint8_t setup(void);

    protected:
    private:
};

#endif /* GETDIFFERENCE_HPP_ */
