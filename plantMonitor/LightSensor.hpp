/*
 * LightSensor.hpp
 *
 *  Created on: Jun 9, 2019
 *      Author: laura
 */

#ifndef LIGHTSENSOR_HPP_
#define LIGHTSENSOR_HPP_

#include "Sensor.hpp"

class LightSensor : public Sensor
{
    public:
        LightSensor();
        uint16_t GetValue(void);
        virtual uint8_t setup(void);
        virtual uint8_t EnableSensor(void);
        virtual uint8_t DisableSensor(void);
        virtual ~LightSensor();
    private:
};

#endif /* LIGHTSENSOR_HPP_ */
