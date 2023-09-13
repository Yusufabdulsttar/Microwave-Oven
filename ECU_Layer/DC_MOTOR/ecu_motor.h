/* 
 * File:   ecu_motor.h
 * Author: yusuf
 *
 * Created on April 20, 2023, 1:51 AM
 */

#ifndef EUC_MOTOR_H
#define	EUC_MOTOR_H

/* section : Includes   */
#include "ecu_motor_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* section : Micro Declaration  */


/* section : Micro Function Declaration  */

/* section : Data Type Declaration  */
typedef enum {
    DC_MOTOR_OFF,
    DC_MOTOR_ON        
}dc_motor_state_t;


typedef struct {
    pin_config_t dc_motor_pin[2];
}dc_motor_t;

/* section : Function Declaration  */
Std_ReturnType dc_motor_initialize (const dc_motor_t *dc_motor);
Std_ReturnType dc_motor_forward (const dc_motor_t *dc_motor);
Std_ReturnType dc_motor_reverse (const dc_motor_t *dc_motor);
Std_ReturnType dc_motor_off (const dc_motor_t *dc_motor);


#endif	/* EUC_MOTOR_H */

