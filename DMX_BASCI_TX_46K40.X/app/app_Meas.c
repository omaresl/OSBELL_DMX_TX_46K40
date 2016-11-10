#include "system.h"
#include "stdtypedef.h"
#include "app_Meas.h"

T_UWORD ruw_DataMeasured[MEASURE_BUFFER_SIZE];
T_UBYTE rub_CHMeasureCounter = 0x00;

void app_MeasureMngr(void)
{
    if(APP_MEAS_IS_CONVERISION_DONE == TRUE) 
    {
        /*Get the value from ADC module*/
        ruw_DataMeasured[rub_CHMeasureCounter] = APP_MEAS_GET_MEAS_VALUE;
        
        if(rub_CHMeasureCounter < (MEASURE_BUFFER_SIZE - 1))
        {
            rub_CHMeasureCounter++;
        }
        else
        {
            rub_CHMeasureCounter = 0x00;
        }
        APP_MEAS_START_CONVERSION(rub_CHMeasureCounter); //Start the measure of the ADC
    }
}

void app_MeasInit(void)
{
    T_UBYTE lub_count;
    
    for(lub_count = 0; lub_count < MEASURE_BUFFER_SIZE; lub_count++)
    {
        ruw_DataMeasured[lub_count] = 0x00;
    }
}