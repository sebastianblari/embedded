/*
 * LightSensor.hpp
 *
 *  Created on: Jun 9, 2019
 *      Author: laura
 */

#ifndef LIGHTSENSOR_HPP_
#define LIGHTSENSOR_HPP_

#include <HAL_I2C.h>
#include "HAL_OPT3001.h"
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "Sensor.hpp"

template <typename numType>
class LightSensor : public Sensor<numType>
{
    public:
        LightSensor();
        numType GetValue(void);
        virtual uint8_t setup(void);
        virtual uint8_t EnableSensor(void);
        virtual uint8_t DisableSensor(void);
        virtual ~LightSensor();
    private:
};

template<typename numType>
LightSensor<numType>::LightSensor()
{


}

template<typename numType>
numType LightSensor<numType>::GetValue()
{

    return OPT3001_getLux();

}

template<typename numType>
uint8_t LightSensor<numType>::setup()
{
    /* Initialize I2C communication */
        Init_I2C_GPIO();
        I2C_init();

    /* Initialize OPT3001 digital ambient light sensor */
        OPT3001_init();

        __delay_cycles(100000);

    return NO_ERR;
}

template<typename numType>
uint8_t LightSensor<numType>::EnableSensor()
{
    return NO_ERR;
}

template<typename numType>
uint8_t LightSensor<numType>::DisableSensor()
{
    return NO_ERR;
}

template<typename numType>
LightSensor<numType>::~LightSensor()
{

}
#endif /* LIGHTSENSOR_HPP_ */
