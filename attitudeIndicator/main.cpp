#include "main.hpp"
#include "math.h"

#include "Task.hpp"
#include "Scheduler.hpp"
#include "FillScreen.hpp"
#include "GetBorder.hpp"
#include "DrawMark.hpp"
#include "LED.hpp"

//----------------------------------------------------------------
uint8_t Task::m_u8NextTaskID = 0;   //init task ID
Scheduler g_MainScheduler;          //instantiate a Scheduler

//----------------------------------------------------------------
/* Clear display and redraw Status */
void LCD_DrawStatus()
{
    Graphics_clearDisplay(&g_sContext);
    LCD_DrawRectangle(64);

    Graphics_drawStringCentered(&g_sContext, (int8_t *)"NIVELADO:",
                                AUTO_STRING_LENGTH, 64, 30, OPAQUE_TEXT);
}

//----------------------------------------------------------------
/* Clear display and redraw title + accelerometer data */
void LCD_DrawTitle()
{
    //Graphics_clearDisplay(&g_sContext);
    Graphics_drawStringCentered(&g_sContext,
                                    (int8_t *)"Accelerometer:",
                                    AUTO_STRING_LENGTH,
                                    64,
                                    30,
                                    OPAQUE_TEXT);
    LCD_DrawAccelData();
}

//----------------------------------------------------------------
/* Redraw accelerometer data */
void LCD_DrawAccelData()
{
    char string[10];
    sprintf(string, "X: %5d", resultsBuffer[0]);
    Graphics_drawStringCentered(&g_sContext,
                                    (int8_t *)string,
                                    8,
                                    64,
                                    50,
                                    OPAQUE_TEXT);

    sprintf(string, "Y: %5d", resultsBuffer[1]);
    Graphics_drawStringCentered(&g_sContext,
                                    (int8_t *)string,
                                    8,
                                    64,
                                    70,
                                    OPAQUE_TEXT);

    sprintf(string, "Z: %5d", resultsBuffer[2]);
    Graphics_drawStringCentered(&g_sContext,
                                    (int8_t *)string,
                                    8,
                                    64,
                                    90,
                                    OPAQUE_TEXT);

}

//----------------------------------------------------------------


void LCD_DrawRollRect (const float i_fRollAngle, const float i_fPitchAngle) {
    Graphics_clearDisplay(&g_sContext);
    int16_t l_u16XYCoordinates[129];
    for (uint16_t l_u16XpixelCounter = 0; l_u16XpixelCounter < 129; l_u16XpixelCounter++){
        l_u16XYCoordinates[l_u16XpixelCounter] = abs (tan(i_fRollAngle)*(l_u16XpixelCounter - 64)
                                               + 64*sin(i_fPitchAngle)
                                               - 64 );
        if (l_u16XYCoordinates[l_u16XpixelCounter] > 128) {
            l_u16XYCoordinates[l_u16XpixelCounter] = 128;
        } else if (l_u16XYCoordinates[l_u16XpixelCounter] < 0) {
            l_u16XYCoordinates[l_u16XpixelCounter] = 0;
        }
    }
    printf("x0: %d \t y0: %d \t xf: %d \t yf: %d \t Roll: %f, tan(Roll): %f\n",0, l_u16XYCoordinates[0], 128, l_u16XYCoordinates[128], i_fRollAngle*180/M_PI, tan(i_fRollAngle));
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    Graphics_drawLine(&g_sContext, 0, l_u16XYCoordinates[0], 128, l_u16XYCoordinates[128]);
}

