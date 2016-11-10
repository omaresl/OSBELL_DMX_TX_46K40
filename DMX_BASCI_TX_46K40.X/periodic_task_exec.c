#include "periodic_task_exec.h"
#include "app/app_HD44780.h"
#include "mcc_generated_files/mcc.h"
#include "app/app_command_processor.h"

void periodic_task_tk(void)
{
    app_main_dxm_command_fct();
}

void periodic_task_2tk(void)
{
    app_HD44780_DisplayUpdate();
    app_HD44780_Mngr();
    return;
}

void periodic_task_4tk(void)
{
    return;
}

void periodic_task_8tk(void)
{
    return;
}

void periodic_task_32tk(void)
{
    return;
}

void periodic_task_1024tk(void)
{
    return;
}

void TASK_DUMMY(void)
{
    return;
}