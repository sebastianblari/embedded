#include "main.hpp"
#include "math.h"

#include "Task.hpp"
#include "Scheduler.hpp"
#include "FillScreen.hpp"
#include "GetBorder.hpp"
#include "DrawMark.hpp"
#include "GetDifference.hpp"
#include "FillDifference.hpp"

//----------------------------------------------------------------
uint8_t Task::m_u8NextTaskID = 0;   //init task ID
Scheduler g_MainScheduler;          //instantiate a Scheduler

//----------------------------------------------------------------
int main(void)
{
	done = false;

    /** instantiate new Tasks **/
    GetBorder BorderLine;
    DrawMark WhiteMark;
    FillScreen Fill;
    GetDifference GD;
	FillDifference FillDiff;

	/** Mailbox instance **/
    Mailbox g_MailHandler;


	/** attach the Tasks to the Scheduler **/
    g_MainScheduler.attach(&BorderLine, 100);
    g_MainScheduler.attach(&WhiteMark, 101);
    g_MainScheduler.attach(&Fill, 102);

	/** run the Setup for the scheduler and all tasks **/
    g_MainScheduler.setup(&g_MailHandler);


	/** configurations and initial conditions **/
    Power_up();

	/** Triggering the start of the sample **/
    MAP_ADC14_enableConversion();
    MAP_ADC14_toggleConversionTrigger();


    while(!done)
    {
        __wfe(); // Wait for Event

        if(g_SystemTicks != g_MainScheduler.m_u64Ticks)
        {
            //only execute the tasks if one tick has passed.
            g_MainScheduler.m_u64Ticks = g_SystemTicks;
            g_MainScheduler.run();
            done = true;
        }
    }

    g_MainScheduler.remove(&Fill);
    g_MainScheduler.remove(&WhiteMark);
    g_MainScheduler.attach(&GD, 102);
    g_MainScheduler.setup(&g_MailHandler);

    while(done)
    {
        __wfe(); // Wait for Event

        if(g_SystemTicks != g_MainScheduler.m_u64Ticks)
        {
            //only execute the tasks if one tick has passed.
            g_MainScheduler.m_u64Ticks = g_SystemTicks;
            g_MainScheduler.run();
        }
    }

    /*while(1)
    {
        //MAP_PCM_gotoLPM0(); //do not know what it does

        __wfe(); // Wait for Event

        if(g_SystemTicks != g_MainScheduler.m_u64Ticks)
        {
            //only execute the tasks if one tick has passed.
            g_MainScheduler.m_u64Ticks = g_SystemTicks;
            g_MainScheduler.run();
            done = true;
        }
        g_MainScheduler.remove(&Fill);
            //g_MainScheduler.remove(&WhiteMark);
            g_MainScheduler.attach(&GD, 102);
            g_MainScheduler.setup(&g_MailHandler);
            while(done){
                //MAP_PCM_gotoLPM0(); //do not know what it does

                __wfe(); // Wait for Event

                if(g_SystemTicks != g_MainScheduler.m_u64Ticks)
                {
                    //only execute the tasks if one tick has passed.
                    g_MainScheduler.m_u64Ticks = g_SystemTicks;
                    g_MainScheduler.run();
                }
            }
    }*/
}
