/* 
 * File:   mcal_interrupt_cfg.h
 * Author: yusuf
 *
 * Created on April 27, 2023, 5:35 PM
 */

#ifndef MCAL_INTERRUPT_CFG_H
#define	MCAL_INTERRUPT_CFG_H
/* section : Includes   */
#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "mcal_interrupt_gen_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* section : Micro Declaration  */
#define INTERRUPT_ENABLE    1
#define INTERRUPT_DISABLE   0
#define INTERRUPT_OCCUR     1
#define INTERRUPT_NOT_OCCUR 0
#define INTERRUPT_PRIORITY_ENABLE    1
#define INTERRUPT_PRIORITY_DISABLE   0


/* section : Micro Function Declaration  */

#ifdef INTERRUPT_PRIORITY_LEVEL_ENABLE 
#define INTERRUPT_PriorityLevelEnable()   (RCONbits.IPEN = 1)
#define INTERRUPT_PriorityLevelDisable()  (RCONbits.IPEN = 0)

#define INTERRUPT_GlobalHighEnable()      (INTCONbits.GIEH = 1)
#define INTERRUPT_GlobalHighDisable()     (INTCONbits.GIEH = 0)

#define INTERRUPT_GlobalLowEnable()       (INTCONbits.GIEL = 1)
#define INTERRUPT_GlobalLowDisable()      (INTCONbits.GIEL = 0)
#else
#define INTERRUPT_GlobalEnabl()          (INTCONbits.GIE = 1)
#define INTERRUPT_GlobalDisable()         (INTCONbits.GIE = 0)

#define INTERRUPT_PeripheralEnable()      (INTCONbits.PEIE = 1)
#define INTERRUPT_PeripheralDisable()     (INTCONbits.PEIE = 0)
#endif

/* section : Data Type Declaration  */
typedef enum{
    PRIORITY_HIGH,
    PRIORITY_LOW 
}Interrupt_priority_t;
/* section : Function Declaration  */

#endif	/* MCAL_INTERRUPT_CFG_H */

