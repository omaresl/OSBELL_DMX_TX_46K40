/*
 * app_convert.c
 *
 *  Created on: Oct 17, 2013
 *      Author: Omar Sevilla
 */

#include "stdtypedef.h"
#include "app_convert.h"


 T_UWORD 	rub_BCDUni = 0,
                rub_BCDDec = 0,
                rub_BCDCen = 0,
                rub_BCDUmil = 0,
                rub_BCDDmil = 0,
                rub_BCDCmil = 0;        //pgfedcba
 const T_UBYTE  rub_7segSymbols[16] = { 0b11000000,     //0
                                        0b11111001,     //1
                                        0b10100100,     //2
                                        0b10110000,     //3
                                        0b10011001,     //4
                                        0b10010010,     //5
                                        0b10000010,     //6
                                        0b11111000,     //7
                                        0b10000000,     //8
                                        0b10011000,     //9
                                        0b10001000,     //A
                                        0b10000011,     //b
                                        0b11000110,     //C
                                        0b10100001,     //d
                                        0b10000110,     //E
                                        0b10001110,     //F
                                        };
void bin2bcd(T_UWORD luw_Bin_Data){
	T_UWORD luw_aux;
	luw_aux = luw_Bin_Data;
	rub_BCDCmil = (luw_aux / 100000);
	luw_aux = (luw_aux - (rub_BCDCmil*100000)); 
	rub_BCDDmil = (luw_aux / 10000);
	luw_aux = (luw_aux - (rub_BCDDmil*10000)); 
	rub_BCDUmil = (luw_aux / 1000);
	luw_aux = (luw_aux - (rub_BCDUmil*1000)); 
	rub_BCDCen = (luw_aux / 100);
	luw_aux = (luw_aux - (rub_BCDCen*100));
	rub_BCDDec = (luw_aux / 10);
	luw_aux = (luw_aux - (rub_BCDDec*10));
	rub_BCDUni = (luw_aux);
}

void bcd2ascii(void)
{
	rub_BCDUni += 0x30;
	rub_BCDDec += 0x30;
	rub_BCDCen += 0x30;
	rub_BCDUmil += 0x30;
	rub_BCDDmil += 0x30;
	rub_BCDCmil += 0x30;
}

T_UBYTE bcd27seg(T_UWORD luw_BCDData){
    if(luw_BCDData <= 0x000f){
        return(rub_7segSymbols[luw_BCDData]);
    }
    else{
        return(luw_BCDData >> 4);//X
    }
}
