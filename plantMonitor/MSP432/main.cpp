/*
 * Main
 *
 *      Author: Laura,Sebastián,Dunia
 */

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
    PowerUp();

    /* Enabling interrupts */
    MAP_Interrupt_enableMaster();

    SensorManager<int> Manager;

    Thermometer<int> Temp1;
    LightSensor<int> Lux1;


    Manager.attach(&Temp1);
    Manager.attach(&Lux1);

    Manager.setup();


        while(1)
        {
            /*Calls sensor manager every time 2bytes data is received*/
           if(g_u8BytesCounter == 4){
               Manager.ManageRequest(g_u16BytesReceived);
                g_u16BytesReceived = 0U;
                g_u8BytesCounter = 0U;
            }
    }
}
