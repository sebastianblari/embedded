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

        g_u64SystemTicks++;

        __enable_irq();
        return;
    }

    void EUSCIA0_IRQHandler(){
        uint32_t status = MAP_UART_getEnabledInterruptStatus(EUSCI_A0_BASE);

        MAP_UART_clearInterruptFlag(EUSCI_A0_BASE, status);


        g_u16BytesReceived =  g_u16BytesReceived <<4;
        g_u16BytesReceived |= (MAP_UART_receiveData(EUSCI_A0_BASE)-0x30);
        g_u8BytesCounter++;

    }
}
