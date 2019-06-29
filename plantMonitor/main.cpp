
//#include <HAL_I2C.h>
#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include "LcdDriver/HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735.h"

#include "LightSensor.hpp"
#include "Thermometer.hpp"
#include "LowPassFilter.hpp"

#include <stdio.h>
#include <stdint.h>
#include <string>
#include <stdbool.h>
#include "printf.h"


uint8_t Sensor<int>::m_u8NextSensorID = 0;   //init task ID

/* UART Configuration Parameter. These are the configuration parameters to
 * make the eUSCI A UART module to operate with a 9600 baud rate. These
 * values were calculated using the online calculator that TI provides
 * at:
 *http://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSP430BaudRateConverter/index.html
 */
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

uint8_t g_SendFlag;
uint8_t g_BytesCounter;
uint16_t g_IDRequiered;
uint16_t g_TempBytes;

/*
 * Main function
 */
int main(void)
{
    /* Halting WDT and disabling master interrupts */
    MAP_WDT_A_holdTimer();

    //    MAP_Interrupt_disableMaster();

    /* Selecting P1.2 and P1.3 in UART mode */
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,
            GPIO_PIN1 | GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);

    /* Setting DCO to 12MHz */
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_12);

    /* Configuring UART Module */
    MAP_UART_initModule(EUSCI_A0_BASE, &uartConfig);

    /* Enable UART module */
    MAP_UART_enableModule(EUSCI_A0_BASE);

////////////////////////////////////////////////////////////////////////////////
    g_BytesCounter = 0U;
    g_TempBytes = 0U;

    /* Enabling interrupts */
    MAP_UART_enableInterrupt(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    MAP_Interrupt_enableInterrupt(INT_EUSCIA0);
    MAP_Interrupt_enableMaster();


////////////////////////////////////////////////////////////////////////////////

    Thermometer<int> Temp1;
    LightSensor<int> Lux1;
    float smoothing = 0.5;
    LowPassFilter<int,float> tempFilter(smoothing);
    LowPassFilter<int,float> luxFilter(smoothing);

    Temp1.setup();
    Lux1.setup();

    g_SendFlag = 0U;


    while(1)
    {

        if(g_SendFlag == 1U){
        printf(EUSCI_A0_BASE, "TEMP%n\r\n", tempFilter.filterSignal(Temp1.GetValue()));
        printf(EUSCI_A0_BASE, "LUX%n\r\n", luxFilter.filterSignal(Lux1.GetValue()));

        g_SendFlag = 0U;
        }

        if(g_BytesCounter == 4){
            g_IDRequiered = g_TempBytes;
            g_TempBytes = 0U;
            g_BytesCounter = 0U;
        }
    }
}



extern "C" {

    void EUSCIA0_IRQHandler(){
        uint32_t status = MAP_UART_getEnabledInterruptStatus(EUSCI_A0_BASE);

        MAP_UART_clearInterruptFlag(EUSCI_A0_BASE, status);


        g_TempBytes =  g_TempBytes <<4;
        g_TempBytes |= (MAP_UART_receiveData(EUSCI_A0_BASE)-0x30);
        g_BytesCounter++;



    }
}
