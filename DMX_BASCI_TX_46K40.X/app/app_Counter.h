/* 
 * File:   app_Counter.h
 * Author: OmarEmanuel
 *
 * Created on 24 de junio de 2016, 10:55 AM
 */

#ifndef APP_COUNTER_H
#define	APP_COUNTER_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "system.h"
#include "stdtypedef.h"
    
#define MAX_DEBOUNCE_COUNTER    0xFFu
#define COUNTER_DEBOUNCE        10u
    
#define MIN_COUNTER     1u
#define MAX_COUNTER     999u
#define MIN_ON_CFG      1u
#define MAX_ON_CFG      250u    
    
    typedef enum
    {
        NORMAL,
        MAX_COUNT_CFG,
        ON_CFG,
        LAST_CFG
    }T_COUNTER_MODE;

    extern void app_CounterMngr(void);
    extern void app_CounterCheckInput(void);
    extern void app_CounterInit(void);
    extern void app_CounterModeManager(void);
    extern void app_CounterCFGMngr(void);
    extern void app_CounterUpdateEeprom(void);
    extern void app_CounterIncrement(void);
    
    extern T_COUNTER_MODE rub_CounterMode;
    extern T_UWORD ruw_Count;
    extern T_UWORD ruw_MaxCount;
    extern T_COUNTER_MODE rub_CounterMode;
    extern T_UWORD ruw_OnCFG;
    
#ifdef	__cplusplus
}
#endif

#endif	/* APP_COUNTER_H */

