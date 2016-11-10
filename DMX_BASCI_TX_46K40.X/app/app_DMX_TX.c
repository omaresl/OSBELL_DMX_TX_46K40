#include <pic18f46k40.h>

#include "system.h"
#include "stdtypedef.h"
#include "app_Meas.h"
#include "app_DMX_TX.h"


T_UBYTE rub_DMX_DATA[DMX_TX_N_DATA];
T_UWORD ruw_TxDMXDataCounter = 0x00;
T_UWORD ruw_DMXColorCounter = 0x00;
T_TX_STATE rub_TxState = TX_START_DATA;
T_BREAK_STATE rub_BreakState = BEFORE_BREAK_SATE;
T_UWORD ruw_DMXBuilderDataCounter = 0x00u;

void app_DMX_ISR(void)
{
    switch(rub_TxState)
    {
        case TX_START_DATA:
        {
            TX1REG = 0x00; //Start Byte
            rub_TxState = TX_DMX_DATA; //Next State
            ruw_TxDMXDataCounter = 0x00u; //Prepare Data Counter
            ruw_DMXColorCounter = 0x00u; //Prepare color counter
        }break;
        case TX_DMX_DATA:
        {
           if(ruw_TxDMXDataCounter < DMX_TX_N_DATA)
            {
                TX1REG = rub_DMX_DATA[ruw_DMXColorCounter]; //Send Data
                ruw_TxDMXDataCounter++;
                if(ruw_DMXColorCounter < (DMX_TX_N_DATA - 1))
                {
                    ruw_DMXColorCounter++;
                }
                else
                {
                    ruw_DMXColorCounter = 0x00u;
                }
            }
            else
            {
                ruw_TxDMXDataCounter = 0x00u; //Reset Data Counter
                ruw_DMXColorCounter = 0x00u; //Reset Color Counter
                rub_TxState = TX_BEFORE_BREAK; //Next State
            }
        }break;
        case TX_BEFORE_BREAK:
        {
            /*Transmission Finished*/
            rub_TxState = TX_START_DATA; //Prepare init state
            PIE3bits.TX1IE = FALSE; //Disable Interrupt
            T2TMR = DMX_TX_MBB_TIME;
            PIR4bits.TMR2IF = FALSE; //Clear TMR1 Flag
            PIE4bits.TMR2IE = TRUE; //Enable TMR1 Interrupt
        }break;
        default:
        {
            rub_TxState = TX_START_DATA;
        }
    }
    return;
}

void app_TMR1_DMX_TX_ISR(void)
{
    switch(rub_BreakState)
    {
        case BEFORE_BREAK_SATE:
        {
            T2TMR = DMX_TX_BREAK_TIME;
            app_DMX_TX_DisableTXPort(); //Disable Uart
            rub_BreakState = BREAK_STATE; //Next state
        }break;
        case BREAK_STATE:
        {
            /*Delay of break finished*/
            T2TMR = DMX_TX_MAB_TIME;
            app_DMX_TX_EnableTXPort(); //Enable uart
            rub_BreakState = AFTER_BREAK_STATE; //Next state
        }break;
        case AFTER_BREAK_STATE:
        {
            /*Delay for MAB Finished*/
            TMR2IE = FALSE; //Disable TMR1 interrupt
            TX1IE = TRUE;
            rub_BreakState = BEFORE_BREAK_SATE;//Prepare init state
        }break;
        default:
        {
            rub_BreakState = BEFORE_BREAK_SATE;
        }break;
    }
    return;
}

void app_DMXBuilder(void)
{
    rub_DMX_DATA[ruw_DMXBuilderDataCounter] = (T_UBYTE)(ruw_DataMeasured[ruw_DMXBuilderDataCounter] >> 2);
    ruw_DMXBuilderDataCounter++;
    
    if(ruw_DMXBuilderDataCounter < MEASURE_BUFFER_SIZE)
    {
        /*Do Nothing*/
    }
    else
    {
        ruw_DMXBuilderDataCounter = 0x00u;
    }
    return;
}

void app_DMX_TX_DisableTXPort(void)
{
    T_UBYTE state = GIE;
    GIE = 0;
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00; // unlock PPS

    RB0PPS = 0x0;   //RB0->LATB0;

    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS

    GIE = state;
    LATB0 = FALSE;    
    return;
}

void app_DMX_TX_EnableTXPort(void)
{
    T_UBYTE state = GIE;
    GIE = 0;
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00; // unlock PPS

    RB0PPS = 0x09;   ////RB0->EUSART1:TX1;

    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS

    GIE = state;
    LATB0 = FALSE;    
    return;
}