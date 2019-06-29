/*
 * SensorManager.hpp
 *
 *  Created on: Jun 26, 2019
 *      Author: laura
 */

#ifndef SENSORMANAGER_HPP_
#define SENSORMANAGER_HPP_

#include "Sensor.hpp"

#define NUMBER_OF_SENSORS 255
#define NO_ERR 0

template <typename numType>
class SensorManager
{
   public:
       SensorManager();
       uint8_t attach(Sensor<numType>i_Toattach);
       uint8_t ManageRequest(uint16_t i_Request);
   private:
       Sensor<numType> * m_SensorsPointers[NUMBER_OF_SENSORS];

};

template <typename numType>
SensorManager::SensorManager()
{
   for(int index = 0; index < NUMBER_OF_SENSORS; index++){
       m_SensorsPointers[index] = (uintptr_t) 0; // Init to an invalid pointer
   }
   return;
}

template <typename numType>
uint8_t SensorManager::attach(Sensor<numType>* i_Toattach){
   m_SensorsPointers[i_Toattach->m_u8SensorID] = i_Toattach;

   return NO_ERR;
}


template <typename numType>
uint8_t SensorManager::ManageRequest(uint16_t i_Request){
   // i_Request = ID1 ID0 Op1 Op0

   /* Identify the Sensor<numType>ID requested
    * by applying a mask
    */
   uint16_t l_u16IDmask = 0x1100;

   l_u16IDmask &= i_Request;
   l_u16IDmask = l_u16IDmask >> 8;

   Sensor<numType> * l_pSensorRequired= m_SensorsPointers[l_u16IDmask];

   /* Identify the operation required
    * by applying a mask
    */

   uint16_t l_u16OperationMask = 0x11;
   l_u16OperationMask &= i_Request;

//    switch (l_u16OperationMask){
//        case 0:
//            l_pSensorRequired->DisableSensor();
//        case 3:
           //Return value
    return NO_ERR;

   }

#endif /* SENSORMANAGER_HPP_ */
