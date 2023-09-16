/* 
 * File:   keypad.c
 * Author: Yusuf_Abdulsttar
 * linkedin : https://www.linkedin.com/in/yusuf-abdulsttar-3087b6ab/
 * Created on September 14, 2023, 2:12 PM
 */

#include <keypad.h>
static const uint8_t keypad_value [KEYPAD_ROW][KEYPAD_COL] = {
                                              {'7','8','9','/'},
                                              {'4','5','6','*'},
                                              {'1','2','3','-'},
                                              {'#','0','=','+'}
};


void keypad_initialize (const keypad_t *keypad){
	uint8_t row = 0, columns =0;

        for (row = 0; row < KEYPAD_ROW; row++){
            HAL_GPIO_WritePin((keypad->keypad_row[row].port), (keypad->keypad_row[row].pin), GPIO_PIN_RESET);
        }
}
void keypad_read (const keypad_t *keypad , uint8_t *key){
    logic_t key_c = 0;
    uint8_t rows_counter = 0 ,columns_counter = 0,counter = 0;

        for (rows_counter = 0; rows_counter < KEYPAD_ROW; rows_counter++){
            for (counter = 0; counter < KEYPAD_ROW; counter++){
            	HAL_GPIO_WritePin((keypad->keypad_row[counter].port), (keypad->keypad_row[counter].pin), GPIO_PIN_RESET);
            }
            HAL_GPIO_WritePin((keypad->keypad_row[rows_counter].port), (keypad->keypad_row[rows_counter].pin), GPIO_PIN_SET);
			HAL_Delay(10);
            for (columns_counter = 0; columns_counter < KEYPAD_COL; columns_counter++){
            	key_c = HAL_GPIO_ReadPin((keypad->keypad_col[columns_counter].port), (keypad->keypad_col[columns_counter].pin));
                if (HIGH == key_c){
                    *key =  keypad_value[rows_counter][columns_counter]; 
                }
            }
        }

}

 
