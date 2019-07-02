/*
 * INTERRUPTIONS
 *
 * Interruptions_handler.cpp
 *
 *
 *      IE-1119 Temas Especiales II: Laboratorio de Introducción a los Sistemas Incrustados
 *
 *      Authors: Dunia, Laura, Sebastian
 */

#include "Interruptions_handler.hpp"
extern "C" {

//----------------------------------------------------------------
    void T32_INT2_IRQHandler(void) {

        __disable_irq();
        TIMER32_2->INTCLR = 0U; //Clear interrup Flag

        g_SystemTicks++;

        __enable_irq();
        return;
    }


//----------------------------------------------------------------
/*
 * IRQ Interruption generated when RXbuffer received data
 */
    void EUSCIA0_IRQHandler(){
        uint32_t status = MAP_UART_getEnabledInterruptStatus(EUSCI_A0_BASE);

        MAP_UART_clearInterruptFlag(EUSCI_A0_BASE, status);

        //shift g_u16BytesReceived to build the data
        g_u16BytesReceived =  g_u16BytesReceived <<4;
        //Parse the values from ASCII to number
        g_u16BytesReceived |= (MAP_UART_receiveData(EUSCI_A0_BASE)-0x30);
        //increase bytes counter
        g_u8BytesCounter++;

    }
}
