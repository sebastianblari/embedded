/*
 * SETUP
 *
 * Hardware_setup.hpp
 *
 *  Created on: Apr 15, 2019
 *
 *      IE-1119 Temas Especiales II: Laboratorio de Introducción a los Sistemas Incrustados
 *
 *      Authors: Dunia, Laura, Sebastian
 */

#ifndef HARDWARE_SETUP_HPP_
#define HARDWARE_SETUP_HPP_

#define TIMER32_1_COUNT_10ms  0x0000752F    //~10ms with 3MHz clock and clock divided by 1
#define TIMER32_2_COUNT_1s 0x0002DC6B   //~1s with 3MHz clock and clock divided by 16
#define BLINK_DELAY 0x2DC6C0            //~1s delay for the initial blink
#define LIGHT_SENSOR_DELAY 100000       //~33ms delay for light sensor configure

#define BLUE_LED 0x04
#define GREEN_LED 0x02
#define RED_LED 0x01

// Global variable that indicates pins on the port used by the LED Light
int g_iLedLight;

void PinSetup(void);
void ADC_setup(void);
void T32_1_setup(void);
void T32_2_setup(void);
void ButtonSetup(void);
void LightSensorSetup(void);

void InitialConditionsSetup(void);
void InitialBlink(int);
void PowerUp(int);


#endif /* HARDWARE_SETUP_HPP_ */
