/* 
 * File:   app_Display.h
 * Author: OmarEmanuel
 *
 * Created on 24 de junio de 2016, 10:35 AM
 */

#ifndef APP_DISPLAY_H
#define	APP_DISPLAY_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "system.h"
#include "stdtypedef.h"

#define TEXT_TIME  100u    

extern void app_UpdateCounterDisplay(void);
extern void app_UpdateADCDisplay(void);
extern void app_TextTimerMng(void);

extern T_UBYTE rub_TextTimer;

#ifdef	__cplusplus
}
#endif

#endif	/* APP_DISPLAY_H */

