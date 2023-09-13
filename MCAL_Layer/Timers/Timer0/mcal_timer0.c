/* 
 * File:   mcal_timer0.c
 * Author: yusuf
 *
 * Created on May 3, 2023, 2:52 PM
 */

#include "mcal_timer0.h"

#ifdef TIMER0_INTERRUPT 
static void(* TIMER0_INTHANDLER)(void) = NULL;
#endif

static uint16 preload_value = 0;

Std_ReturnType timer0_init(const timer0_t *timer0){
    Std_ReturnType ret = E_OK;
    if (NULL == timer0){
        ret = E_NOT_OK;
    }
    else {
        /*disable timer0*/
        TIMER0_DISABLE();
        /*8bit mode or 16bit mode*/
        if(REGISTER_8BIT == timer0->timer_register_mode){
            TIMER0_8BIT_MODE();
        }
        else if(REGISTER_16BIT == timer0->timer_register_mode){
            TIMER0_16BIT_MODE();
        }
        /*timer mode or counter mode*/
        if(COUNTER_MODE == timer0->timer_mode){
            TIMER0_COUNTER_MODE();
        }
        else if(TIMER_MODE == timer0->timer_mode){
            TIMER0_TIMER_MODE();
        }
        /*rising edge or falling edge*/
        if(RISE_EDGE == timer0->timer_edge){
            TIMER0_RISE_EDGE();
        }
        else if(FALL_EDGE == timer0->timer_edge){
            TIMER0_FALL_EDGE();
        }
        /*prescaler enable and its value*/
        if(PRESCALER_ENABLE == timer0->prescaler_enable){
            TIMER0_PRESCALER_ENABLE();
            T0CONbits.T0PS = timer0->prescale_value;
        }
        else if(PRESCALER_DISABLE == timer0->prescaler_enable){
            TIMER0_PRESCALER_DISABLE();
        }
        /*preload value */
        TMR0H = (uint8)(timer0->preload_value >> 8); 
        TMR0L = (uint8) timer0->preload_value;
        preload_value = timer0->preload_value;
        /*interrupt configuration*/
#ifdef TIMER0_INTERRUPT 
        TIMER0_INTERRUPT_FlagClear();
        TIMER0_INTERRUPT_ENABLE();
        TIMER0_INTHANDLER = timer0->EXT_INTERRUPT;
#ifdef INTERRUPT_PRIORITY_LEVEL_ENABLE 
        INTERRUPT_PriorityLevelEnable();
        if (PRIORITY_HIGH == timer0->priority){
            INTERRUPT_GlobalHighEnable();
            TIMER0_INTERRUPT_PriortyHigh();
        }
        else if(PRIORITY_LOW == timer0->priority){
            INTERRUPT_GlobalLowEnable();
            TIMER0_INTERRUPT_PriortyLow();
        } 
#else
        INTERRUPT_GlobalEnabl();
        INTERRUPT_PeripheralEnable();
#endif
#endif
        /*enable timer0*/
        TIMER0_ENABLE();
    }
    return ret;   
}


Std_ReturnType timer0_Deinit(const timer0_t *timer0){
    Std_ReturnType ret = E_OK;
    if (NULL == timer0){
        ret = E_NOT_OK;
    }
    else {
        /*disable timer0*/
        TIMER0_DISABLE();
        /*disable interrupt future*/
#ifdef TIMER0_INTERRUPT
        TIMER0_INTERRUPT_FlagClear();
        TIMER0_INTERRUPT_DISABLE();
#endif
    }
    return ret;   
}


Std_ReturnType timer0_Read (const timer0_t *timer0, uint16 *value){
    Std_ReturnType ret = E_OK;
    if (NULL == timer0){
        ret = E_NOT_OK;
    }
    else {
        if(REGISTER_8BIT == timer0->timer_register_mode){
           *value = (uint16)TMR0L; 
        }
        else if(REGISTER_16BIT == timer0->timer_register_mode){
            uint8 timerlow = TMR0L; 
            uint8 timerhigh = TMR0H;
            *value =(uint16)(timerlow + (timerhigh << 8));
        }
    }
    return ret; 
}


Std_ReturnType timer0_write (const timer0_t *timer0, uint16 value){
    Std_ReturnType ret = E_OK;
    if (NULL == timer0){
        ret = E_NOT_OK;
    }
    else {
        if(REGISTER_8BIT == timer0->timer_register_mode){
           TMR0L = (uint8)value ; 
        }
        else if(REGISTER_16BIT == timer0->timer_register_mode){
            TMR0H = (value >> 8); 
            TMR0L = (uint8)value;
        }
    }
    return ret; 
}

void TIMER_ISR (void ){
    #ifdef TIMER0_INTERRUPT
    TIMER0_INTERRUPT_FlagClear();
   /*code*/
    TMR0H = (preload_value >> 8); 
    TMR0L = (uint8)preload_value;
    
    if(TIMER0_INTHANDLER) {
        TIMER0_INTHANDLER();
    }
    #endif
    
}
