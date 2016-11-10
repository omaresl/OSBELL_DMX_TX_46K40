#include "system.h"
#include "stdtypedef.h"
#include "app_HD44780.h"
#include "PIN_Configuration.h"
#include "app_convert.h"
#include "../mcc_generated_files/mcc.h"
#include "app_DMX_TX.h"

#ifdef APP_HD44780_ENABLE
typedef struct
{
    T_UBYTE DB0 :1;
    T_UBYTE DB1 :1;
    T_UBYTE DB2 :1;
    T_UBYTE DB3 :1;
    T_UBYTE DB4 :1;
    T_UBYTE DB5 :1;
    T_UBYTE DB6 :1;
    T_UBYTE DB7 :1;
}T_HDDB;

typedef union
{
    T_UBYTE Byte;
    T_HDDB  Bits;
}T_HDDATA;

typedef struct
{
    T_UBYTE RS          :1;
    T_UBYTE RW          :1;
    T_UBYTE DATA_READY  :1;
    T_UBYTE HD_READY    :1;
    T_UBYTE unused      :3;
    T_HDDATA DATA;
    
}T_HD44780;

T_HD44780 ruw_HDBuffer;

typedef enum
{
    HD_SET_STATE = 0u,
    HD_DIS_CTRL,
    HD_MODE_SET,
    HD_INIT_DELAY
            
}T_HD_INIT_STATES;

static T_HD_INIT_STATES rub_HDInitState = HD_INIT_DELAY;

T_UBYTE rub_HDDelay = 5u;
static T_HD_INIT_STATES rub_HD_NextState = HD_SET_STATE;

T_UBYTE rub_SlotCounter = 0u;
T_UBYTE raub_DataBufferLine1[HD_MAX_SLOT] = "FOB Tester      ";
T_UBYTE raub_DataBufferLine2[HD_MAX_SLOT] = "Omar Sevilla    ";
T_UBYTE rub_Line = 0u;
T_UBYTE rub_SEQFLAG;


T_UBYTE app_HD44780_SenCmd(void)
{
    T_UBYTE lub_return = FALSE;
    
//    PIN_EN = FALSE;
    PIN_RS = ruw_HDBuffer.RS;
    PIN_RW = ruw_HDBuffer.RW;
    if(rub_SEQFLAG == FALSE) //First part of the cmd MSN
    {
        PIN_DB4 = ruw_HDBuffer.DATA.Bits.DB4;
        PIN_DB5 = ruw_HDBuffer.DATA.Bits.DB5;
        PIN_DB6 = ruw_HDBuffer.DATA.Bits.DB6;
        PIN_DB7 = ruw_HDBuffer.DATA.Bits.DB7;
        
        if(PIN_EN == FALSE)
        {
            PIN_EN = TRUE; //Enable Display
        }
        else
        {
            rub_SEQFLAG = TRUE;
            PIN_EN = FALSE; //Disable Display
        }
        
        lub_return = FALSE;

    }
    else
    {
        PIN_DB4 = ruw_HDBuffer.DATA.Bits.DB0;
        PIN_DB5 = ruw_HDBuffer.DATA.Bits.DB1;
        PIN_DB6 = ruw_HDBuffer.DATA.Bits.DB2;
        PIN_DB7 = ruw_HDBuffer.DATA.Bits.DB3;

        if(PIN_EN == FALSE)
        {
            PIN_EN = TRUE; //Enable Display
            lub_return = FALSE;
        }
        else
        {
            rub_SEQFLAG = FALSE;
            PIN_EN = FALSE; //Disable Display
            lub_return = TRUE;
        }
    }
    return(lub_return);
}

void app_HD44780_PrepareCMD(T_UBYTE lub_type,T_UBYTE lub_cmd)
{
    ruw_HDBuffer.RS = lub_type;
    ruw_HDBuffer.RW = 0u;
    ruw_HDBuffer.DATA.Byte = lub_cmd;
    ruw_HDBuffer.DATA_READY = TRUE;
}

void app_HD44780_Init(void)
{
    /*4 bit operation*/
    PIN_EN = FALSE;
    PIN_RS = 0u;
    PIN_RW = 0u;
    PIN_DB4 = 0u;
    PIN_DB5 = 1u;
    PIN_DB6 = 0u;
    PIN_DB7 = 0u;
    PIN_EN = TRUE;
    PIN_EN = FALSE;
    ruw_HDBuffer.HD_READY = FALSE;
}

