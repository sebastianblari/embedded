/*
 *
 * Filter.hpp
 *
 *  Created on: June 9, 2019
 *
 *      IE-1119 Temas Especiales II: Laboratorio de Introducción a los Sistemas Incrustados
 *
 *      Authors: Dunia, Laura, Sebastian
 */

#ifndef FILTER_HPP_
#define FILTER_HPP_

//#include "msp.h"

#define NO_ERR 0
#define RET_ERR 1

#include "Filter.hpp"

template <typename numType>
class Filter
{
	public:
		Filter();
		virtual numType getFilteredValue(void) = 0;
	private:
	   numType m_filteredValue;

};

#endif /* FILTER_HPP_ */
