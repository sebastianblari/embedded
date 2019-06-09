/*
 * Sensor.cpp
 *
 *  Created on: Jun 9, 2019
 *      Author: laura
 */

#include "Sensor.hpp"


Sensor::Sensor()
{
    m_u8SensorID = m_u8NextSensorID; //assign id
    m_u8NextSensorID++;
}
