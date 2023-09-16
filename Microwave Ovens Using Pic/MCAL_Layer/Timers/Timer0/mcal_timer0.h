/* 
 * File:   mcal_timer0.h
 * Author: yusuf
 *
 * Created on May 3, 2023, 2:52 PM
 */

#ifndef MCAL_TIMER0_H
#define	MCAL_TIMER0_H

/* section : Includes   */
#include "../../GPIO/hal_gpio.h"
#include "../../Interrupt/mcal_internal_interrupt.h"

/* section : Micro Declaration  */
#define PRESCALER_ENABLE 0
#define PRESCALER_DISABLE 1

#define RISE_EDGE 0
#define FALL_EDGE 1

#define REGISTER_8BIT  1
#define REGISTER_16BIT 0

#define COUNTER_MODE 1
#define TIMER_MODE   0

/* section : Micro Function Declaration  */
#define TIMER0_ENABLE()            (T0CONbits.TMR0ON = 1)
#define TIMER0_DISABLE()           (T0CONbits.TMR0ON = 0)

#define TIMER0_8BIT_MODE()         (T0CONbits.T08BIT = 1)
#define TIMER0_16BIT_MODE()        (T0CONbits.T08BIT = 0)

#define TIMER0_TIMER_MODE()        (T0CONbits.T0CS = 0)
#define TIMER0_COUNTER_MODE()      (T0CONbits.T0CS = 1)

#define TIMER0_RISE_EDGE()         (T0CONbits.T0SE = 0)
#define TIMER0_FALL_EDGE()         (T0CONbits.T0SE = 1)

#define TIMER0_PRESCALER_ENABLE()  (T0CONbits.PSA = 0)
#define TIMER0_PRESCALER_DISABLE() (T0CONbits.PSA = 1)
/* section : Data Type Declaration  */
 
typedef enum {
    PRESCALER_2,
    PRESCALER_4,
    PRESCALER_8,
    PRESCALER_16,       
    PRESCALER_32,
    PRESCALER_64,
    PRESCALER_128,
    PRESCALER_256,           
}timer0_prescaler_select_t;

typedef struct{
#ifdef TIMER0_INTERRUPT
    void (* EXT_INTERRUPT)(void);
#endif    
    timer0_prescaler_select_t prescale_value;
    uint16 preload_value;
    Interrupt_priority_t priority;
    uint8 timer_register_mode : 1;
    uint8 timer_mode : 1;
    uint8 timer_edge : 1;
    uint8 prescaler_enable : 1;
}timer0_t;

/* section : Function Declaration  */

Std_ReturnType timer0_init(const timer0_t *timer0);
Std_ReturnType timer0_Deinit(const timer0_t *timer0);
Std_ReturnType timer0_Read (const timer0_t *timer0, uint16 *value);
Std_ReturnType timer0_write (const timer0_t *timer0, uint16 value);

#endif	/* MCAL_TIMER0_H */

