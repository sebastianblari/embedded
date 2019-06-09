/*
 * Task: GetBorder
 *
 * GetBorder.cpp
 *
 *  Created on: May 18, 2019
 *
 *      IE-1119 Temas Especiales II: Laboratorio de Introducción a los Sistemas Incrustados
 *
 *      Authors: Dunia, Laura, Sebastian
 */

#include "GetBorder.hpp"

/*--------------------------------------------------*/
//constructor
GetBorder::GetBorder()
{
    //...
}

/*--------------------------------------------------*/
/* Obtains the necessary coordinates to delimit the horizon line
 * saves this coordinates in the m_iXYCoordinates array
 * expected to send this array to FillScreen and GetDifference Tasks as a message
 * uses g_fRollAngle and g_fPitchAngle given by the ADC14 converter
 */
int GetBorder::run()
{


}

//---------------------------------------------------
//Saves the mailbox instance pointer
int GetBorder::setup()
{

}
/*--------------------------------------------------*/
/*Builds the data of the message, to be send for a the
 * next task */
int GetBorder::BuildMsgData()
{

}
