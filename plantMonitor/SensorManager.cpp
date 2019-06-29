/*
 * SensorManager.cpp
 *
 *  Created on: Jun 26, 2019
 *      Author: laura
 */

//#include "SensorManager.hpp"
//
//SensorManager::SensorManager()
//{
//    for(int index = 0; index < NUMBER_OF_SENSORS; index++){
//        m_SensorsPointers[index] = (uintptr_t) 0; // Init to an invalid pointer
//    }
//    return;
//}
//
//uint8_t SensorManager::attach(Sensor * i_Toattach){
//    m_SensorsPointers[i_Toattach->m_u8SensorID] = i_Toattach;
//
//    return NO_ERR;
//}
//
//uint8_t SensorManager::ManageRequest(uint16_t i_Request){
//    // i_Request = ID1 ID0 Op1 Op0
//
//    /* Identify the Sensor ID requested
//     * by applying a mask
//     */
//    uint16_t l_u16IDmask = 0x1100;
//
//    l_u16IDmask &= i_Request;
//    l_u16IDmask = l_u16IDmask >> 8;
//
//    Sensor * l_pSensorRequired= m_SensorsPointers[l_u16IDmask];
//
//    /* Identify the operation required
//     * by applying a mask
//     */
//
//    uint16_t l_u16OperationMask = 0x11;
//    l_u16OperationMask &= i_Request;
//
////    switch (l_u16OperationMask){
////        case 0:
////            l_pSensorRequired->DisableSensor();
////        case 3:
//            //Return value
//     return NO_ERR;
//
//    }
//
//
//
//}


