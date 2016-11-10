/* 
 * File:   app_HD44780.h
 * Author: OmarEmanuel
 *
 * Created on 16 de julio de 2016, 05:48 PM
 */

#ifndef APP_HD44780_H
#define	APP_HD44780_H

#ifdef	__cplusplus
extern "C" {
#endif

#define APP_HD44780_ENABLE
#ifdef APP_HD44780_ENABLE
#define HD_MAX_SLOT 16u //Characters Per Line

#define HD_CMD_TYPE     0x00u
#define HD_CHAR_TYPE    0x01u

#define HD_FUNCSET  0x28
#define HD_DISCTRL  0x0E
#define HD_MODESET  0x06
    
#define HD_FIRST_LINE   0x80u
#define HD_SEC_LINE     0xC0u
    
    extern T_UBYTE raub_DataBufferLine1[HD_MAX_SLOT];
    extern T_UBYTE raub_DataBufferLine2[HD_MAX_SLOT];

    extern T_UBYTE app_HD44780_SenCmd(void);
    extern void app_HD44780_PrepareCMD(T_UBYTE lub_type,T_UBYTE lub_cmd);
    extern void app_HD44780_Init(void);
    extern void app_HD44780_Mngr(void);
    extern void app_HD44780_CallInitDelay(T_UBYTE lub_delay, T_UBYTE lub_next_state);
#endif
#ifdef	__cplusplus
}
#endif

#endif	/* APP_HD44780_H */