void app_HD44780_Mngr(void)
{
    /*Initialize the HD*/
    if(ruw_HDBuffer.HD_READY == FALSE)
    {
        switch(rub_HDInitState)
        {
            case HD_SET_STATE:
            {
                app_HD44780_PrepareCMD(HD_CMD_TYPE,HD_FUNCSET); //Send Function Set
                if(app_HD44780_SenCmd() == TRUE)
                {
                    app_HD44780_CallInitDelay(1u,HD_DIS_CTRL); //Next STATE
                }
                else
                {
                    /*Wait for command sent*/
                }
            }break;
            case HD_DIS_CTRL:
            {
                app_HD44780_PrepareCMD(HD_CMD_TYPE,HD_DISCTRL); //Send Function Set
                if(app_HD44780_SenCmd() == TRUE)
                {
                    app_HD44780_CallInitDelay(1u,HD_MODE_SET); //Next STATE
                }
                else
                {
                    /*Wait for command sent*/
                }
            }break;
            case HD_MODE_SET:
            {
                app_HD44780_PrepareCMD(HD_CMD_TYPE,HD_FUNCSET); //Send Function Set
                if(app_HD44780_SenCmd() == TRUE)
                {
                    rub_HDInitState = HD_SET_STATE; //Next STATE
                    ruw_HDBuffer.HD_READY = TRUE;
                }
                else
                {
                    /*Wait for command sent*/
                }
            }break; 
            case HD_INIT_DELAY:
            {
                if(rub_HDDelay > 0u) //Check for the delay expiration
                {
                    rub_HDDelay--; //Decrement timer
                }
                else
                {
                    rub_HDInitState = rub_HD_NextState;
                }
            }break;
            default:
            {
                
            }break;
        }
    }
    else
    {
        if(rub_Line == 0u)//First Line
        {
            if(rub_SlotCounter < HD_MAX_SLOT)//Check for all slots are sent
            {
                app_HD44780_PrepareCMD(HD_CHAR_TYPE,raub_DataBufferLine1[rub_SlotCounter]);
                if(app_HD44780_SenCmd() == TRUE)
                {
                    rub_SlotCounter++;
                }
                else
                {
                    /*Wait for cmd sent*/
                }
            }
            else
            {                
                app_HD44780_PrepareCMD(HD_CMD_TYPE,HD_SEC_LINE);
                if(app_HD44780_SenCmd() == TRUE)
                {
                    rub_SlotCounter = 0u;//Reset the counter
                    rub_Line = 0x01; //CHange to Line 2
                }
                else
                {
                    /*Wait for cmd sent*/
                }
            }
        }
        else
        {
            if(rub_SlotCounter < HD_MAX_SLOT)//Check for all slots are sent
            {
                app_HD44780_PrepareCMD(HD_CHAR_TYPE,raub_DataBufferLine2[rub_SlotCounter]);
                if(app_HD44780_SenCmd() == TRUE)
                {
                    rub_SlotCounter++;
                }
                else
                {
                    /*Wait for cmd sent*/
                }
            }
            else
            {
                app_HD44780_PrepareCMD(HD_CMD_TYPE,HD_FIRST_LINE);
                if(app_HD44780_SenCmd() == TRUE)
                {
                    rub_SlotCounter = 0u;//Reset the counter
                    rub_Line = 0x00; //CHange to Line 1
                    GIE = FALSE;
                    app_HD44780_Init();
                    GIE = TRUE;
                }
                else
                {
                    /*Wait for cmd sent*/
                }
            }
        }
    }
}

void app_HD44780_CallInitDelay(T_UBYTE lub_delay, T_UBYTE lub_next_state)
{
    rub_HDDelay = lub_delay;
    rub_HD_NextState = lub_next_state;
    rub_HDInitState = HD_INIT_DELAY;
}

void app_HD44780_DisplayUpdate(void)
{
    bin2bcd(rub_DMX_DATA[0]);
    
    bcd2ascii();
    
    raub_DataBufferLine1[0] = rub_BCDCen;
    raub_DataBufferLine1[1] = rub_BCDDec;
    raub_DataBufferLine1[2] = rub_BCDUni;
    
//    static T_UBYTE lub_CharCounter = 0;
//    T_UBYTE lub_RXChar;
//    T_UBYTE lub_ForCounter;
//
//    
//    if(EUSART2_DataReady)
//    {
//        INTERRUPT_GlobalInterruptHighDisable();
//        lub_RXChar = EUSART2_Read();
//        INTERRUPT_GlobalInterruptHighEnable();
//        if(lub_RXChar == 'C')
//        {
//            lub_CharCounter = 0;
//            for(lub_ForCounter = 1;lub_ForCounter < 16u;lub_ForCounter++)
//            {
//                raub_DataBufferLine1[lub_ForCounter] = ' ';
//            }
//        }
//        else if(lub_RXChar == 'L')
//        {
//            lub_CharCounter = 16u;
//            for(lub_ForCounter = 1;lub_ForCounter < 16u;lub_ForCounter++)
//            {
//                raub_DataBufferLine2[lub_ForCounter] = ' ';
//            }            
//        }
//        else
//        {
//            /*Do Nothing*/
//        }
//        if(lub_CharCounter < 16u)
//        {
//            raub_DataBufferLine1[lub_CharCounter] = lub_RXChar;
//        }
//        else
//        {
//            raub_DataBufferLine2[lub_CharCounter - 16u] = lub_RXChar;
//        }
//        
//        lub_CharCounter++;
//        if(lub_CharCounter < 32)
//        {
//            /*Do Nothing*/
//        }
//        else
//        {
//            lub_CharCounter = 0;
//            
//        }
//    }
}
#endif