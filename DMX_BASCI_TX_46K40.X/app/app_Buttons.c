#include "app_Buttons.h"
#include "system.h"
#include "stdtypedef.h"
#include "PIN_Configuration.h"

T_PRESS_TYPE rub_ButtonStatus[N_BUTTONS] = { UNPRESSED };
T_UBYTE rub_ButtonDebounceCounter[N_BUTTONS];
T_FLAG8 rsub_EmulationFlags;

void app_CheckButtons(void)
{
    app_Button1();
    app_Button2();
    app_Button3();
    return;
}

void app_Button1(void)
{
    /*Check for Button 1*/
    if(BUTTON1 == TRUE)
    {
        if(rub_ButtonDebounceCounter[0x00] < EMULATION_TIME)//Avoid Overflow
        {
            rub_ButtonDebounceCounter[0x00]++;
        }
        else
        {
            //rub_ButtonDebounceCounter[0x00] = 0u;
            //rub_ButtonStatus[0x00] = SHORT_PRESS; //Button 2 Press emulation
            BTN1_EMULATED = TRUE;
        }
    }
    else
    {
        if((rub_ButtonDebounceCounter[0x00] >= MIN_DEBOUNCE_TIME) && (BTN1_EMULATED == FALSE))
        {
            rub_ButtonStatus[0x00] = SHORT_PRESS;
        }
        else
        {
            BTN1_EMULATED = FALSE;
        }
        rub_ButtonDebounceCounter[0x00] = 0u;
    }
    return;
}

void app_Button2(void)
{
    /*Check for Button 1*/
    if(BUTTON2 == TRUE)
    {
        if(rub_ButtonDebounceCounter[0x01] < EMULATION_TIME)//Avoid Overflow
        {
            rub_ButtonDebounceCounter[0x01]++;
        }
        else
        {
            //rub_ButtonDebounceCounter[0x01] = 0u;
            rub_ButtonStatus[0x01] = SHORT_PRESS; //Button 2 Press emulation
            BTN2_EMULATED = TRUE;
        }
    }
    else
    {
        if((rub_ButtonDebounceCounter[0x01] >= MIN_DEBOUNCE_TIME) && (BTN2_EMULATED == FALSE))
        {
            rub_ButtonStatus[0x01] = SHORT_PRESS;
        }
        else
        {
            BTN2_EMULATED = FALSE;
        }
        rub_ButtonDebounceCounter[0x01] = 0u;
    }
    return;
}

void app_Button3(void)
{
    /*Check for Button 1*/
    if(BUTTON3 == TRUE)
    {
        if(rub_ButtonDebounceCounter[0x02] < EMULATION_TIME)//Avoid Overflow
        {
            rub_ButtonDebounceCounter[0x02]++;
        }
        else
        {
            //rub_ButtonDebounceCounter[0x02] = 0u;
            rub_ButtonStatus[0x02] = SHORT_PRESS; //Button 3 Press emulation
            BTN3_EMULATED = TRUE;
        }
    }
    else
    {
        if((rub_ButtonDebounceCounter[0x02] >= MIN_DEBOUNCE_TIME) && (BTN3_EMULATED == FALSE))
        {
            rub_ButtonStatus[0x02] = SHORT_PRESS;
        }
        else
        {
            BTN3_EMULATED = FALSE;
        }
        rub_ButtonDebounceCounter[0x02] = 0u;
    }
    return;
}