/*
 *
 * LowPassFilter.hpp
 *
 *  Created on: June 9, 2019
 *
 *      IE-1119 Temas Especiales II: Laboratorio de Introducción a los Sistemas Incrustados
 *
 *      Authors: Dunia, Laura, Sebastian
 */

#ifndef LOWPASSFILTER_HPP_
#define LOWPASSFILTER_HPP_

#include "Filter.hpp"

/* Class: LowPassFilter
 * inherit from Class Filter
 */
template<typename numTypeReadValue, typename numTypeSmoothingFactor>
class LowPassFilter : public Filter<numTypeReadValue>
{
    public:
        LowPassFilter(numTypeSmoothingFactor i_smoothingFactorValue); //constructor
        numTypeReadValue getFilteredValue(numTypeReadValue i_actualReadValue);
    private:
        numTypeSmoothingFactor smoothingFactorValue;
        numTypeReadValue previousFilteredValue;
    protected:

};

#endif /* LOWPASSFILTER_HPP_ */
