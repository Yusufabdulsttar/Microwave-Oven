/* 
 * File:   mcal_internal_interrupt.h
 * Author: yusuf
 *
 * Created on April 27, 2023, 5:36 PM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H

#include "mcal_interrupt_cfg.h"

/* section : Includes   */

/* section : Micro Declaration  */

/* section : Micro Function Declaration  */

/*configure adc interrupt*/
#ifdef ADC_INTERRUPT 
#define ADC_INTERRUPT_FlagClear()   (PIR1bits.ADIF = 0)
#define ADC_INTERRUPT_ENABLE()      (PIE1bits.ADIE = 1)
#define ADC_INTERRUPT_DISABLE()     (PIE1bits.ADIE = 0)
#ifdef INTERRUPT_PRIORITY_LEVEL_ENABLE 
#define ADC_INTERRUPT_PriortyHigh()    (IPR1bits.ADIP = 1)
#define ADC_INTERRUPT_PriortyLow()     (IPR1bits.ADIP = 0)
#endif
#endif

/*configure timer0 interrupt*/
#ifdef TIMER0_INTERRUPT 
#define TIMER0_INTERRUPT_FlagClear()     (INTCONbits.TMR0IF = 0)
#define TIMER0_INTERRUPT_ENABLE()        (INTCONbits.TMR0IE = 1)
#define TIMER0_INTERRUPT_DISABLE()       (INTCONbits.TMR0IE = 0)
#ifdef INTERRUPT_PRIORITY_LEVEL_ENABLE 
#define TIMER0_INTERRUPT_PriortyHigh()   (INTCON2bits.TMR0IP = 1)
#define TIMER0_INTERRUPT_PriortyLow()    (INTCON2bits.TMR0IP = 0)
#endif
#endif

/*configure timer1 interrupt*/
#ifdef TIMER1_INTERRUPT 
#define TIMER1_INTERRUPT_FlagClear()     (PIR1bits.TMR1IF = 0)
#define TIMER1_INTERRUPT_ENABLE()        (PIE1bits.TMR1IE = 1)
#define TIMER1_INTERRUPT_DISABLE()       (PIE1bits.TMR1IE = 0)
#ifdef INTERRUPT_PRIORITY_LEVEL_ENABLE 
#define TIMER1_INTERRUPT_PriortyHigh()   (IPR1bits.TMR1IP = 1)
#define TIMER1_INTERRUPT_PriortyLow()    (IPR1bits.TMR1IP = 0)
#endif
#endif

/*configure timer2 interrupt*/
#ifdef TIMER2_INTERRUPT 
#define TIMER2_INTERRUPT_FlagClear()     (PIR1bits.TMR2IF = 0)
#define TIMER2_INTERRUPT_ENABLE()        (PIE1bits.TMR2IE = 1)
#define TIMER2_INTERRUPT_DISABLE()       (PIE1bits.TMR2IE = 0)
#ifdef INTERRUPT_PRIORITY_LEVEL_ENABLE 
#define TIMER2_INTERRUPT_PriortyHigh()   (IPR1bits.TMR2IP = 1)
#define TIMER2_INTERRUPT_PriortyLow()    (IPR1bits.TMR2IP = 0)
#endif
#endif

/*configure timer3 interrupt*/
#ifdef TIMER3_INTERRUPT 
#define TIMER3_INTERRUPT_FlagClear()     (PIR2bits.TMR3IF = 0)
#define TIMER3_INTERRUPT_ENABLE()        (PIE2bits.TMR3IE = 1)
#define TIMER3_INTERRUPT_DISABLE()       (PIE2bits.TMR3IE = 0)
#ifdef INTERRUPT_PRIORITY_LEVEL_ENABLE 
#define TIMER3_INTERRUPT_PriortyHigh()   (IPR2bits.TMR3IP = 1)
#define TIMER3_INTERRUPT_PriortyLow()    (IPR2bits.TMR3IP = 0)
#endif
#endif

/*configure ccp1 interrupt*/
#ifdef CCP1_INTERRUPT 
#define CCP1_INTERRUPT_FlagClear()     (PIR1bits.CCP1IF = 0)
#define CCP1_INTERRUPT_ENABLE()        (PIE1bits.CCP1IE = 1)
#define CCP1_INTERRUPT_DISABLE()       (PIE1bits.CCP1IE = 0)
#ifdef INTERRUPT_PRIORITY_LEVEL_ENABLE 
#define CCP1_INTERRUPT_PriortyHigh()   (IPR1bits.CCP1IP = 1)
#define CCP1_INTERRUPT_PriortyLow()    (IPR1bits.CCP1IP = 0)
#endif
#endif

