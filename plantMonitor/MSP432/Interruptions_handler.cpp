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
/*
 * Serial port receiver interruption handler.
 * Casts the data received and concatenates
 * every 8 bits with the previous data.
 */

    void EUSCIA0_IRQHandler(){
        uint32_t status = MAP_UART_getEnabledInterruptStatus(EUSCI_A0_BASE);

        MAP_UART_clearInterruptFlag(EUSCI_A0_BASE, status);

        P2->OUT ^= BIT1; // Indicates a new 8 bit data was received
        g_u16BytesReceived =  g_u16BytesReceived <<4;
        g_u16BytesReceived |= (MAP_UART_receiveData(EUSCI_A0_BASE)-0x30);
        g_u8BytesCounter++;

    }
}
