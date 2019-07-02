/*
 * main.hpp
 *
 *  Created on: Jun 30, 2019
 *      Author: laura
 */

#ifndef MAIN_HPP_
#define MAIN_HPP_


#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#include "SensorManager.hpp"
#include "LightSensor.hpp"
#include "Thermometer.hpp"

#include "Hardware_setup.hpp"
#include "Interruptions_handler.hpp"

#include <stdio.h>
#include <stdint.h>
#include <string>
#include <stdbool.h>
#include "printf.h"

#define TIMER32_COUNT_1ms 0x00000BB7


#endif /* MAIN_HPP_ */
