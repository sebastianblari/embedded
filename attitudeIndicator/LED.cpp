/*
 * LED.cpp
 *
 *  Created on: Aug 31, 2016
 *      Author: eortiz
 */
 
#include "LED.hpp"

//constructor -------------------------------
LED::LED(uint16_t i_BITN)
{
	m_u16BITN = i_BITN;
}

//run ---------------------------------------
uint8_t LED::run()
{
    //Blink code Assuming PORT2
	P2->OUT ^= m_u16BITN;
    return(NO_ERR);
}

//setup -------------------------------------
uint8_t LED::setup()
{
    //LED Setup, assuming PORT2
    P2->DIR |= m_u16BITN; //Selects the LED: Red, Blue or Green
    P2->OUT &= m_u16BITN; //Initialize the LED Value
    return(NO_ERR);
}
