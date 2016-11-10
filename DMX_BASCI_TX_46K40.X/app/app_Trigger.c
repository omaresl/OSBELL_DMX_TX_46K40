#include "system.h"
#include "stdtypedef.h"
#include "app_Trigger.h"
#include "PIN_Configuration.h"
#include "app_Counter.h"

T_UBYTE rub_TriggerFlag = FALSE;
T_UWORD ruw_TriggerTimer = 0x00;

void app_TriggerMngr(void)
{
    if(rub_CounterMode == NORMAL)
    {
        /*Revisa si se activa el trigger*/
        if(rub_TriggerFlag == TRUE)
        {
            rub_TriggerFlag = FALSE;
            ruw_TriggerTimer = (ruw_OnCFG * TRIGGER_TASK_MULTIPLIER);//100ms
            VALVULA_A = TRUE;
            VALVULA_B = FALSE;
        }
        else if(ruw_TriggerTimer == 0x00)
        {
            VALVULA_A = FALSE;
            VALVULA_B = TRUE;
        }
        else
        {
            if(ruw_TriggerTimer > 0x00)
            {
                ruw_TriggerTimer--;
            }
            else
            {
                /*Do Nothing*/
            }
        }
    }
    else
    {
        app_TriggerInit();
    }
    return;
}

void app_TriggerInit(void)
{
    /*Valvulas Apagadas*/
    VALVULA_A = FALSE;
    VALVULA_B = FALSE;
}