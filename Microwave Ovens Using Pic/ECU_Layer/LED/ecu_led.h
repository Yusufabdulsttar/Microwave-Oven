/* 
 * File:   ecu_led.h
 * Author: yusuf
 *
 * Created o    n April 16, 2023, 2:47 PM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H

/* section : Includes   */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_led_cfg.h"


/* section : Micro Declaration  */

/* section : Micro Function Declaration  */

/* section : Data Type Declaration  */
typedef enum {
    LED_OFF,
    LED_ON        
}led_status_t; 

typedef struct {
    uint8 port_name  : 4;
    uint8 pin        : 3;
    uint8 led_status : 1;
}led_t;

/* section : Function Declaration  */

Std_ReturnType led_initialize (const led_t *led);
Std_ReturnType led_off (const led_t *led);
Std_ReturnType led_on  (const led_t *led);
Std_ReturnType led_toggle (const led_t *led);

#endif	/* ECU_LED_H */

