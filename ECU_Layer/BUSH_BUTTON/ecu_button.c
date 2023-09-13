/* 
 * File:   ecu_button.c
 * Author: yusuf
 *
 * Created on April 19, 2023, 1:08 PM
 */

#include "ecu_button.h"
/**
 * @brief initialize the assigned pin to be input
 * @param button pointer to the button configuration
 * @return Std_ReturnType :
 *            E_ok     : the function done successfully
 *            E_NOT_OK : the function has issue           
 */
Std_ReturnType button_initialize (const button_t *button){
    Std_ReturnType ret = E_OK;
    if (NULL == button){
        ret = E_NOT_OK;
    }
    else {
        ret = gpio_pin_direction_intialize (&(button->pin_b));
    }
    return ret; 
}

/**
 * @brief reade the assigned pin 
 * @param button pointer to the button configuration
 * @btn_s pointer to return button state
 * @return Std_ReturnType :
 *            E_ok     : the function done successfully
 *            E_NOT_OK : the function has issue           
 */
Std_ReturnType button_status (const button_t *button,button_state_t *btn_s){
    Std_ReturnType ret = E_OK;
    logic_t logic = LOW;
    if ((NULL == button) || (NULL == btn_s)){
        ret = E_NOT_OK;
    }
    else {
        ret = gpio_pin_read_logic (&(button->pin_b),&logic);
        if (button->button_conec == BUTTON_ACTIVE_HIGH){
            if (HIGH == logic){
                *btn_s = BUTTON_PUSHED;
            }
            else if (LOW == logic){
                *btn_s = BUTTON_RELEASE;
            }
        }
        else if(button->button_conec == BUTTON_ACTIVE_LOW){
            if (HIGH == logic){
                *btn_s = BUTTON_RELEASE;
            }
            else if (LOW == logic){
                *btn_s = BUTTON_PUSHED;
            }
        }
    }
    return ret;
}