/*configure ccp2 interrupt*/
#ifdef CCP2_INTERRUPT 
#define CCP2_INTERRUPT_FlagClear()     (PIR2bits.CCP2IF = 0)
#define CCP2_INTERRUPT_ENABLE()        (PIE2bits.CCP2IE = 1)
#define CCP2_INTERRUPT_DISABLE()       (PIE2bits.CCP2IE = 0)
#ifdef INTERRUPT_PRIORITY_LEVEL_ENABLE 
#define CCP2_INTERRUPT_PriortyHigh()   (IPR2bits.CCP2IP = 1)
#define CCP2_INTERRUPT_PriortyLow()    (IPR2bits.CCP2IP = 0)
#endif
#endif

/*configure usart tx interrupt*/
#ifdef USART_TX_INTERRUPT 
#define USART_TX_INTERRUPT_ENABLE()        (PIE1bits.TX1IE = 1)
#define USART_TX_INTERRUPT_DISABLE()       (PIE1bits.TX1IE = 0)
#ifdef INTERRUPT_PRIORITY_LEVEL_ENABLE 
#define USART_TX_INTERRUPT_PriortyHigh()   (IPR1bits.TXIP = 1)
#define USART_TX_INTERRUPT_PriortyLow()    (IPR1bits.TXIP = 0)
#endif
#endif

/*configure usart rx interrupt*/
#ifdef USART_RX_INTERRUPT 
#define USART_RX_INTERRUPT_ENABLE()        (PIE1bits.RCIE = 1)
#define USART_RX_INTERRUPT_DISABLE()       (PIE1bits.RCIE = 0)
#ifdef INTERRUPT_PRIORITY_LEVEL_ENABLE 
#define USART_RX_INTERRUPT_PriortyHigh()   (IPR1bits.RCIP = 1)
#define USART_RX_INTERRUPT_PriortyLow()    (IPR1bits.RCIP = 0)
#endif
#endif

/*configure SPI interrupt*/
#ifdef SPI_INTERRUPT 
#define SPI_INTERRUPT_FlagClear()     (PIR1bits.SSPIF = 0)
#define SPI_INTERRUPT_ENABLE()        (PIE1bits.SSPIE = 1)
#define SPI_INTERRUPT_DISABLE()       (PIE1bits.SSPIE = 0)
#ifdef INTERRUPT_PRIORITY_LEVEL_ENABLE 
#define SPI_INTERRUPT_PriortyHigh()   (IPR1bits.SSPIP = 1)
#define SPI_INTERRUPT_PriortyLow()    (IPR1bits.SSPIP = 0)
#endif
#endif

/*configure I2C interrupt*/
#ifdef I2C_INTERRUPT 
#define I2C_INTERRUPT_FlagClear()             (PIR1bits.SSPIF = 0)
#define I2C_BUS_COL_INTERRUPT_FlagClear()     (PIR2bits.BCLIF = 0)
#define I2C_INTERRUPT_ENABLE()                (PIE1bits.SSPIE = 1)
#define I2C_BUS_COL_INTERRUPT_ENABLE()        (PIE2bits.BCLIE = 1)
#define I2C_INTERRUPT_DISABLE()               (PIE1bits.SSPIE = 0)
#define I2C_BUS_COL_INTERRUPT_DISABLE()       (PIE2bits.BCLIE = 0)
#ifdef INTERRUPT_PRIORITY_LEVEL_ENABLE 
#define I2C_BUS_COL_INTERRUPT_PriortyHigh()   (IPR2bits.BCLIP = 1)
#define I2C_INTERRUPT_PriortyHigh()           (IPR1bits.SSPIP = 1)
#define I2C_BUS_COL_INTERRUPT_PriortyLow()    (IPR2bits.BCLIP = 0)
#define I2C_INTERRUPT_PriortyLow()            (IPR1bits.SSPIP = 0)
#endif
#endif

/* section : Data Type Declaration  */
 
/* section : Function Declaration  */


#else
#endif	/* MCAL_INTERNAL_INTERRUPT_H */

