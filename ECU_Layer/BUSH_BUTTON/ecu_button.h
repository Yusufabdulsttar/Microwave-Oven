/* 
 * File:   ecu_button.h
 * Author: yusuf
 *
 * Created on April 19, 2023, 1:06 PM
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H

/* section : Includes   */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_button_cfg.h"
 
/* section : Micro Declaration  */

/* section : Micro Function Declaration  */

/* section : Data Type Declaration  */
typedef enum {
    BUTTON_RELEASE,
    BUTTON_PUSHED
}button_state_t; 

typedef enum {
    BUTTON_ACTIVE_LOW,
    BUTTON_ACTIVE_HIGH
}button_conec_t;

typedef struct {
    pin_config_t pin_b;
    button_state_t button_state;
    button_conec_t button_conec;
}button_t;

/* section : Function Declaration  */
/**
 * @brief initialize the assigned pin to be input
 * @param button pointer to the button configuration
 * @return Std_ReturnType :
 *            E_ok     : the function done successfully
 *            E_NOT_OK : the function has issue           
 */
Std_ReturnType button_initialize (const button_t *button);
/**
 * @brief reade the assigned pin 
 * @param button pointer to the button configuration
 * @btn_s pointer to return button state
 * @return Std_ReturnType :
 *            E_ok     : the function done successfully
 *            E_NOT_OK : the function has issue           
 */
Std_ReturnType button_status (const button_t *button,button_state_t *btn_s);

#endif	/* ECU_BUTTON_H */

