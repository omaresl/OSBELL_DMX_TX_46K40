/* 
 * File:   app_VirtualUart.h
 * Author: uidj2522
 *
 * Created on November 2, 2016, 2:41 PM
 */

#ifndef APP_VIRTUALUART_H
#define	APP_VIRTUALUART_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "stdtypedef.h"
#define VIRTUAL_UART_HALF_PERIOD    (50u)
#define VIRTUAL_UART_RX_BUFFER_SIZE (8u)
#define VIRTUAL_UART_RX_BIT_LENGTH  (8u)

    extern void app_VirtualUartInit(void);
    extern void app_VirtualUartStop(void);
    extern void app_VirtualUartStart(void);
    extern void app_VirtualUartSCKMngr(void);
    extern void app_VirtualUartReceive(void);
    extern T_UBYTE app_VirtualUartRead(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* APP_VIRTUALUART_H */

