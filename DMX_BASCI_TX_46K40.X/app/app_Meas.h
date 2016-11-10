/* 
 * File:   app_Meas.h
 * Author: OmarEmanuel
 *
 * Created on 16 de julio de 2016, 04:55 PM
 */

#ifndef APP_MEAS_H
#define	APP_MEAS_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#define MEASURE_BUFFER_SIZE     3u
    
#define APP_MEAS_IS_CONVERISION_DONE    TRUE
#define APP_MEAS_GET_MEAS_VALUE         0x00
#define APP_MEAS_START_CONVERSION(CH)   
    
    extern T_UWORD ruw_DataMeasured[MEASURE_BUFFER_SIZE];
    extern T_UBYTE rub_CHMeasureCounter;

extern void app_MeasureMngr(void);
extern void app_MeasInit(void);


#ifdef	__cplusplus
}
#endif

#endif	/* APP_MEAS_H */

