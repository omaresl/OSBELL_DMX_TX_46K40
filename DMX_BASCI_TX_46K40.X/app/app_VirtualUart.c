
#include "PIN_Configuration.h"
#include "app_io.h"
#include "system.h"
#include "stdtypedef.h"
#include "app_VirtualUart.h"

static T_UBYTE lub_VurtualUartBitCounter;
static T_UBYTE lub_VirtualUartTempBuffer;

static T_UBYTE lub_VirtualUartRxHead = 0;
static T_UBYTE lub_VirtualUartRxTail = 0;
static T_UBYTE lub_VirtualUartRxBuffer[VIRTUAL_UART_RX_BUFFER_SIZE];
volatile T_UBYTE lub_VirtualUartRxCount;

void app_VirtualUartInit(void)
{
    /*Initialize driver state*/
    lub_VirtualUartRxHead = 0u;
    lub_VirtualUartRxTail = 0u;
    lub_VirtualUartRxCount = 0u;
    return;
}

void app_VirtualUartStop(void)
{
//    /*TMR2 (Clock Manager) Interrupt disable*/
//    PIE1bits.TMR2IE = FALSE;
//    
//    // interrupt on change for group IOCAF - flag
//    IOCAFbits.IOCAF2 = 0; // Pin : RA2
//
//    // interrupt on change for group IOCAN - negative
//    IOCANbits.IOCAN2 = 1; // Pin : RA2
//
//    // interrupt on change for group IOCAP - positive
//    IOCAPbits.IOCAP2 = 0; // Pin : RA2
//
//    INTCONbits.IOCIE = 1; // Enable IOCI interrupt 
}

void app_VirtualUartStart(void)
{
//    /*Disable IOCAN2*/
//    INTCONbits.IOCIE = 0u;
//    /*Set TMR2*/
//    T2TMR = 100u; //100 counts
//    /*Clear TMR2IF*/
//    PIR1bits.TMR2IF = 0;
//    
//    /*Initialize bit counter*/
//    lub_VurtualUartBitCounter = 0u;
//
//    /*Initialize temp buffer*/
//    lub_VirtualUartTempBuffer = 0u;
//    
//    /*TMR2 (Clock Manager) Interrupt Enable*/
//    PIE1bits.TMR2IE = TRUE;
}

void app_VirtualUartSCKMngr(void)
{
    /*Check the actual bit measure*/
    if(lub_VurtualUartBitCounter < VIRTUAL_UART_RX_BIT_LENGTH)
    {
        /*Store the bit into the temp buffer*/
        lub_VirtualUartTempBuffer |= (PIN_RX_VIRT_UART << lub_VurtualUartBitCounter);
        /*Increase the Bit Counter*/
        lub_VurtualUartBitCounter++;
    }
    else
    {
        /*Check Stop Bit*/
        if(PIN_RX_VIRT_UART == TRUE)
        {
            /*Stop Bit OK*/
            app_VirtualUartReceive();
        }
        else
        {
            /*Wrong Stop Bit*/
            /*Data Error Mngr*/
        }
        app_VirtualUartStop();
    }
    
    /*Set time for next toggle*/
    T2TMR = VIRTUAL_UART_HALF_PERIOD;
}

void app_VirtualUartReceive(void)
{
    lub_VirtualUartRxBuffer[lub_VirtualUartRxHead++] = lub_VirtualUartTempBuffer;
    if(VIRTUAL_UART_RX_BUFFER_SIZE <= lub_VirtualUartRxHead)
    {
        lub_VirtualUartRxHead = 0;
    }
    lub_VirtualUartRxCount++;
}

T_UBYTE app_VirtualUartRead(void)
{
    T_UBYTE lub_ReadValue = 0;
    
    lub_ReadValue = lub_VirtualUartRxBuffer[lub_VirtualUartRxTail++];
    if(VIRTUAL_UART_RX_BUFFER_SIZE <= lub_VirtualUartRxTail)
    {
        lub_VirtualUartRxTail = 0u;
    }
    else
    {
        /*Do nothing*/
    }
    lub_VirtualUartRxCount--;
    return lub_ReadValue;
}