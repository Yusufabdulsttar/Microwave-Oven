/* 
 * File:   mcal_interrupt_manager.h
 * Author: yusuf
 *
 * Created on April 27, 2023, 5:37 PM
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H

#include "mcal_interrupt_cfg.h"

void INT0_ISR (void);
void INT1_ISR (void);
void INT2_ISR (void);
void ADC_ISR (void);
void TIMER_ISR (void);
void TIMER1_ISR (void);
void TIMER2_ISR (void);
void TIMER3_ISR (void);
void CCP1_ISR (void);
void CCP2_ISR (void);
void RB4_ISR (uint8 logic);
void RB5_ISR (uint8 logic);
void RB6_ISR (uint8 logic);
void RB7_ISR (uint8 logic);
void USART_TX_ISR(void);
void USART_RX_ISR(void);
void SPI_ISR(void);
void I2C_ISR (void);
void I2C_BUS_COL_ISR (void);


#endif	/* MCAL_INTERRUPT_MANAGER_H */