//Dibujar línea de Roll
void LCD_DrawRollLine(const float i_fRollAngle, const float i_fPitchAngle) {
    int16_t l_u16XYCoordinates[129]; // Cambiar 129 por un parámetro
    int16_t l_u8xMinValue, l_u8xMaxValue;
    // Esta lógica funciona para para un -45 < ángulo de roll < 45, puede copiar y cambiar una serie de parámetros para la lógica de los demás cuadrantes.
    for (uint16_t l_u16XpixelCounter = 0; l_u16XpixelCounter < 129; l_u16XpixelCounter++){
        l_u16XYCoordinates[l_u16XpixelCounter] = - ( tan(i_fRollAngle)*(l_u16XpixelCounter - 64)
                                               + 64*sin(i_fPitchAngle)
                                               - 64 );
        if (l_u16XYCoordinates[l_u16XpixelCounter] > 128) {
            l_u16XYCoordinates[l_u16XpixelCounter] = 129;
        } else if (l_u16XYCoordinates[l_u16XpixelCounter] < 0) {
            l_u16XYCoordinates[l_u16XpixelCounter] = -1;
        }
    }

    if(i_fPitchAngle <=  M_PI/2 && i_fPitchAngle > i_fPitchAngle >  0.95*M_PI/2) {
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BROWN);
            Graphics_Rectangle t_Rectangle2 = {0,0,128,128};
            Graphics_fillRectangle(&g_sContext, &t_Rectangle2);
    } else if(i_fPitchAngle >= - M_PI/2 && i_fPitchAngle <=  M_PI/2 ) {
        if (i_fRollAngle <= M_PI/2 || i_fRollAngle >= 3*M_PI/2) {
            for (uint8_t line_index = 0; line_index < 129; line_index++) {
                Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
                Graphics_drawLine(&g_sContext, line_index, l_u16XYCoordinates[line_index] - 1, line_index, 0);
                Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BROWN);
                Graphics_drawLine(&g_sContext, line_index, l_u16XYCoordinates[line_index] + 1, line_index, 128);
            }
            Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
            Graphics_drawLine(&g_sContext, 0, l_u16XYCoordinates[0], 128, l_u16XYCoordinates[128]);
        } else if (i_fRollAngle > M_PI/2 && i_fRollAngle < 3*M_PI/2) {
            for (uint8_t line_index = 0; line_index < 129; line_index++) {
                Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BROWN);
                Graphics_drawLine(&g_sContext, line_index, l_u16XYCoordinates[line_index] - 1, line_index, 0);
                Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
                Graphics_drawLine(&g_sContext, line_index, l_u16XYCoordinates[line_index] + 1, line_index, 128);
            }
            Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
            Graphics_drawLine(&g_sContext, 0, l_u16XYCoordinates[0], 128, l_u16XYCoordinates[128]);
        }
    }

}

//Cambiar yInitPosition segun lectura acelerometro
void LCD_DrawRectangle(const int yInitPosition)
{
    //draws blue part
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BROWN);
    Graphics_Rectangle t_Rectangle2 = {0,yInitPosition,128,128};
    Graphics_fillRectangle(&g_sContext, &t_Rectangle2);

    //draws brown part
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
    Graphics_Rectangle t_Rectangle1 = {0,0,128,yInitPosition};
    Graphics_fillRectangle(&g_sContext, &t_Rectangle1);

    //draws white line
//    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
//    Graphics_drawLine(&g_sContext, 0, 128, 128, 0);

    //displays info (para debugging)

    //Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    //Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    GrContextFontSet(&g_sContext, &g_sFontFixed6x8);
    //LCD_DrawAccelData();
    //LCD_DrawTitle();
    return;
}

//----------------------------------------------------------------
int main(void)
{
    //Instantiate new Tasks
    GetBorder BorderLine;
    DrawMark WhiteMark;
    FillScreen Fill;

    //attach the Tasks to the Scheduler;
    g_MainScheduler.attach(&BorderLine, 100);
    g_MainScheduler.attach(&WhiteMark, 101);
    g_MainScheduler.attach(&Fill, 102);

    //run the Setup for the scheduler and all tasks
    g_MainScheduler.setup();

    /* Halting WDT and disabling master interrupts */
    MAP_WDT_A_holdTimer();
    MAP_Interrupt_disableMaster();

    //configurations and initial conditions
    Power_up();

    /* Triggering the start of the sample */
    MAP_ADC14_enableConversion();
    MAP_ADC14_toggleConversionTrigger();


    while(1)
    {
        //MAP_PCM_gotoLPM0(); //do not know what it does

        __wfe(); // Wait for Event

        if(g_SystemTicks != g_MainScheduler.m_u64ticks)
        {
            //only execute the tasks if one tick has passed.
            g_MainScheduler.m_u64ticks = g_SystemTicks;
            g_MainScheduler.run();
        }
    }
}
