/* 
 * File:   ecu_led.c
 * Author: yusuf
 *
 * Created on April 16, 2023, 2:47 PM
 */
#include "ecu_led.h"

/**
 * @brief initialize the assigned pin to be output ND TURN THE LED OFF
 * @param led : pointer to the led module configuration
 * @return Std_ReturnType :
 *            E_ok     : the function done successfully
 *            E_NOT_OK : the function has issue           
 */
Std_ReturnType led_initialize (const led_t *led){
    Std_ReturnType ret = E_OK;
    if (NULL == led){
        ret = E_NOT_OK;
    }
    else {
        pin_config_t led_cfg = {.port = led->port_name,.pin = led->pin,.direction = dirc_OUTPUT,.logic = led->led_status};
        ret = gpio_pin_config_intialize (&led_cfg);
    }
    return ret;
}

/**
 * @brief turn the led off
 * @param led : pointer to the led module configuration
 * @return Std_ReturnType :
 *            E_ok     : the function done successfully
 *            E_NOT_OK : the function has issue           
 */
Std_ReturnType led_off (const led_t *led){
    Std_ReturnType ret = E_OK;
    if (NULL == led){
        ret = E_NOT_OK;
    }
    else {
        pin_config_t led_cfg = {.port = led->port_name,.pin = led->pin,.direction = dirc_OUTPUT,.logic = led->led_status};
        ret = gpio_pin_write_logic (&led_cfg,LOW);        
    }    
    return ret;    
}

/**
 * @brief turn the led on
 * @param led : pointer to the led module configuration
 * @return Std_ReturnType :
 *            E_ok     : the function done successfully
 *            E_NOT_OK : the function has issue           
 */
Std_ReturnType led_on  (const led_t *led){
    Std_ReturnType ret = E_OK;
    if (NULL == led){
        ret = E_NOT_OK;
    }
    else {
        pin_config_t led_cfg = {.port = led->port_name,.pin = led->pin,.direction = dirc_OUTPUT,.logic = led->led_status};
        ret = gpio_pin_write_logic (&led_cfg,HIGH);         
    }    
    return ret;    
}

/**
 * @brief toggle the led 
 * @param led : pointer to the led module configuration
 * @return Std_ReturnType :
 *            E_ok     : the function done successfully
 *            E_NOT_OK : the function has issue           
 */
Std_ReturnType led_toggle (const led_t *led){
    Std_ReturnType ret = E_OK;
    if (NULL == led){
        ret = E_NOT_OK;
    }
    else {
        pin_config_t led_cfg = {.port = led->port_name,.pin = led->pin,.direction = dirc_OUTPUT,.logic = led->led_status};
        ret = gpio_pin_toggle_logic (&led_cfg);         
    }   
    return ret;    
}
