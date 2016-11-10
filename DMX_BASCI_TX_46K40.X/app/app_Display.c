#include "app_Display.h"
#include "app_7seg.h"
#include "app_Counter.h"
#include "app_convert.h"
#include "app_Meas.h"

T_UBYTE rub_TextTimer = 0;
void app_UpdateCounterDisplay(void)
{
    switch(rub_CounterMode)
    {
        case MAX_COUNT_CFG:
            /*Show Text*/
            if(rub_TextTimer > 0x00)
            {
                rub_BCDCen = 0xC60; //C
                rub_BCDDec = 0x8E0; //F
                rub_BCDUni = 0x820; //G
            }
            else
            {
                bin2bcd((T_UWORD)(ruw_MaxCount));
            }
            break;
        case ON_CFG:
            /*Show Text*/
            if(rub_TextTimer > 0x00)
            {
                rub_BCDCen = 0x400; //O
                rub_BCDDec = 0xAB0; //n
                rub_BCDUni = 0xFF0; //BLANK
            }
            else
            {
                bin2bcd((T_UWORD)(ruw_OnCFG));
            }
            break;
        default:
            bin2bcd(ruw_Count);
            break;
    }
}

void app_UpdateADCDisplay(void)
{
    bin2bcd(ruw_DataMeasured[0x00] >> 2);
}

void app_TextTimerMng(void)
{
    if(rub_TextTimer > 0x00)
    {
        rub_TextTimer--;
    }
    else
    {
        /*Do Nohting*/
    }
}
