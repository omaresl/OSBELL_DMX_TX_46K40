/**
  @Generated Interrupt Manager File

  @Company:
    Microchip Technology Inc.

  @File Name:
    interrupt_manager.c

  @Summary:
    This is the Interrupt Manager file generated using MPLAB(c) Code Configurator

  @Description:
    This header file provides implementations for global interrupt handling.
    For individual peripheral handlers please see the peripheral driver for
    all modules selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 4.0
        Device            :  PIC18F46K40
        Driver Version    :  1.02
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.40
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#include "interrupt_manager.h"
#include "mcc.h"

void  INTERRUPT_Initialize (void)
{
    // Enable Interrupt Priority Vectors
    INTCONbits.IPEN = 1;

    // Assign peripheral interrupt priority vectors

    // RCI - high priority
    IPR3bits.RC2IP = 1;

    // TXI - high priority
    IPR3bits.TX1IP = 1;

    // TMRI - high priority
    IPR4bits.TMR2IP = 1;

    // TMRI - high priority
    IPR4bits.TMR1IP = 1;


}

void interrupt INTERRUPT_InterruptManagerHigh (void)
{
   // interrupt handler
    if(PIE3bits.RC2IE == 1 && PIR3bits.RC2IF == 1)
    {
        EUSART2_Receive_ISR();
    }
    if(PIE3bits.TX1IE == 1 && PIR3bits.TX1IF == 1)
    {
        EUSART1_Transmit_ISR();
    }
    if(PIE4bits.TMR2IE == 1 && PIR4bits.TMR2IF == 1)
    {
        TMR2_ISR();
    }
    if(PIE4bits.TMR1IE == 1 && PIR4bits.TMR1IF == 1)
    {
        TMR1_ISR();
    }
}

/**
 End of File
*/