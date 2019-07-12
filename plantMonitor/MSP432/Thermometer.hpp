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
#include "LowPassFilter.hpp"

#include <stdio.h>
#include <stdint.h>
#include <string>
#include <stdbool.h>
#include "printf.h"

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
    this->sensorStatus = false;
}
/*
 * Function responsible of collecting and
 * sending the measurement by serial port
 */
template <typename numType>
numType Thermometer<numType>::GetValue()
{
    if(this->sensorStatus){
            float smoothing = 0.5;
            LowPassFilter<int,float> tempFilter(smoothing);

            printf(EUSCI_A0_BASE, "TEMP:%n\r\n", tempFilter.filterSignal(TMP006_getTemp()));
        }
        return NO_ERR;

}
/*
 * Setup configuration to activate and enable
 *  the temperature sensor.
 */
template <typename numType>
uint8_t Thermometer<numType>::setup()
{
    /* Initialize I2C communication */
        Init_I2C_GPIO();
        I2C_init();

        /* Initialize TMP006 temperature sensor */
        TMP006_init();

        __delay_cycles(100000);

        EnableSensor();

    return NO_ERR;
}

/*
 * Status modifier, to enable the
 * capture of the measurements
 * and actuator
 */
template <typename numType>
uint8_t Thermometer<numType>::EnableSensor()
{
    P1->OUT |= BIT0;
    this->sensorStatus = true;
    return NO_ERR;
}
/*
 * Status modifier, to disable the
 * capture of the measurements
 * and actuator
 */
template <typename numType>
uint8_t Thermometer<numType>::DisableSensor()
{
    this->sensorStatus = false;
    P1->OUT &= ~BIT0;
    return NO_ERR;
}

template <typename numType>
Thermometer<numType>::~Thermometer()
{
    /* Obtain temperature value from TMP006 */
}



#endif /* THERMOMETER_HPP_ */
