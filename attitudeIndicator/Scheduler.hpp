/*
 * Scheduler
 *
 * Scheduler.hpp
 *
 *  Created on: Aug 31, 2016
 *
 *      IE-1119 Temas Especiales II: Laboratorio de Introducción a los Sistemas Incrustados
 *
 *      Authors: eortiz
 */

#ifndef TASKS_SCHEDULER_HPP_
#define TASKS_SCHEDULER_HPP_

//#include "msp.h"
#include "Task.hpp"

#define NUMBER_OF_SLOTS 255
#define NULL            0

//-------------------------------------------------------
// This structure defines the Task Information
struct st_TaskInfo {
	Task * pToAttach;           //pointer to the Task
	uint64_t u64TickInterval;   //how often the task is executed
	uint64_t u64ticks;          //current tick count
	uint64_t u64TickIntervalInitValue; //value to reset
};

//-------------------------------------------------------
class Scheduler
{
public:
    Scheduler();
    uint64_t m_u64ticks;
    uint8_t attach(Task * i_ToAttach, uint64_t i_u64TickInterval);
    uint8_t run(void);
    uint8_t setup(void);
private:
    uint8_t m_u8OpenSlots; // Available slots
    uint8_t m_u8NextSlot;  // Next available slot
    st_TaskInfo m_aSchedule[NUMBER_OF_SLOTS];       // Current schedule to be executed
    st_TaskInfo m_aNextSchedule[NUMBER_OF_SLOTS];   // Next schedule to be executed (not implemented)
    uint8_t CalculateNextSchedule(void);            // Calculate next schedule tasks (not implemented)
    uint8_t SortScheduleByPriority(Task * i_pSchedule); // Sorts a schedule based on priority (not implemented)
};

#endif /* TASKS_SCHEDULER_HPP_ */
