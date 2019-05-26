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

#ifndef TASK_HPP_
#define TASK_HPP_

//#include "msp.h"

#define NO_ERR 0
#define RET_ERR 1

#include "Mailbox.hpp"


class Task
{
	public:
		Task();
		uint8_t m_u8TaskID; //Task id
		Mailbox *TaskMailbox;
		virtual uint8_t     run(void){return(0);};
		virtual uint8_t     setup(Mailbox *i_MailboxPtr){return(0);};
		bool                IsTaskFinished(void){return m_bIsFinished;};
		uint8_t             GetTaskPriority(void) {return m_u8Priority;};
		void                SetTaskPriority(uint8_t i_u8NewPriority){m_u8Priority = i_u8NewPriority;};
	private:
	   static uint8_t m_u8NextTaskID;
	   uint8_t m_u8Priority;
	protected:
	   bool m_bIsFinished;
};

#endif /* TASK_HPP_ */
