/* 
 * File:   app_Button.h
 * Author: OmarEmanuel
 *
 * Created on 20 de abril de 2016, 07:54 PM
 */

#ifndef APP_BUTTON_H
#define	APP_BUTTON_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "system.h"
#include "stdtypedef.h"
#include "PIN_Configuration.h"
    
    typedef enum
    {
        UNPRESSED,
        SHORT_PRESS,
        LONG_PRESS
    }T_PRESS_TYPE;

#define N_BUTTONS   3
    
#define MAX_DEBOUNCE_TIME   0xFFu
#define MIN_DEBOUNCE_TIME   10u
#define EMULATION_TIME      100u
    
#define BTN1_EMULATED   rsub_EmulationFlags.bi.bit0
#define BTN2_EMULATED   rsub_EmulationFlags.bi.bit1
#define BTN3_EMULATED   rsub_EmulationFlags.bi.bit2
    
    extern T_PRESS_TYPE rub_ButtonStatus[N_BUTTONS];   
    extern void app_CheckButtons(void);
    extern void app_Button1(void);
    extern void app_Button2(void);
    extern void app_Button3(void);


#ifdef	__cplusplus
}
#endif

#endif	/* APP_BUTTON_H */

