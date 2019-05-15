/*
 * INTERRUPTIONS
 *
 * Interruptions_handler.cpp
 *
 *  Created on: Apr 15, 2019
 *
 *      IE-1119 Temas Especiales II: Laboratorio de Introducción a los Sistemas Incrustados
 *
 *      Authors: Dunia, Laura, Sebastian
 */



extern "C" {

//----------------------------------------------------------------
// Timer32_1 interruption activates ADC14 sampling
    void T32_INT1_IRQHandler(void) {

        // Generates an interrupt every 10ms:
        __disable_irq();
        //Clear interruption flag
        TIMER32_1->INTCLR = 0U;

        // ADC14 starts
        ADC14->CTL0 = ADC14->CTL0 | ADC14_CTL0_SC;

        __enable_irq();

        return;
    }

//----------------------------------------------------------------

/*Timer32_1 obtains the average of the audios samples of 1s and 5s.
 *Calculates the audio threshold with the 5s samples and compare the 
 *last sencond with the threshold.
 *Also, keeps the track of time the light is on.
 */
    void T32_INT2_IRQHandler(void) {

        __disable_irq();

        TIMER32_2->INTCLR = 0U; //Clear interrup Flag

        int l_iAdc14ResultIndex;

        /* Compares the actual sample with the sensitive of 10% to set
    	 * the Over audio threshold flag 
         */  
        if (g_u8OverThSampleCount >= (g_iAudioSampleCount*0.1) ){
            g_u8Flags |= BIT3;
        }
        else{
            g_u8Flags &= ~BIT3;
        }
        g_u8OverThSampleCount = 0;

        // 1s Audio sample average
        g_u16AudioAverage_1s = g_u32AudioSampleSum / g_iAudioSampleCount;

        // Reset
        g_u32AudioSampleSum = 0U;
        g_iAudioSampleCount = 0;

        //Stores the last second sample
        g_u16Adc14Result[5] = g_u16AudioAverage_1s;

        //Obtains the audio average of the last 5s
        for (l_iAdc14ResultIndex = 0; l_iAdc14ResultIndex<5; l_iAdc14ResultIndex++){

            g_u16AudioAverage_5s += g_u16Adc14Result[l_iAdc14ResultIndex];
            g_u16Adc14Result[l_iAdc14ResultIndex] = g_u16Adc14Result[l_iAdc14ResultIndex+1];

            if (l_iAdc14ResultIndex == 4){
                g_u16AudioAverage_5s /= 5;
                g_iAudioThreshold = ((g_u16AudioAverage_5s*10)/100) + g_u16AudioAverage_5s;
                g_u16AudioAverage_5s = 0U;
            }
        }

        //---- Lamp on  timer track ------------
        
        // Lamp On during LampOnInterval seconds
        if (g_iLampOnCount > 0) {
            g_iLampOnCount --;
        }
        else if ( (g_iLampOnCount == 0) ) {
            LED_CTRL->OUT &= ~g_iLedLight; //Turn off light
            g_u8Flags &= ~BIT1;
        }

        __enable_irq();

        return;
    }

//----------------------------------------------------------------

/* ADC14 takes the audio sample, stores it and counts the amount  
 * of samples are done in a period of 1s.
 */
    void ADC14_IRQHandler(void) {

        __disable_irq();

        //If the power up is over, store the samples
        if( (g_u8Flags & BIT0) == BIT0){

            if(ADC14->MEM[0] >= g_iAudioThreshold){
                g_u8OverThSampleCount ++;
            }
        }

        g_u32AudioSampleSum += ADC14->MEM[0];
        g_iAudioSampleCount ++;

        ADC14->CLRIFGR0 = ADC14_CLRIFGR0_CLRIFG0;
        __enable_irq();

        return;
    }

//----------------------------------------------------------------

/* Toggle the light status if the lamp's button is pressed, and   
 * starts the automatic mode timer if the change of lamp was from
 * off to on. 
 */
    void PORT1_IRQHandler( void ) {

        uint32_t l_u32GpioStatus;
        
        //Verify which port was activated
        l_u32GpioStatus = GPIO_getEnabledInterruptStatus ( GPIO_PORT_P1 ) ;
        if ( l_u32GpioStatus & GPIO_PIN1 ) {

            // Toggle the state of light
            GPIO_toggleOutputOnPin( GPIO_PORT_P2 , g_iLedLight ) ;

            //Checks the actual state of the lamp
            if(P2->OUT != 0){
                g_u8Flags |= BIT1;
                g_iLampOnCount = LAMP_ON_INTERVAL;}

            GPIO_clearInterruptFlag( GPIO_PORT_P1 , l_u32GpioStatus ) ;
        }
    }
}
