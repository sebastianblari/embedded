/*
 * LightSensor.hpp
 *
 *  Created on: Jun 9, 2019
 *      Author: Laura,Sebastián,Dunia
 */

#ifndef LIGHTSENSOR_HPP_
#define LIGHTSENSOR_HPP_

#include <HAL_I2C.h>
#include "HAL_OPT3001.h"
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "Sensor.hpp"
#include "LowPassFilter.hpp"

#include <stdio.h>
#include <stdint.h>
#include <string>
#include <stdbool.h>
#include "printf.h"

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
    this->sensorStatus = false;
}
/*
 * Function responsible of collecting and
 * sending the measurement by serial port
 */
template<typename numType>
numType LightSensor<numType>::GetValue()
{

    if(this->sensorStatus){
        float smoothing = 0.5;
        LowPassFilter<int,float> luxFilter(smoothing);
        /* Sends the serial message */
        printf(EUSCI_A0_BASE, "LUX:%n\r\n", luxFilter.filterSignal(OPT3001_getLux()));
    }
    return NO_ERR;

}

template<typename numType>
/*
 * Setup configuration to activate and enable
 *  the light sensor.
 */
uint8_t LightSensor<numType>::setup()
{
    /* Initialize I2C communication */
        Init_I2C_GPIO();
        I2C_init();

    /* Initialize OPT3001 digital ambient light sensor */
        OPT3001_init();

        __delay_cycles(100000);

        EnableSensor();

    return NO_ERR;
}

template<typename numType>
/*
 * Status modifier, to enable the
 * capture of the measurements
 * and actuator
 */
uint8_t LightSensor<numType>::EnableSensor()
{
    P2->OUT |= BIT2;
    this->sensorStatus = true;
    return NO_ERR;
}

template<typename numType>
/*
 * Status modifier, to disable the
 * capture of the measurements
 * and actuator
 */
uint8_t LightSensor<numType>::DisableSensor()
{
    this->sensorStatus = false;
    P2->OUT &= ~BIT2;
    return NO_ERR;
}

template<typename numType>
LightSensor<numType>::~LightSensor()
{

}
#endif /* LIGHTSENSOR_HPP_ */
