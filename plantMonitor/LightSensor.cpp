/*
 * LightSensor.cpp
 *
 *  Created on: Jun 9, 2019
 *      Author: laura
 */

#include "LightSensor.hpp"
#include <HAL_I2C.h>
#include "HAL_OPT3001.h"
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

LightSensor::LightSensor()
{


}

uint16_t LightSensor::GetValue()
{

    return OPT3001_getLux();

}


uint8_t LightSensor::setup()
{
    /* Initialize I2C communication */
        Init_I2C_GPIO();
        I2C_init();

    /* Initialize OPT3001 digital ambient light sensor */
        OPT3001_init();

        __delay_cycles(100000);

    return NO_ERR;
}

uint8_t LightSensor::EnableSensor()
{
    return NO_ERR;
}


uint8_t LightSensor::DisableSensor()
{
    return NO_ERR;
}

LightSensor::~LightSensor()
{

}

