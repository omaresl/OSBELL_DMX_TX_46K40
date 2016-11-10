/*
 * app_convert.h
 *
 *  Created on: Oct 17, 2013
 *      Author: Omar Sevilla
 */

#ifndef APP_CONVERT_H_
#define APP_CONVERT_H_
#include "stdtypedef.h"
extern void bin2bcd(T_UWORD luw_Bin_Data);
extern void bcd2ascii(void);
extern T_UBYTE bcd27seg(T_UWORD luw_BCDData);

extern T_UWORD 	rub_BCDUni,
                rub_BCDDec,
                rub_BCDCen,
                rub_BCDUmil,
                rub_BCDDmil,
                rub_BCDCmil;

#endif /* APP_CONVERT_H_ */
