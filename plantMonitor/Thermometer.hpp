/*
 * Thermometer.hpp
 *
 *  Created on: Jun 9, 2019
 *      Author: laura
 */

#ifndef THERMOMETER_HPP_
#define THERMOMETER_HPP_

#include <HAL_I2C.h>
#include "HAL_TMP006.h"
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "Sensor.hpp"

template <typename numType>
class Thermometer : public Sensor<numType>
{
    public:
        Thermometer();
        virtual numType GetValue(void);
        uint8_t setup(void);
        uint8_t EnableSensor(void);
        uint8_t DisableSensor(void);
        ~Thermometer();
    private:
};

template <typename numType>
Thermometer<numType>::Thermometer()
{
    // TODO Auto-generated constructor stub

}

template <typename numType>
numType Thermometer<numType>::GetValue()
{
    // TODO Auto-generated constructor stubnumType
    return TMP006_getTemp();

}

template <typename numType>
uint8_t Thermometer<numType>::setup()
{
    /* Initialize I2C communication */
        Init_I2C_GPIO();
        I2C_init();

        /* Initialize TMP006 temperature sensor */
        TMP006_init();

        __delay_cycles(100000);

    return NO_ERR;
}


template <typename numType>
uint8_t Thermometer<numType>::EnableSensor()
{
    return NO_ERR;
}

template <typename numType>
uint8_t Thermometer<numType>::DisableSensor()
{
    return NO_ERR;
}

template <typename numType>
Thermometer<numType>::~Thermometer()
{
    /* Obtain temperature value from TMP006 */
}



#endif /* THERMOMETER_HPP_ */
