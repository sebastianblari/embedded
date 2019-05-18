/*
 * Tasks
 *
 * Task.hpp
 *
 *  Created on: May 18, 2019
 *
 *      IE-1119 Temas Especiales II: Laboratorio de Introducción a los Sistemas Incrustados
 *
 *      Authors: Dunia, Laura, Sebastian
 */

#include "Task.hpp"

Task::Task()
{
    m_u8TaskID = m_u8NextTaskID; //assign id
    m_u8NextTaskID++;
    m_bIsFinished = false;
}


