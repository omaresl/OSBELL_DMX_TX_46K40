/* 
 * File:   app_command_processor.h
 * Author: David Bellomo
 *
 * Created on 05 de Nov de 2016
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

 

// TODO Insert appropriate #include <>

// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations

// Comment a function and leverage automatic documentation with slash star star
/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation

#ifdef	__cplusplus
extern "C" {   
#endif /* __cplusplus */
#include "stdtypedef.h"
#define GET_NB_CMD_BYTES() {nb_bytes}
#define ASCII_CLASS  0x4u
#define CMD_MASK  0x1Fu
#define GET_ASCII_CLASS(x)  (x>>ASCII_CLASS)
#define IS_VALID_CMD(x)  ( ((x>>ASCII_CLASS) == 4u) || ((x>>ASCII_CLASS) == 5u) )
#define GET_CMD(x)  (x & CMD_MASK)
#define INT_VALUE_ASCII_MASK  0x0Fu
#define GET_INT_VALUE(x)  ( INT_VALUE_ASCII_MASK  & x)
typedef enum{
	/*CHECK_CONNECTION = 3u,*/
	DMX_STATUS = 0x13u,
	GET_INFO= 0x9u,
	DMX_VALUE = 0x3u,
    VALUE_DMX_PORT = 0x16u,
	BLACKOUT = 0x2u,
	DMX_CHANNELS = 0x0Eu,
	DMX_CHANNELS_EEPROM = 0x05u,
	MERGE = 0x06u,
	PROGRAM_RUN = 0x12u
}T_CMD_CLASS;

typedef enum{
	DMX_SET_VALUE_CHK_CONN = 0u,
	NO_CDM
}T_CDM_INDEX;


extern void app_Evaluate_Command(T_UBYTE lptr_Command);
extern void app_main_dxm_command_fct(void);
extern void app_CDM_DMX_Value_CHK_CON(T_UBYTE lub_cmd_character);
extern void app_conver_ascii2int(T_UBYTE * lptr_data, T_UWORD* lptr_destiny_data, T_UBYTE lub_char_counter);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

