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

#ifndef LOWPASSFILTER_HPP
#define LOWPASSFILTER_HPP

#include "Filter.hpp"

/* Class: LowPassFilter
 * inherit from Class Filter
 */
template<typename numTypeReadValue, typename numTypeSmoothingFactor>
class LowPassFilter : public Filter<numTypeReadValue>
{
    public:
        LowPassFilter(numTypeSmoothingFactor i_smoothingFactorValue); //constructor
        LowPassFilter(void); //constructor
        ~LowPassFilter(void); //constructor
        numTypeReadValue filterSignal(numTypeReadValue i_actualReadValue);
    private:
        numTypeSmoothingFactor smoothingFactorValue;
        numTypeReadValue previousFilteredValue;
    protected:

};

template<typename numTypeReadValue, typename numTypeSmoothingFactor>
LowPassFilter<numTypeReadValue, numTypeSmoothingFactor>::LowPassFilter(numTypeSmoothingFactor i_smoothingFactorValue)
{
    this->previousFilteredValue = 0;
    this->smoothingFactorValue = i_smoothingFactorValue;
}

template<typename numTypeReadValue, typename numTypeSmoothingFactor>
LowPassFilter<numTypeReadValue, numTypeSmoothingFactor>::LowPassFilter(void )
{
    this->previousFilteredValue = 0;
}

template<typename numTypeReadValue, typename numTypeSmoothingFactor>
LowPassFilter<numTypeReadValue, numTypeSmoothingFactor>::~LowPassFilter()
{
}

template<typename numTypeReadValue, typename numTypeSmoothingFactor>
numTypeReadValue LowPassFilter<numTypeReadValue, numTypeSmoothingFactor>::filterSignal(numTypeReadValue i_actualReadValue){
    this->m_filteredValue = this->previousFilteredValue + this->smoothingFactorValue * (i_actualReadValue - this->previousFilteredValue);
    this->previousFilteredValue = this->m_filteredValue;
    return this->m_filteredValue;
}
#endif /* LOWPASSFILTER_HPP */
