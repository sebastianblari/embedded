/*
 * Thermometer.hpp
 *
 *  Created on: Jun 9, 2019
 *      Author: laura
 */

#ifndef THERMOMETER_HPP_
#define THERMOMETER_HPP_

#include "Sensor.hpp"

//template <typename numType>

class Thermometer : public Sensor//<numType>
{
    public:
        Thermometer();
//        virtual numType GetValue(void);
        uint16_t GetValue(void);
        virtual uint8_t setup(void);
        virtual uint8_t EnableSensor(void);
        virtual uint8_t DisableSensor(void);
        virtual ~Thermometer();
    private:
};

#endif /* THERMOMETER_HPP_ */
