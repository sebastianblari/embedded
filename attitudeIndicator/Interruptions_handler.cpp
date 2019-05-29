/*
 * INTERRUPTIONS
 *
 * Interruptions_handler.cpp
 *
 *  Created on: May 5, 2019
 *
 *      IE-1119 Temas Especiales II: Laboratorio de Introducción a los Sistemas Incrustados
 *
 *      Authors: Dunia, Laura, Sebastian
 */

#include "Interruptions_handler.hpp"
#include "math.h"
extern "C" {

//---------------------------------------------------------------
/*
 *
 */
void ADC14_IRQHandler(void)
{
    uint64_t status;

    status = MAP_ADC14_getEnabledInterruptStatus();
    MAP_ADC14_clearInterruptFlag(status);

    //ADC_MEM2 conversion completed
    if(status & ADC_INT2)
    {
        //Store ADC14 conversion results

        double alpha = 0.005;



        int16_t Xg = ADC14_getResult(ADC_MEM0) - 8192;
        int16_t Yg = ADC14_getResult(ADC_MEM1) - 8192;
        int16_t Zg = ADC14_getResult(ADC_MEM2) - 8192;


        fXg = Xg * alpha + (fXg * (1.0 - alpha));
        fYg = Yg * alpha + (fYg * (1.0 - alpha));
        fZg = Zg * alpha + (fZg * (1.0 - alpha));


        g_fRollAngle  = atan2(-fYg, fXg);
        if( g_fRollAngle >= M_PI/2 &&  g_fRollAngle <= M_PI) {
            g_fRollAngle = M_PI/2 - g_fRollAngle;
        } else if (g_fRollAngle > - M_PI &&  g_fRollAngle < - 0) {
            g_fRollAngle = 3*M_PI/2 + g_fRollAngle;
        } else if (g_fRollAngle > 0 && g_fRollAngle <= M_PI/2) {
            g_fRollAngle = 3*M_PI/2 + g_fRollAngle;
        }
        if (g_fRollAngle > - M_PI/2 && g_fRollAngle < 0){
            g_fRollAngle = -g_fRollAngle;
        }


        g_fPitchAngle = atan2(fZg, sqrt(fYg*fYg + fXg*fXg));

    }
}
//----------------------------------------------------------------
    void T32_INT2_IRQHandler(void) {

        __disable_irq();
        TIMER32_2->INTCLR = 0U; //Clear interrupion's  Flag

        g_SystemTicks++;

        __enable_irq();
        return;
    }
}
