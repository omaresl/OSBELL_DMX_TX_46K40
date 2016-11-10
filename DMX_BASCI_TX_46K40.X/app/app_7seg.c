#include "system.h"
#include "app_convert.h"
#include "app_7seg.h"
#include "app_Display.h"
#include "PIN_Configuration.h"


static T_FLAG8 rub_DataBuffer;
static T_UBYTE rub_DigCount = DIGIT1;
void print_7seg(T_UWORD luw_Data){
    rub_DataBuffer.by = bcd27seg(luw_Data);
    PIN_A_7SEG = rub_DataBuffer.bi.bit0;
    PIN_B_7SEG = rub_DataBuffer.bi.bit1;
    PIN_C_7SEG = rub_DataBuffer.bi.bit2;
    PIN_D_7SEG = rub_DataBuffer.bi.bit3;
    PIN_E_7SEG = rub_DataBuffer.bi.bit4;
    PIN_F_7SEG = rub_DataBuffer.bi.bit5;
    PIN_G_7SEG = rub_DataBuffer.bi.bit6;
}

void app_7SegMux(void){
    switch(rub_DigCount){
        case DIGIT1:
            DIGIT2_MUX_PORT = FALSE;
            DIGIT3_MUX_PORT = FALSE;
            print_7seg(rub_BCDCen);
            DIGIT1_MUX_PORT = TRUE;
            rub_DigCount = DIGIT2;
            break;
        case DIGIT2:
            DIGIT1_MUX_PORT = FALSE;
            DIGIT3_MUX_PORT = FALSE;
            print_7seg(rub_BCDDec);
            DIGIT2_MUX_PORT = TRUE;
            rub_DigCount = DIGIT3;
            break;
        case DIGIT3:
            DIGIT1_MUX_PORT = FALSE;
            DIGIT2_MUX_PORT = FALSE;
            print_7seg(rub_BCDUni);
            DIGIT3_MUX_PORT = TRUE;
            rub_DigCount = DIGIT1;
            break;
        default:
            rub_DigCount = DIGIT1;
            break;
    }
}
    static T_FLAG8 lf_DigitMux;
void digits_off(){

    lf_DigitMux.bi.bit0 = DIGIT1_MUX_PORT;
    lf_DigitMux.bi.bit1 = DIGIT2_MUX_PORT;
    lf_DigitMux.bi.bit2 = DIGIT3_MUX_PORT;
    DIGIT1_MUX_PORT = FALSE;
    DIGIT2_MUX_PORT = FALSE;
    DIGIT3_MUX_PORT = FALSE;
}

void digits_on(){
    print_7seg(rub_DataBuffer.by);
    DIGIT1_MUX_PORT = lf_DigitMux.bi.bit0;
    DIGIT2_MUX_PORT = lf_DigitMux.bi.bit1;
    DIGIT3_MUX_PORT = lf_DigitMux.bi.bit2;
}