/* 
 * File:   ecu_motor.c
 * Author: yusuf
 *
 * Created on April 20, 2023, 1:51 AM
 */

#include "ecu_motor.h"

/**
 * @brief initialize the dc motor
 * @param dc_motor pointer to dc motor configuration
 * @return Std_ReturnType :
 *            E_ok     : the function done successfully
 *            E_NOT_OK : the function has issue   
 */
Std_ReturnType dc_motor_initialize (const dc_motor_t *dc_motor){
    Std_ReturnType ret = E_OK;
    if (NULL == dc_motor){
        ret = E_NOT_OK;
    }
    else {
        ret = gpio_pin_config_intialize (&(dc_motor->dc_motor_pin[0]));
        ret = gpio_pin_config_intialize (&(dc_motor->dc_motor_pin[1]));     
    }
    return ret; 
}

/**
 * @brief move the dc motor right
 * @param dc_motor pointer to dc motor configuration
 * @return Std_ReturnType :
 *            E_ok     : the function done successfully
 *            E_NOT_OK : the function has issue   
 */
Std_ReturnType dc_motor_forward (const dc_motor_t *dc_motor){
    Std_ReturnType ret = E_OK;
    if (NULL == dc_motor){
        ret = E_NOT_OK;
    }
    else {
        ret = gpio_pin_write_logic (&(dc_motor->dc_motor_pin[0]),HIGH);
        ret = gpio_pin_write_logic (&(dc_motor->dc_motor_pin[1]),LOW);
    }  
        return ret; 
}

/**
 * @brief move the dc motor left
 * @param dc_motor pointer to dc motor configuration
 * @return Std_ReturnType :
 *            E_ok     : the function done successfully
 *            E_NOT_OK : the function has issue   
 */
Std_ReturnType dc_motor_reverse (const dc_motor_t *dc_motor){
    Std_ReturnType ret = E_OK;
    if (NULL == dc_motor){
        ret = E_NOT_OK;
    }
    else {
        ret = gpio_pin_write_logic (&(dc_motor->dc_motor_pin[0]),LOW);
        ret = gpio_pin_write_logic (&(dc_motor->dc_motor_pin[1]),HIGH);
    } 
        return ret; 
}

/**
 * @brief turn off the dc motor
 * @param dc_motor pointer to dc motor configuration
 * @return Std_ReturnType :
 *            E_ok     : the function done successfully
 *            E_NOT_OK : the function has issue   
 */
Std_ReturnType dc_motor_off (const dc_motor_t *dc_motor){
    Std_ReturnType ret = E_OK;
    if (NULL == dc_motor){
        ret = E_NOT_OK;
    }
    else {
        ret = gpio_pin_write_logic (&(dc_motor->dc_motor_pin[0]),LOW);
        ret = gpio_pin_write_logic (&(dc_motor->dc_motor_pin[1]),LOW);
    } 
        return ret; 
}

