/* 
 * File:   hal_gpio.c
 * Author: yusuf
 *
 * Created on April 16, 2023, 2:33 PM
 */

#include "hal_gpio.h"


volatile uint8 *tris_reg[] = {&TRISA,&TRISB,&TRISC,&TRISD,&TRISE};
volatile uint8 *lat_reg[]  = {&LATA,&LATB,&LATC,&LATD,&LATE};
volatile uint8 *port_reg[] = {&PORTA,&PORTB,&PORTC,&PORTD,&PORTE};

/**
 * #brief initialize the direction of a specific pin
 * @param _pin_config : pint to configuration
 * @return Std_ReturnType
 *                E_ok : the function done successfully 
 *                E_not_ok : the function has issue 
 */
#if gpio_pin_conf == CONF_ENABLE
Std_ReturnType gpio_pin_direction_intialize (const pin_config_t *_pin_config){
    Std_ReturnType ret = E_OK;
    if (NULL == _pin_config || _pin_config->pin >= PORT_PIN_MAX_NUM){
        ret = E_NOT_OK; 
    }
    else {
        ret = E_OK;
        switch (_pin_config->direction){
            case dirc_OUTPUT : 
                CLEAR_BIT(*tris_reg[_pin_config->port] ,_pin_config->pin );
                break;
            
            case dirc_INPUT :
                SET_BIT(*tris_reg[_pin_config->port], _pin_config->pin);
                break;
            default : ret = E_NOT_OK;  
        }        
    }
    return ret;
}
#endif
/**
 * #brief get direction of a specific pin
 * @param _pin_config : pint to configuration
 * @param dic_statu
 * @return Std_ReturnType
 *                E_ok : the function done successfully 
 *                E_not_ok : the function has issue 
 */
#if gpio_pin_conf == CONF_ENABLE
Std_ReturnType gpio_pin_get_direction (const pin_config_t *_pin_config,direction_t *dic_statu){
    Std_ReturnType ret = E_OK;
    if (NULL == _pin_config || NULL == dic_statu  || _pin_config->pin >= PORT_PIN_MAX_NUM){
        ret = E_NOT_OK;
    }
    else {
        *dic_statu = READ_BIT(*tris_reg[_pin_config->port], _pin_config->pin);
    }
    return ret;
}
#endif
/**
 * #brief write logic to a specific pin
 * @param _pin_config : pint to configuration
 * @param logic
 * @return Std_ReturnType
 *                E_ok : the function done successfully 
 *                E_not_ok : the function has issue 
 */
#if gpio_pin_conf == CONF_ENABLE
Std_ReturnType gpio_pin_write_logic (const pin_config_t *_pin_config,logic_t logic){
    Std_ReturnType ret = E_OK;
    if (NULL == _pin_config || _pin_config->pin >= PORT_PIN_MAX_NUM){
        ret = E_NOT_OK;
    }
    else {
         ret = E_OK;
        switch (logic){
            case LOW : 
                CLEAR_BIT(*lat_reg[_pin_config->port] ,_pin_config->pin );
                break;
            
            case HIGH :
                SET_BIT(*lat_reg[_pin_config->port], _pin_config->pin);
                break;
            default : ret = E_NOT_OK;  
        }       
    }
    return ret;
}
#endif
/**
 * 
 * @param _pin_config : pint to configuration
 * @param logic
 * @return Std_ReturnType
 *                E_ok : the function done successfully 
 *                E_not_ok : the function has issue 
 */
#if gpio_pin_conf == CONF_ENABLE
Std_ReturnType gpio_pin_read_logic (const pin_config_t *_pin_config,logic_t *logic){
    Std_ReturnType ret = E_OK;
    if (NULL == _pin_config || NULL == logic || _pin_config->pin >= PORT_PIN_MAX_NUM){
        ret = E_NOT_OK;
        
    }
    else {
        *logic = READ_BIT(*port_reg[_pin_config->port], _pin_config->pin);
             
    }
    return ret;    
}
#endif
/**
 * 
 * @param _pin_config : pint to configuration
 * @return Std_ReturnType
 *                E_ok : the function done successfully 
 *                E_not_ok : the function has issue 
 */
