/*
 * Filter
 *
 * Filter.hpp
 *
 *  Created on: June 9, 2019
 *
 *      IE-1119 Temas Especiales II: Laboratorio de Introducción a los Sistemas Incrustados
 *
 *      Authors: Dunia, Laura, Sebastian
 */

#include "LowPassFilter.hpp"

template<typename numTypeReadValue, typename numTypeSmoothingFactor>
LowPassFilter<numTypeReadValue, numTypeSmoothingFactor>::LowPassFilter(numTypeSmoothingFactor i_smoothingFactorValue)
{
    this->previousFilteredValue = 0;
    this->smoothingFactorValue = i_smoothingFactorValue;
}

template<typename numTypeReadValue, typename numTypeSmoothingFactor>
numTypeReadValue LowPassFilter<numTypeReadValue, numTypeSmoothingFactor>::getFilteredValue(numTypeReadValue i_actualReadValue){
    this->m_filteredValue = this->previousFilteredValue + this->smoothingFactorValue * (i_actualReadValue - this->previousFilteredValue);
    return this->m_filteredValue;
}


