/* 
 * File:   app_DMX_TX.h
 * Author: uidj2522
 *
 * Created on 3 de agosto de 2016, 12:55 PM
 */

#ifndef APP_DMX_TX_H
#define	APP_DMX_TX_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "stdtypedef.h"
/*Delays for DMX Protocol*/
#define DMX_TX_MBB_TIME     (0x00u)
#define DMX_TX_BREAK_TIME   (0x00u)
#define DMX_TX_MAB_TIME     (0xFAu)
    
/*DMX CFG*/
#define DMX_TX_N_DATA           512u //Number of data packets to be sent

/*TX States*/
typedef enum
    {
            BEFORE_BREAK_SATE,
            BREAK_STATE,
            AFTER_BREAK_STATE
    }T_BREAK_STATE;
    
    typedef enum
    {
        TX_START_DATA,
        TX_DMX_DATA,
        TX_BEFORE_BREAK
    }T_TX_STATE;

    extern T_TX_STATE rub_TxState;
    extern T_BREAK_STATE rub_BreakState;
    extern T_UWORD ruw_TxDMXDataCounter;
    extern T_UWORD ruw_DMXColorCounter;
    extern T_UBYTE rub_DMX_DATA[DMX_TX_N_DATA];
    
    extern void app_DMX_ISR(void);
    extern void app_TMR1_DMX_TX_ISR(void);
    extern void app_DMX_TX_DisableTXPort(void);
    extern void app_DMX_TX_EnableTXPort(void);
#ifdef	__cplusplus
}
#endif

#endif	/* APP_DMX_TX_H */

