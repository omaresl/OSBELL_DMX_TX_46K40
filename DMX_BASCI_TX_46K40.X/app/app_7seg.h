/* 
 * File:   app_7seg.h
 * Author: Omar Sevilla
 *
 * Created on 7 de diciembre de 2013, 02:51 AM
 */

/*7 seg pins
 *      ------ +
 *      ------ Digit 3
 *      ------ Digit 2
 *      ------ Digit 1
 *      ------ f
 *      ------ g
 *      ------ a
 *      ------ b
 *      ------ c
 *      ------ d
 *      ------ e
*/

#ifndef APP_7SEG_H
#define	APP_7SEG_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "system.h"
#include "PIN_Configuration.h"

#define DIGITS      3
#define DIGIT1      0
#define DIGIT2      1
#define DIGIT3      2

    extern void print_7seg(T_UWORD luw_Data);
    extern void app_7SegMux(void);
    extern void digits_off(void);
    extern void digits_on(void);

#ifdef	__cplusplus
}
#endif

#endif	/* APP_7SEG_H */

