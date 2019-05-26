/*
 * Scheduler
 *
 * Scheduler.cpp
 *
 *  Created on: May 18, 2019
 *
 *      IE-1119 Temas Especiales II: Laboratorio de Introducción a los Sistemas Incrustados
 *
 *      Author: eortiz
 *      Modify by: Dunia Barahona
 */

#include "Scheduler.hpp"

//-------------------------------------------------------
//constructor
Scheduler::Scheduler()
{
    m_u8OpenSlots = static_cast<uint8_t>(NUMBER_OF_SLOTS);  //empty schedule
    m_u8NextSlot = 0;                                       //task will be assign to the first slot
    for(int index = 0; index < NUMBER_OF_SLOTS; index++)
    {
        m_aSchedule[index].pToTask = (uintptr_t) 0; //init to an invalid pointer
    }
    return;
}

//-------------------------------------------------------
//inserts the task into the schedule slots
uint8_t Scheduler::attach(Task * i_ToAttach, uint64_t i_u64TickInterval)
{
    /**Local Variables**/
    uint8_t l_ErrorCode = NO_ERR;
    st_TaskInfo l_st_StructToAttach;

    l_st_StructToAttach.pToTask = i_ToAttach;   //assign pointer of the task
    l_st_StructToAttach.u64TaskTicks = 0;       //Task Tick Counter set in zero
    l_st_StructToAttach.u64Ticks = this->m_u64Ticks;

    //The task will be executed every i_u64TickInterval ticks
    l_st_StructToAttach.u64TickInterval = i_u64TickInterval;


    //if there are free slots in the schedule:
    if((m_u8OpenSlots>0) && (m_u8NextSlot < NUMBER_OF_SLOTS))
    {
        m_aSchedule[m_u8NextSlot] =  l_st_StructToAttach; //assign Task struct to respective Schedule slot
        m_u8OpenSlots--;
        m_u8NextSlot++;
    }
    else
    {
        l_ErrorCode = RET_ERR;
    }
    return l_ErrorCode;
}

//-------------------------------------------------------
//removes the task of the schedule slot
uint8_t Scheduler::remove(Task * i_ToRemove)
{
    /**Local Variable**/
    uint8_t l_ErrorCode = NO_ERR;

    //if Scheduler is NOT empty: if there is at least one task in Schedule
    if(m_u8OpenSlots < NUMBER_OF_SLOTS)
    {
        m_u8NextSlot--;
        m_u8OpenSlots++;

        //reorganizes the Tasks in the Scheduler slots after removal
        for(uint8_t i=(i_ToRemove->m_u8TaskID); i < (m_u8NextSlot); i++){
            m_aSchedule[i].pToTask = m_aSchedule[i+1].pToTask;
            m_aSchedule[i].pToTask->m_u8TaskID--;
        }
    }
    else
    {
        l_ErrorCode = RET_ERR;  //if Scheduler is empty
    }
    return l_ErrorCode;
}

//-------------------------------------------------------
//execute the current schedule
uint8_t Scheduler::run(void)
{
    /**Local Variable**/
    int l_iNextTaskSlot = 0U;
    Task * l_pNextTask = (uintptr_t) 0;
    uint8_t l_u8ErrorCode = NO_ERR;

    //if Scheduler is NOT empty: if there is at least one task in Schedule
    if(m_u8OpenSlots < NUMBER_OF_SLOTS)
    {
        //goes through every occupied slot of the current schedule, checking if its task is to be executed
        while(l_iNextTaskSlot < m_u8NextSlot)
        {
            l_pNextTask = static_cast<Task *> (m_aSchedule[l_iNextTaskSlot].pToTask);
            if(l_pNextTask != ((uintptr_t) 0))
            {
                //if the Task Tick counter is zero, the task will be executed
                if(m_aSchedule[l_iNextTaskSlot].u64TaskTicks == 0){
                    l_pNextTask->run();
                }
                m_aSchedule[l_iNextTaskSlot].u64TaskTicks ++; //Task tick counter increases

                //if the Task tick counter reaches the Task tick interval, the counter is set to zero
                if(m_aSchedule[l_iNextTaskSlot].u64TaskTicks > m_aSchedule[l_iNextTaskSlot].u64TickInterval) {
                    m_aSchedule[l_iNextTaskSlot].u64TaskTicks = 0;
                }
            }
            l_iNextTaskSlot++;
        }
    }
    else
    {
        l_u8ErrorCode = RET_ERR;  //if Schedule is empty
    }

    // CalculateNextSchedule(); //TODO
    return l_u8ErrorCode;
}

//-------------------------------------------------------
//execute the setup function for all tasks
uint8_t Scheduler::setup(Mailbox *i_MailboxPtr)
{
    /**Local Variable**/
    int l_iNextTaskSlot = 0U;
    Task * l_pNextTask = (uintptr_t) 0;
    uint8_t l_u8ErrorCode = NO_ERR;

    //if Scheduler is NOT empty: if there is at least one task
    if(m_u8OpenSlots < NUMBER_OF_SLOTS)
    {
        //goes through every occupied slot of the current schedule, setting the task up
        while(l_iNextTaskSlot < m_u8NextSlot)
        {
            l_pNextTask = static_cast<Task *> (m_aSchedule[l_iNextTaskSlot].pToTask);
            if(l_pNextTask != ((uintptr_t) 0))
            {
                l_pNextTask->setup();
            }
            l_iNextTaskSlot++;
        }
    }
    else
    {
        l_u8ErrorCode = RET_ERR;  //if Schedule is empty
    }
    return l_u8ErrorCode;
}

//-------------------------------------------------------
uint8_t Scheduler::CalculateNextSchedule(void)
{
    return(NO_ERR);
}

//-------------------------------------------------------
uint8_t Scheduler::SortScheduleByPriority(Task * i_pSchedule)
{
    return(NO_ERR);
}
