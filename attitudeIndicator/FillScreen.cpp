/*
 * Task: FillScreen
 *
 * FillScreen.cpp
 *
 *  Created on: May 18, 2019
 *
 *      IE-1119 Temas Especiales II: Laboratorio de Introducción a los Sistemas Incrustados
 *
 *      Authors: Dunia, Laura, Sebastian
 */
#include "FillScreen.hpp"
#include "math.h"

/*--------------------------------------------------*/
//constructor
FillScreen::FillScreen()
{
    //...
}

/*--------------------------------------------------*/
/* Fills the screen with each color
 * it can be optimized by decreasing the filling area
 * uses g_u16XYCoordinates[i] values
 * expected to receive this values from a message
 */
uint8_t FillScreen::run()
{
//    printf("fillscreen->run\n");
    uint16_t* Coordinates_ptr = DecodeMsgData();
    if(g_fPitchAngle <=  M_PI/2 && g_fPitchAngle > g_fPitchAngle >=  0.95*M_PI/2) {
            Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BROWN);
            Graphics_Rectangle t_Rectangle2 = {0,0,128,128};
            printf("90");
            Graphics_fillRectangle(&g_sContext, &t_Rectangle2);
        } else if(g_fPitchAngle >= - M_PI/2 && g_fPitchAngle <=  M_PI/2 ) {
            if (g_fRollAngle <= M_PI/2 || g_fRollAngle >= 3*M_PI/2) {
                for (uint8_t line_index = 0; line_index < 129; line_index++) {
                    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
//                    Graphics_drawLine(&g_sContext, line_index, g_u16XYCoordinates[line_index], line_index, 0);
                    Graphics_drawLine(&g_sContext, line_index, Coordinates_ptr[line_index], line_index, 0);
                    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BROWN);
//                    Graphics_drawLine(&g_sContext, line_index, g_u16XYCoordinates[line_index], line_index, 128);
                    Graphics_drawLine(&g_sContext, line_index, Coordinates_ptr[line_index], line_index, 128);
                }
//                Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
//                Graphics_drawLine(&g_sContext, 0, g_u16XYCoordinates[0], 128, g_u16XYCoordinates[128]);
            } else if (g_fRollAngle > M_PI/2 && g_fRollAngle < 3*M_PI/2) {
                for (uint8_t line_index = 0; line_index < 129; line_index++) {
                    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BROWN);
//                    Graphics_drawLine(&g_sContext, line_index, g_u16XYCoordinates[line_index], line_index, 0);
                    Graphics_drawLine(&g_sContext, line_index, Coordinates_ptr[line_index], line_index, 0);
                    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
//                    Graphics_drawLine(&g_sContext, line_index, g_u16XYCoordinates[line_index], line_index, 128);
                    Graphics_drawLine(&g_sContext, line_index, Coordinates_ptr[line_index], line_index, 128);
                }
//                Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
//                Graphics_drawLine(&g_sContext, 0, g_u16XYCoordinates[0], 128, g_u16XYCoordinates[128]);
            }
        }
    BuidMsgData();
    return(NO_ERR);
}

/*--------------------------------------------------*/
uint8_t FillScreen::setup(Mailbox *i_MailboxPtr)
{
    TaskMailbox = i_MailboxPtr;
    return(NO_ERR);
}

/*--------------------------------------------------*/
uint8_t FillScreen::BuidMsgData()
{
    st_MsgInfo CoordinatesPtrMsg;
    CoordinatesPtrMsg.source = m_u8TaskID;
    CoordinatesPtrMsg.destiny = m_u8TaskID + 1;

    //building the message
    CoordinatesPtrMsg.data_ptr = m_lastCoodinates;
    TaskMailbox->ReceiveMsg(CoordinatesPtrMsg);

    return 0;
}
/*--------------------------------------------------*/
uint16_t* FillScreen::DecodeMsgData()
{
    st_MsgInfo ParametersReceived;
        if (TaskMailbox->CheckMailbox(m_u8TaskID)>0){
            ParametersReceived = TaskMailbox->SendMsg(m_u8TaskID-1,m_u8TaskID);
            m_lastCoodinates = ParametersReceived.data_ptr;
            return ParametersReceived.data_ptr;
        }
        else{
            return m_lastCoodinates;

        }
}
