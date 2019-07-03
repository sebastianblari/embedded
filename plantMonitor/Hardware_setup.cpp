/*
 * SETUP
 *
 * Hardware_setup.cpp
 *
 *
 *      IE-1119 Temas Especiales II: Laboratorio de Introducción a los Sistemas Incrustados
 *
 *      Authors: Dunia, Laura, Sebastian
 */
#include "Hardware_setup.hpp"

const eUSCI_UART_Config uartConfig =
{
    EUSCI_A_UART_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
    78,                                     // BRDIV = 78
    2,                                       // UCxBRF = 2
    0,                                       // UCxBRS = 0
    EUSCI_A_UART_NO_PARITY,                  // No Parity
    EUSCI_A_UART_LSB_FIRST,                  // MSB First
    EUSCI_A_UART_ONE_STOP_BIT,               // One stop bit
    EUSCI_A_UART_MODE,                       // UART mode
    EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION  // Oversampling
};

//*****************************************************************
void T32_2_setup(void){

    //slot time: 1ms
    TIMER32_2->LOAD |= TIMER32_COUNT_1ms;
    TIMER32_2->CONTROL = TIMER32_CONTROL_SIZE | TIMER32_CONTROL_PRESCALE_1 |
                         TIMER32_CONTROL_MODE | TIMER32_CONTROL_IE | TIMER32_CONTROL_ENABLE;
    NVIC_SetPriority(T32_INT2_IRQn,1);
    NVIC_EnableIRQ(T32_INT2_IRQn);

    return;
}

void UartSetup(void){
    /* Selecting P1.2 and P1.3 in UART mode */
        MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,
                GPIO_PIN1 | GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);

        /* Setting DCO to 12MHz */
        CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_12);

        /* Configuring UART Module */
        MAP_UART_initModule(EUSCI_A0_BASE, &uartConfig);

        /* Enable UART module */
        MAP_UART_enableModule(EUSCI_A0_BASE);

        /* Enabling interrupts */
        MAP_UART_enableInterrupt(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
        MAP_Interrupt_enableInterrupt(INT_EUSCIA0);

        return;
}
void PinSetup(void){
    P1->DIR |= BIT0; //P1 Red LED -  Temperature Sensor actuator
    P2->DIR |= BIT2; //P2 Blue LED - Light Sensor actuator
}
//*****************************************************************
void InitialConditionsSetup(void){
    P1->OUT &= ~BIT0;   // OFF
    P2->OUT &= ~BIT2;   // OFF

    g_u64SystemTicks = 0;
    g_u8BytesCounter = 0U;
    g_u16BytesReceived = 0U;

    return;
}
//*****************************************************************
void PowerUp(void){
    PinSetup();
    T32_2_setup();
    UartSetup();

    //Initial Conditions
    InitialConditionsSetup();
}
