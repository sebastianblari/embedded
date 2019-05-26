/*
 * Task :FillDIfference
 *
 * FillDifference.hpp
 *
 *  Created on: May 25, 2019
 *
 *      IE-1119 Temas Especiales II: Laboratorio de Introducción a los Sistemas Incrustados
 *
 *      Authors: Dunia, Laura, Sebastian
 */

#ifndef FILLDIFFERENCE_HPP_
#define FILLDIFFERENCE_HPP_

#include "Task.hpp"

/* Class: FillDifference
 * inherit from Class Task
 */
class FillDifference : public Task
{
    public:
        FillDifference(); //constructor

        //uint16_t m_u16XYCoordinates_initial[128]; //Array with (x,y) initial coordinates (old)
        //uint16_t g_u16XYCoordinates_f[128]; //Array with (x,y) final coordinates (new)

        uint16_t m_u16InitialValue;

        virtual uint8_t run(void);
        virtual uint8_t setup(void);
        uint8_t fill();

    protected:
    private:
};

#endif /* FILLDIFFERENCE_HPP_ */
