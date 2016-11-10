#include "app_init.h"
#include "app_HD44780.h"

void InitApp(void)
{  
    /*Init HD44780 Module*/
    app_HD44780_Init();
    
    return;
}