/*
 * Task: FillScreen
 *
 * FillScreen.hpp
 *
 *  Created on: May 18, 2019
 *
 *      IE-1119 Temas Especiales II: Laboratorio de Introducción a los Sistemas Incrustados
 *
 *      Authors: Dunia, Laura, Sebastian
 */

#ifndef FILLSCREEN_HPP_
#define FILLSCREEN_HPP_

#include "Filter.hpp"

/* Class: FillScreen
 * inherit from Class Task
 */
class FillScreen //: public Task
{
    public:
        FillScreen(); //constructor
        int* m_piLastCoodinates;
        virtual int run(void);
        virtual int setup(void);
        int BuildMsgData(void);
        int* DecodeMsgData(void);

    protected:
    private:
};

#endif /* FILLSCREEN_HPP_ */
