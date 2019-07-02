#include "main.hpp"

uint8_t Sensor<int>::m_u8NextSensorID = 0;   //init task ID

/*
 * Main function
 */
int main(void)
{
    /* Halting WDT and disabling master interrupts */
    MAP_WDT_A_holdTimer();

    MAP_Interrupt_disableMaster();

    //configurations and initial conditions
    Power_up();

    g_BytesCounter = 0U;
    g_TempBytes = 0U;


    MAP_Interrupt_enableMaster();

////////////////////////////////////////////////////////////////////////////////


    SensorManager<int> Manager;

    Thermometer<int> Temp1;
    LightSensor<int> Lux1;

    Manager.attach(&Temp1,500);
    Manager.attach(&Lux1,501);

    Manager.setup();


    while(1)
    {
        __wfe(); // Wait for Event

       if(g_SystemTicks != Manager.m_u64ticks)
           {
               //only execute the tasks if one tick has passed.
           Manager.m_u64ticks = g_SystemTicks;
           Manager.run();
           }

        if(g_BytesCounter == 4){
            Manager.ManageRequest(g_TempBytes);
            g_TempBytes = 0U;
            g_BytesCounter = 0U;
        }
    }
}
