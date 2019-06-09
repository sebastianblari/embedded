/*
 * Sensor.hpp
 *
 *  Created on: Jun 9, 2019
 *      Author: laura
 */

#ifndef SENSOR_HPP_
#define SENSOR_HPP_

#define NO_ERR 0
#define RET_ERR 1

//template <typename numType>

#include <ti/devices/msp432p4xx/inc/msp.h>

class Sensor
{
    public:
        Sensor();
        uint8_t m_u8SensorID;
//        virtual numType GetValue(void){return numType};
        virtual uint8_t setup(void){return(0);};
        virtual uint8_t EnableSensor(void){return(0);};
        virtual uint8_t DisenableSensor(void){return(0);};
    private:
        static uint8_t m_u8NextSensorID;
};



#endif /* SENSOR_HPP_ */