#if gpio_pin_conf == CONF_ENABLE
Std_ReturnType gpio_pin_toggle_logic (const pin_config_t *_pin_config){
    Std_ReturnType ret = E_OK;
    if (NULL == _pin_config || _pin_config->pin >= PORT_PIN_MAX_NUM){
        ret = E_NOT_OK;  
    }
    else {
        ret = E_OK;
        TOGGLE_BIT(*lat_reg[_pin_config->port], _pin_config->pin);
    }
    return ret;        
}
#endif
/**
 * 
 * @param _pin_config : pint to configuration
 * @return Std_ReturnType
 *                E_ok : the function done successfully 
 *                E_not_ok : the function has issue 
 */
#if gpio_pin_conf == CONF_ENABLE
Std_ReturnType gpio_pin_config_intialize (const pin_config_t *_pin_config){
    Std_ReturnType ret = E_OK;
    if (NULL == _pin_config || _pin_config->pin >= PORT_PIN_MAX_NUM){
        ret = E_NOT_OK;  
    }
    else {
        ret = E_OK;
        gpio_pin_direction_intialize (_pin_config);
        gpio_pin_write_logic (_pin_config,_pin_config->logic);
    }
    return ret;        
}
#endif
/**
 * 
 * @param port
 * @param dic_init
 * @return Std_ReturnType
 *                E_ok : the function done successfully 
 *                E_not_ok : the function has issue 
 */
#if gpio_port_conf == CONF_ENABLE
Std_ReturnType gpio_port_direction_intialize (port_index_t port,uint8 dic_init){
    Std_ReturnType ret = E_OK;
    if (port >= PORT_MAX_NUM){
        ret = E_NOT_OK;
    }
    else {
        *tris_reg[port] = dic_init;
    }
    return ret;        
}
#endif
/**
 * 
 * @param port
 * @param dic_statu
 * @return Std_ReturnType
 *                E_ok : the function done successfully 
 *                E_not_ok : the function has issue 
 */
#if gpio_port_conf == CONF_ENABLE
Std_ReturnType gpio_port_get_direction (port_index_t port,uint8 *dic_statu){
    Std_ReturnType ret = E_OK;
    if (NULL == dic_statu || port >= PORT_MAX_NUM){
        ret = E_NOT_OK;
    }
    else {
        *dic_statu = *tris_reg[port];
    }
    return ret;        
}
#endif
/**
 * 
 * @param port
 * @param logic
 * @return Std_ReturnType
 *                E_ok : the function done successfully 
 *                E_not_ok : the function has issue 
 */
#if gpio_port_conf == CONF_ENABLE
Std_ReturnType gpio_port_write_logic (port_index_t port,uint8 logic){
    Std_ReturnType ret = E_OK;
    if (port >= PORT_MAX_NUM){
        ret = E_NOT_OK;
    }
    else {
        *lat_reg[port] = logic;
    }
    
    return ret;      
}
#endif
/**
 * 
 * @param port
 * @param logic
 * @return Std_ReturnType
 *                E_ok : the function done successfully 
 *                E_not_ok : the function has issue 
 */
#if gpio_port_conf == CONF_ENABLE
Std_ReturnType gpio_port_read_logic (port_index_t port,uint8 *logic){
    Std_ReturnType ret = E_OK;
    if (NULL == logic || port >= PORT_MAX_NUM){
        ret = E_NOT_OK;
        
    }
    else {
        *logic = *port_reg[port];
    }
    return ret;      
}
#endif
/**
 * 
 * @param port
 * @return Std_ReturnType
 *                E_ok : the function done successfully 
 *                E_not_ok : the function has issue 
 */
#if gpio_port_conf == CONF_ENABLE
Std_ReturnType gpio_port_toggle_logic (port_index_t port){
    Std_ReturnType ret = E_OK;
    if (port >= PORT_MAX_NUM){
        ret = E_NOT_OK;    
    }
    else {
         *lat_reg[port] ^= PORT_MASK_FF;
    }
    return ret;        
}
#endif