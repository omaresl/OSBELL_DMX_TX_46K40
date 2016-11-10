/* 
 * File:   app_Trigger.h
 * Author: OmarEmanuel
 *
 * Created on 25 de junio de 2016, 05:15 PM
 */

#ifndef APP_TRIGGER_H
#define	APP_TRIGGER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "system.h"
#include "stdtypedef.h"
    
#define TRIGGER_TASK_MULTIPLIER 3u //Task is exe every 32ms (32*3 = 96ms (~100ms))
    
    extern T_UBYTE rub_TriggerFlag;
    
    extern void app_TriggerMngr(void);
    extern void app_TriggerInit(void);


#ifdef	__cplusplus
}
#endif

#endif	/* APP_TRIGGER_H */

