/* 
 * File:   keypad.c
 * Author: yusuf
 *
 * Created on April 24, 2023, 1:11 PM
 */

#include "keypad.h"
static const uint8 keypad_value [KEYPAD_ROW][KEYPAD_COL] = {
                                              {'7','8','9','/'},
                                              {'4','5','6','*'},
                                              {'1','2','3','-'},
                                              {'#','0','=','+'}
};

Std_ReturnType keypad_initialize (const keypad_t *keypad){
    Std_ReturnType ret = E_OK;
	uint8 row = 0, columns =0;
    if (NULL == keypad){
        ret = E_NOT_OK;
    }
    else {
        for (row = 0; row < KEYPAD_ROW; row++){
            ret = gpio_pin_config_intialize (&(keypad->keypad_row[row]));
        }
        for (columns = 0; columns < KEYPAD_COL; columns++){
            ret = gpio_pin_direction_intialize (&(keypad->keypad_col[columns]));
        }
    }
    return ret;   
} 


Std_ReturnType keypad_read (const keypad_t *keypad , uint8 *key){
    Std_ReturnType ret = E_OK;
    logic_t key_c = 0;
    uint8 rows_counter = 0 ,columns_counter = 0,counter = 0,newkey=0;
    
    if (NULL == keypad || NULL == key){
        ret = E_NOT_OK;
    }
    else {
        for (rows_counter = 0; rows_counter < KEYPAD_ROW; rows_counter++){
            for (counter = 0; counter < KEYPAD_ROW; counter++){
                ret = gpio_pin_write_logic (&(keypad->keypad_row[counter]),(LOW));
            }
            gpio_pin_write_logic (&(keypad->keypad_row[rows_counter]),(HIGH));
			__delay_ms(10);
            for (columns_counter = 0; columns_counter < KEYPAD_COL; columns_counter++){
                ret = gpio_pin_read_logic (&(keypad->keypad_col[columns_counter]),&key_c);
                if (HIGH == key_c){
                    *key =  keypad_value[rows_counter][columns_counter]; 
                }
            }
        }
          
    }
    return ret;       
}

 