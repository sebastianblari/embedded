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
/* Nivelado:
 * x = 8100 - 8300
 * y = 4900 - 5000
 * z = 8000 - 8700
 *
 * Viendo totalmente hacia abajo:
 * x = 8100 - 8300
 * y = 8000 - 8300: aumenta 2900 puntos
 * z = 11400 - 11600: aumenta 2940 puntos
 * cada vez que se aumente 45 en y se suma uno en yinicial
 *
 * * Viendo totalmente hacia arriba:
 * x = 8100 - 8300
 * y = 8300 - 8500: aumenta 3200 puntos
 * z = 4800 - 5000: disminuye 3200 puntos
 * cada vez que se aumente 50 en y se resta uno en yinicial
 *
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

        int16_t x = (ADC14_getResult(ADC_MEM0) - 8192);
        int16_t y = (ADC14_getResult(ADC_MEM1) - 8192);
        int16_t z = ADC14_getResult(ADC_MEM2) - 8192;

        float theta_x_deg = atan(x/sqrt(y*y + z*z))*180/M_PI; // Get a counter clockwise angle movement
        if (x < 0 && y < 0) {
            theta_x_deg = - theta_x_deg;
        } else if (x < 0 && y >= 0){
            theta_x_deg = 180 + theta_x_deg;
        } else if (x >= 0 && y >= 0){
            theta_x_deg = 180 + theta_x_deg;
        } else {
            theta_x_deg = 360 - theta_x_deg;
        }
        float theta_y_deg = atan(y/sqrt(z*z + x*x))*180/M_PI;
        float theta_z_deg = atan(z/sqrt(x*x + y*y))*180/M_PI;
        float theta_z_rad = (float)theta_z_deg*M_PI/180;
        g_fRollAngle  = theta_x_deg*M_PI/180;
        g_fPitchAngle = theta_z_rad;
        int position = 64*(1-sin(theta_z_rad));

        g_iyInitPosition = position;
//        printf("Roll angle: %f \n",theta_x_deg);
    }
}
//----------------------------------------------------------------
    void T32_INT1_IRQHandler(void) {

        __disable_irq();
        TIMER32_1->INTCLR = 0U; //Clear interrup Flag

        LCD_DrawRectangle(g_iyInitPosition);
        LCD_DrawRollLine(g_fRollAngle,g_fPitchAngle);
        __enable_irq();
        return;
    }
//----------------------------------------------------------------
    /*void T32_INT2_IRQHandler(void) {

        __disable_irq();
        TIMER32_2->INTCLR = 0U; //Clear interrup Flag

        //...

        __enable_irq();
        return;
    }*/
}
