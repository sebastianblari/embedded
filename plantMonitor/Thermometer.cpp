/*
 * Thermometer.cpp
 *
 *  Created on: Jun 9, 2019
 *      Author: laura
 */
#include <HAL_I2C.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "HAL_TMP006.h"
#include "Thermometer.hpp"

//template <typename numType>
//Thermometer<numType>::Thermometer()
Thermometer::Thermometer()
{
    // TODO Auto-generated constructor stub

}

//template <typename numType>
//numType Thermometer<numType>::GetValue()
uint16_t Thermometer::GetValue()
{
    // TODO Auto-generated constructor stubnumType
    return TMP006_getTemp();

}

//template <typename numType>
//uint8_t Thermometer<numType>::setup()
uint8_t Thermometer::setup()
{
    /* Initialize I2C communication */
        Init_I2C_GPIO();
        I2C_init();

        /* Initialize TMP006 temperature sensor */
        TMP006_init();

        __delay_cycles(100000);

    return NO_ERR;
}


//template <typename numType>
//uint8_t Thermometer<numType>::EnableSensor()
uint8_t Thermometer::EnableSensor()
{
    return NO_ERR;
}

//template <typename numType>
//uint8_t Thermometer<numType>::DisableSensor()
uint8_t Thermometer::DisableSensor()
{
    return NO_ERR;
}

//template <typename numType>
//Thermometer<numType>::~Thermometer()
Thermometer::~Thermometer()
{
    /* Obtain temperature value from TMP006 */
}

