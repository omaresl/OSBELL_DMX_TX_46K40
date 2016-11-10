/*
 * app_command_processor.c
 *
 *  Created on: Nov 5, 2016
 *      Author: David Bellomo
 */

#include "app_command_processor.h"
#include "../mcc_generated_files/eusart2.h" /*TODO Como quitar el path*/
extern T_UBYTE rub_DMX_DATA[];
void (*rptr_Cmd_Functions[1])(T_UBYTE x) = {&app_CDM_DMX_Value_CHK_CON};
T_CDM_INDEX rub_CDM_FCT_Index = NO_CDM;
T_UWORD ruw_channel;
T_UWORD ruw_value;
T_UBYTE rub_set_Value_cnt;
T_UWORD * rptr_value_storage = &ruw_channel;
/******************************************************
   This functions receives the PTR of the command
     and will evaluate which is the action to be taken
********************************************************/

void app_Evaluate_Command(T_UBYTE lptr_Command){

	
	/*Check if the received command is valid*/
	if(IS_VALID_CMD(lptr_Command )){
		/*Command is valid proceed with the process*/
		switch(GET_CMD(lptr_Command)){
			/*case CHECK_CONNECTION:*/
			case DMX_VALUE:

				/*Set CDM Indext to the DXM_Value or Check Connection*/
				rub_CDM_FCT_Index  = DMX_SET_VALUE_CHK_CONN ;
			break;
			case DMX_STATUS:
			break;
			case GET_INFO:
			break;
			case VALUE_DMX_PORT:
			break;
			case BLACKOUT:
			break;
			case DMX_CHANNELS:
			break;
			case DMX_CHANNELS_EEPROM:
			break;
			case MERGE:
			break;
			case PROGRAM_RUN:
			break;
			default:
			/*No valid*/
			break;
		}
	
	}else{
		/*No action to be taken*/
	}


}


void app_main_dxm_command_fct(void){
T_UBYTE lub_read_character;
if(EUSART2_DataReady){
    lub_read_character = EUSART2_Read();
	if(rub_CDM_FCT_Index == NO_CDM){
		/*if CDM is not found and there is data evaluate the command*/
		app_Evaluate_Command(lub_read_character);
	}else{
		/*CMD is already identified execute the function of the command*/
		(*rptr_Cmd_Functions[rub_CDM_FCT_Index])(lub_read_character);
	}
}

}


void app_CDM_DMX_Value_CHK_CON(T_UBYTE lub_cmd_character){


	if(lub_cmd_character == 0x3Fu){
		/*This command is a Check Connection CDM since second char is ?*/
	}else{
		if(lub_cmd_character == 0x4Cu){
			rptr_value_storage = &ruw_value;
		}else{
			app_conver_ascii2int(&lub_cmd_character,rptr_value_storage,rub_set_Value_cnt);
			rub_set_Value_cnt++;
			if(rub_set_Value_cnt == 6u){
			/*write the value*/
                   rub_DMX_DATA[ruw_channel] = ruw_value;
			/*Clear states*/
			rub_set_Value_cnt = 0u;
			rub_CDM_FCT_Index =NO_CDM;
			ruw_channel = 0u;
			ruw_value = 0u;
			rptr_value_storage = &ruw_channel;
			}
		}
					
		
	}
}

void app_conver_ascii2int(T_UBYTE * lptr_data, T_UWORD* lptr_destiny_data, T_UBYTE lub_char_counter){
	T_UBYTE lub_temp;
	/*Convert the number of digits form ASCII to Int*/
	lub_temp = GET_INT_VALUE(*lptr_data);
	switch((lub_char_counter % 3)){
		case 0:
		*lptr_destiny_data = *lptr_destiny_data + (lub_temp*100);

		break;
		case 1:
		*lptr_destiny_data= *lptr_destiny_data + (lub_temp*10);

		break;
		case 2:	
		*lptr_destiny_data= *lptr_destiny_data + lub_temp;

		break;

	}
	

}

