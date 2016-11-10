#include "app_Counter.h"
#include "PIN_Configuration.h"
#include "app_Buttons.h"
#include "app_Display.h"
#include "app_Trigger.h"

T_UBYTE rub_CountDebounceCounter = 0x00;
T_UWORD ruw_Count = 0x00;
T_COUNTER_MODE rub_CounterMode = NORMAL;

__eeprom T_UWORD euw_MaxCount = 10u;
__eeprom T_UWORD euw_OnCFG = 10u;

T_UWORD ruw_MaxCount = 0u;
T_UWORD ruw_OnCFG = 0u;

void app_CounterInit(void)
{
    ruw_MaxCount = euw_MaxCount;
    ruw_OnCFG = euw_OnCFG;
    rub_CounterMode = MAX_COUNT_CFG;
    rub_TextTimer = TEXT_TIME;
    return;
}

void app_CounterMngr(void)
{
    if(rub_CounterMode == NORMAL)
    {
        app_CounterCheckInput();
    }
    else
    {
        /*Do Nothing*/
    }
}

void app_CounterCheckInput(void)
{
    COUNT_INDICATOR = !(COUNT_INPUT); //Set indicator to the Input
    if(COUNT_INPUT == FALSE)
    {
        /*Revisa si el conador de debounce ya supero su valor maximo*/
        if(rub_CountDebounceCounter < MAX_DEBOUNCE_COUNTER)
        {
            /*Incrementa el contador de debounce*/
            rub_CountDebounceCounter++;
        }
        else
        {
            /*Do Nothing*/
        }
    }
    else
    {
        /*Revisa si la cuenta es valida*/
        if(rub_CountDebounceCounter >= COUNTER_DEBOUNCE)
        {
            /*Incrementa la cuenta*/
            app_CounterIncrement();
        }
        else
        {
            /*Do Nothing*/
        }
        /*Reinicia el contador*/
        rub_CountDebounceCounter = 0x00;
        
    }
}

void app_CounterModeManager(void)
{
    if(rub_ButtonStatus[0x00] == SHORT_PRESS)
    {
        rub_ButtonStatus[0x00] = UNPRESSED;
        if(rub_CounterMode < LAST_CFG - 1)
        {
            rub_CounterMode++;
            rub_TextTimer = TEXT_TIME;
        }
        else
        {
            app_CounterUpdateEeprom();
            rub_CounterMode = NORMAL;
        }
    }
    else
    {
        
    }
}

void app_CounterCFGMngr(void)
{
    if(rub_ButtonStatus[0x01] == SHORT_PRESS)
    {
        rub_ButtonStatus[0x01] = UNPRESSED;
        /*Revisa el modo de operacion actual*/
        switch(rub_CounterMode)
        {
            case MAX_COUNT_CFG:
                /*Incrementa coniguracion de contador*/
                if(ruw_MaxCount < MAX_COUNTER)
                {
                    ruw_MaxCount++;
                }
                else
                {
                    /*Reinicia configuracion si el valor ha alcanzado el maximo*/
                    ruw_MaxCount = MIN_COUNTER;
                }
                break;
            case ON_CFG:
                /*Incementa configuracion de encendido*/
                if(ruw_OnCFG < MAX_ON_CFG)
                {
                    ruw_OnCFG++;
                }
                else
                {
                    /*Reinicia configuracion si ha alcanzado el limite*/
                    ruw_OnCFG = MIN_ON_CFG;
                }
                break;
            default:
                /*Do Nothing*/
                break;               
        }
    }
    else if(rub_ButtonStatus[0x02] == SHORT_PRESS)
    {
        rub_ButtonStatus[0x02] = UNPRESSED;
        /*Revisa el modo de operacion actual*/
        switch(rub_CounterMode)
        {
            case MAX_COUNT_CFG:
                /*Decrementa configuracion de contador*/
                if(ruw_MaxCount > MIN_COUNTER)
                {
                    ruw_MaxCount--;
                }
                else
                {
                    /*Usa el ultimo valor si se alcanzo el minimo*/
                    ruw_MaxCount = MAX_COUNTER;
                }
                break;
            case ON_CFG:
                /*Decrementa configuracion de encendido*/
                if(ruw_OnCFG > MIN_ON_CFG)
                {
                    ruw_OnCFG--;
                }
                else
                {
                    /*Usa el ultimo valor si se alcanzo el minimo*/
                    ruw_OnCFG = MAX_ON_CFG;
                }
                break;
            default:
                /*Do Nothing*/
                break;               
        }
    }
    else
    {
        /*Do Nothing*/
    }
}

void app_CounterUpdateEeprom(void)
{
    GIE = FALSE;
    /*Actualiza valores de eeprom*/
    euw_MaxCount = ruw_MaxCount;
    euw_OnCFG = ruw_OnCFG;
    GIE = TRUE;
}

void app_CounterIncrement()
{
    ruw_Count++;
    if(ruw_Count >= ruw_MaxCount)
    {
        ruw_Count = 0;
        rub_TriggerFlag = TRUE;
    }
    else
    {
        /*Do Nothing*/
    }
}