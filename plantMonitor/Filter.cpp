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

#include "Filter.hpp"

template<typename numType>
Filter<numType>::Filter()
{

}
template<typename numType>
numType Filter<numType>::getFilteredValue(){
    return this->m_filteredValue;
}


