/* 
 * File:   hal_gpio.h
 * Author: yusuf
 *
 * Created on April 16, 2023, 2:33 PM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H

/* section : Includes   */
#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../../MCAL_Layer/device_config.h"
#include "hal_gpio_conf.h"
/* section : Macro Declaration  */

#define BIT_MASK   (uint8)1
#define PORT_PIN_MAX_NUM 7
#define PORT_MAX_NUM     4
#define PORT_MASK_FF     0xff

#define gpio_pin_conf    CONF_ENABLE
#define gpio_port_conf   CONF_ENABLE

/* section : Macro Function Declaration  */
#define HWREG (_X) (*((volatile uint8 *)(_x)))

#define SET_BIT(REG, BIT_POSN)    (REG |= ((BIT_MASK) << BIT_POSN))
#define CLEAR_BIT(REG, BIT_POSN)  (REG &= ~((BIT_MASK) << BIT_POSN))
#define TOGGLE_BIT(REG, BIT_POSN) (REG ^= ((BIT_MASK) << BIT_POSN))
#define READ_BIT(REG, BIT_POSN)   (REG >> (BIT_POSN) & (BIT_MASK))
 
/* section : Data Type Declaration  */
typedef enum {
    LOW = 0,
    HIGH
}logic_t;

typedef enum {
    dirc_OUTPUT = 0,
    dirc_INPUT
}direction_t;

typedef enum {
    PIN0 = 0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7
}pin_index_t;

typedef enum {
    PORTA_INDEX= 0,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX
}port_index_t;

typedef struct {
    uint8 port : 3;          /* &ref port_index_t */
    uint8 pin : 3;           /* &ref pin_index_t */
    uint8 direction : 1;     /* &ref direction_t */
    uint8 logic : 1;         /* &ref logic_t */
}pin_config_t;

/* section : Function Declaration  */

Std_ReturnType gpio_pin_direction_intialize (const pin_config_t *_pin_config);
Std_ReturnType gpio_pin_get_direction (const pin_config_t *_pin_config,direction_t *dic_statu);
Std_ReturnType gpio_pin_write_logic (const pin_config_t *_pin_config,logic_t logic);
Std_ReturnType gpio_pin_read_logic (const pin_config_t *_pin_config,logic_t *logic);
Std_ReturnType gpio_pin_toggle_logic (const pin_config_t *_pin_config);
Std_ReturnType gpio_pin_config_intialize (const pin_config_t *_pin_config);

Std_ReturnType gpio_port_direction_intialize (port_index_t port,uint8 dic_init);
Std_ReturnType gpio_port_get_direction (port_index_t port,uint8 *dic_statu);
Std_ReturnType gpio_port_write_logic (port_index_t port,uint8 logic);
Std_ReturnType gpio_port_read_logic (port_index_t port,uint8 *logic);
Std_ReturnType gpio_port_toggle_logic (port_index_t port);



#endif	/* HAL_GPIO_H */

